//#define _ISR_TRACE
#include "OneTouchM3.h"
#include "PinChangeInt.h"
#include "WatchDog.h"

namespace OneTouchM3
{
//=============================== OneTouchM3 class =======================================
OneTouchM3& OneTouchM3::GetInstance()
{
    static OneTouchM3 theInstance;
    return theInstance;
}

OneTouchM3::OneTouchM3(): m_rightTurnSwitchPin(m_rightTurnSwitchPinNo), m_leftTurnSwitchPin(m_leftTurnSwitchPinNo),
        m_rightBlinkPin(m_rightBlinkPinNo), m_leftBlinkPin(m_leftBlinkPinNo),
        m_rightBcmPin(m_rightBcmPinNo), m_leftBcmPin(m_leftBcmPinNo)
{}

void OneTouchM3::Setup()
{
    InitPins();
    SetupISRs(); //ISR stands for Interrupt Service Routine
}

void RightBlinkISR();
void LeftBlinkISR();

void OneTouchM3::SetupISRs()
{
    AttachPinsInterrupts();

    WatchDog::init(ResetBCMDriveISR, OVF_1000MS, STOP); //initially stop the watchdog. To delay for two seconds use OVF_2000MS value
}

void OneTouchM3::AttachPinsInterrupts()
{
     //for turn switches we're interested for both RISING and FALLING fronts. They are interchanged into the ISR
     PCintPort::attachInterrupt(m_rightTurnSwitchPinNo, RightTurnSwitchISR, RISING);
     PCintPort::attachInterrupt(m_leftTurnSwitchPinNo,  LeftTurnSwitchISR, RISING);

    //the blinks ISR is used for counting the blinks. A blink is considered complete at its falling edge
    PCintPort::attachInterrupt(m_rightBlinkPinNo, RightBlinkISR, FALLING);
    PCintPort::attachInterrupt(m_leftBlinkPinNo,  LeftBlinkISR, FALLING);
}
void OneTouchM3::DetachPinsInterrupts()
{
     PCintPort::detachInterrupt(m_rightTurnSwitchPinNo);
     PCintPort::detachInterrupt(m_leftTurnSwitchPinNo);

    //the blinks ISR is used for counting the blinks. A blink is considered complete at its falling edge
    PCintPort::detachInterrupt(m_rightBlinkPinNo);
    PCintPort::detachInterrupt(m_leftBlinkPinNo);
}

bool OneTouchM3::IsPinUsed(const int& pinNo)
{
    switch(pinNo)
    {
    case m_rightTurnSwitchPinNo:
    case m_leftTurnSwitchPinNo:
    case m_rightBlinkPinNo:
    case m_leftBlinkPinNo:
    case m_rightBcmPinNo:
    case m_leftBcmPinNo:
        return true;
    default:
        return false;
    }
}

void OneTouchM3::InitPins()
{
    //set all unused pins as INPUT_PULLUP, including D1 - RX. On Arduino Mini it's not connected to anything and on release builds it would be set on the default mode
    for(int pin = 1; pin <= PIN_A7; pin++)
        if(!IsPinUsed(pin))
        {
            pinMode(pin, INPUT_PULLUP);
        }

    constexpr int txPin = 1;
    pinMode(txPin, OUTPUT); //On Arduino Mini it's not connected to anything and on release builds it would be set on the default mode
    pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, LOW);
}

extern OneTouchM3& g_theOneTouchM3;

void OneTouchM3::HandleTurnSwitch(/*volatile*/ TurnSwitchPin& turnSwitchPin, /*volatile*/ TurnSwitchPin& oppositeTurnSwitchPin,
    /*volatile*/ BlinkPin& blinkPin, /*volatile*/ BlinkPin& oppositeBlinkPin,
    /*volatile*/ BcmSignalPin& bcmPin, /*volatile*/ BcmSignalPin& oppositeBcmPin,
    void (*isr)(void))
{
    ISR_TR1("Front %i", turnSwitchPin.Event());
    if(turnSwitchPin.IsLow() && oppositeTurnSwitchPin.IsLow() && bcmPin.IsLow() && oppositeBcmPin.IsLow() && turnSwitchPin.Event() == RISING)
    { //The turn switch was activated in one of the directions and BCM wasn't driven in any way
        if (m_allowBCMDrive)
        {//if enough time passed from the last time the turn switch returned to its neutral position then drive the BCM (i.e. activate OneTouch function)
            ISR_TR("Drv BCM");
            bcmPin.SetHigh();
        }
        else
        {
            ISR_TR("BCM drv dis");
        }
    }
    else
    if(turnSwitchPin.IsLow() && (bcmPin.IsHigh() || oppositeBcmPin.IsHigh()) && turnSwitchPin.Event() == RISING)
    { //The turn switch was activated in one of the directions while the BCM was driven in this or opposite direction.  Abort the driving
        ISR_TR("T sw act - BCM drv. Stop");
        bcmPin.SetLow();
        oppositeBcmPin.SetLow();
        blinkPin.Reset(); //reset the blink counter pin
        oppositeBlinkPin.Reset(); //reset also the opposite bink counter pin
    }
    else
    if(turnSwitchPin.IsHigh() && turnSwitchPin.Event() == FALLING)
    { //The turn switch returned to its neutral position
        //disable the BCM drive for one or two second, i.e. up until the one or two seconds watchdog time awakes the cpu and execute its ISR
        if (m_switchLongTurned)
        {
            ISR_TR("Dis BCM drv 1s");
            m_allowBCMDrive = false;
            //start the WDT (Watchdog timer). It's the few one which runs at POWER_DOWN sleep level
            auto oldSREG = SREG;
            WatchDog::stop();
            WatchDog::start();
            SREG = oldSREG;
            m_switchLongTurned = false;
        }
    }
    //to correctly reflect the pins state on dumps, always toggle the current pin
    if(turnSwitchPin.IsHigh())
        ISR_TR("T sw h2l");
    else
        ISR_TR("T sw l2h");
    //ToDo: attach an observer for automatically setting the right interrupt, based on the pin state.
    //For now, only here the pin is toggled, so it's kind of acceptable
    PCintPort::detachInterrupt(turnSwitchPin.PinNo()); //detaching the interrupt. It will be reactivated bellow for the opposite front
    turnSwitchPin.Toggle();
    PCintPort::attachInterrupt(turnSwitchPin.PinNo(), isr, turnSwitchPin.Event()); //reactivating interrupt for the next opposite front

    ISR_TR1("Out %s", __func__);
}

void OneTouchM3::HandleBlink(/*volatile*/ BlinkPin& blinkPin, /*volatile*/ BlinkPin& oppositeBlinkPin,
    /*volatile*/ TurnSwitchPin& turnSwitchPin,
    /*volatile*/ BcmSignalPin& bcmPin, /*volatile*/ BcmSignalPin& oppositeBcmPin)
{
    ISR_TR1("In %s", __func__);
    if(bcmPin.IsHigh())
    { // BCM is currently driven by the OneTouch module
        ISR_TR("BCM drv. Inc blks cnt");
        ++blinkPin; //increment the blink pin counter
        ISR_TR1("Blks cnt: %i", blinkPin.Counter());
        if (blinkPin.MaxBlinksCountHit() || turnSwitchPin.IsHigh())
        {//if the OneTouch module drove for at least oneTouchMaxBlinksCount blinks or the turn switch it's being active for at least one blink
            ISR_TR("Dis drv BCM");
            bcmPin.SetLow();
            blinkPin.Reset(); //reset the blinks count
        }
        m_switchLongTurned = turnSwitchPin.IsHigh();
    }
    else
    if(oppositeBcmPin.IsHigh())
    {// hazard switch activated where all direction light bulbs are linking. If BCM driving is desired to continue despite the hazard switch activation then just comment this if
        ISR_TR("Opp blk => hazard sw. Dis drv BCM");
        oppositeBcmPin.SetLow();
        blinkPin.Reset(); //reset the blinks count
        oppositeBlinkPin.Reset(); //reset the blinks count also for the opposite pin
    }
    ISR_TR1("Out %s", __func__);
}


void RightTurnSwitchISR()
 { //The turn switch signal is considered to be hardware de-bounced (from tests, with a 0.1 uF capacitor)
    ISR_TR("RightTurnSwitchISR");
    g_theOneTouchM3.OnRightTurnSwitch();
}

void LeftTurnSwitchISR()
 { //The turn switch signal is considered to be hardware de-bounced (from tests, with a 0.1 uF capacitor)
    ISR_TR("LeftTurnSwitchISR");
    g_theOneTouchM3.OnLeftTurnSwitch();
}

void RightBlinkISR()
{ //The blink signal is considered to be hardware de-bounced (from tests, with a 0.1 uF capacitor)
    ISR_TR("RightBlinkISR");
    g_theOneTouchM3.OnRightBlink();
}

void ResetBCMDriveISR()
{
    ISR_TR("ResetBCMDriveISR");
    g_theOneTouchM3.OnResetBCMDrive();
    auto oldSREG = SREG;
    WatchDog::stop();
    SREG = oldSREG;
}

void LeftBlinkISR()
{ //The blink signal is considered to be hardware de-bounced (from tests, with a 0.1 uF capacitor)
    ISR_TR("LeftBlinkISR");
    g_theOneTouchM3.OnLeftBlink();
}

//=============================== BlinkCounterPin class =======================================
BlinkPin::BlinkPin(const int pinNo): CounterPin(pinNo)
{
    pinMode(pinNo, INPUT);

}

//=============================== TurnSwitchPin class =======================================
TurnSwitchPin::TurnSwitchPin(const int pinNo, const int initialState, const int initialExpectedEvent): 
        EventStatePin(pinNo, initialState, initialExpectedEvent)
{
    pinMode(pinNo, INPUT);
}
}

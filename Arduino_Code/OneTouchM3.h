/* 
 * File:   OneTouchM3.h
 * Author: mne
 *
 * Created on November 6, 2018, 4:04 PM
 */
#include "pins_arduino.h"
#include "DbgUtils.h"
#include <avr/sleep.h>
#include "Pins.h"

#ifndef ONETOUCHM3_H
#define ONETOUCHM3_H

namespace OneTouchM3
{
//Counter pin class used to count the blinks number.
class BlinkPin: public Pins::CounterPin
{
public:
    BlinkPin(const int pinNo);
    inline bool MaxBlinksCountHit() /*volatile*/; //return true if the maxim blink count was hit
protected:
    constexpr static int m_maxBlinksCount = 3; // for how many blinks the OneTouch module should drive the BCM
};

//Event pin class which on top actually sets the pin mode to INPUT. It's state is change in pin change ISRs (Interrupt Service Routines)
class TurnSwitchPin: public Pins::EventStatePin
{
public:
    TurnSwitchPin(const int pinNo, const int initialState = LOW, const int initialExpectedEvent = RISING);
};

//BCM pin class is the same as OutStatePin
using BcmSignalPin = Pins::OutStatePin;

/*Central class which implements the Renault Megane 3 One-touch logic. It has:
 * - two input pins for sensing the turn switch
 * - two input pins for counting the direction light bulbs blinks
 * - two output pins for driving the BCM (Body Control Module) through a pair of diodes
 */
class OneTouchM3
{
public:
    static OneTouchM3& GetInstance(); //static method from which the sole singleton instance can be accessed
    
    void Setup(); //must be called during the setup routine
    inline void Loop(); //must be called from the loop routine
    inline static void Sleep(); //put cpu to sleep. Usually called from Setup routine, after (re-)activating the interrupts
    
    inline void OnRightTurnSwitch(); //logic when the right turn switch (activation/deactivation)
    inline void OnLeftTurnSwitch(); //logic when the left turn switch (activation/deactivation)
    inline void OnRightBlink(); //logic when the right direction light bulb blink is over (FALLING front)
    inline void OnLeftBlink(); //logic when the left direction light bulb blink is over (FALLING front)
    inline void OnResetBCMDrive();
protected:
    OneTouchM3(); //Setup method must be called so the ISRs gets installed and make the magic possible
    
    static void InitPins(); //initialize the pins accordingly
        static bool IsPinUsed(const int& pinNo); //used by InitPins method

    static void SetupISRs(); //setup the interrupts routines for input pins
    static void AttachPinsInterrupts(); // attach the corresponding pin interrupts
    static void DetachPinsInterrupts(); // detach the corresponding pin interrupts

    void HandleTurnSwitch(/*volatile*/ TurnSwitchPin& turnSwitchPin, /*volatile*/ TurnSwitchPin& oppositeTurnSwitchPin,
        /*volatile*/ BlinkPin& blinkCounterPin,  /*volatile*/ BlinkPin& oppositeBlinkPin,
        /*volatile*/ BcmSignalPin& bcmPin, /*volatile*/ BcmSignalPin& oppositeBcmPin,
        void (*isr)(void)); //generic turn switch event handler called from right or left turn switches methods
    void HandleBlink(/*volatile*/ BlinkPin& blinkPin, /*volatile*/ BlinkPin& oppositeBlinkPin,
        /*volatile*/ TurnSwitchPin& turnSwitchPin,
        /*volatile*/ BcmSignalPin& bcmPin, /*volatile*/ BcmSignalPin& oppositeBcmPin); //generic blink handler called from right or left blinks
    
    inline void DumpState(); //dumps the pins state to serial so that we can get a hint of ISRs effect
    
    constexpr static int m_rightTurnSwitchPinNo = 2; //the Arduino right turn switch pin no
    /*volatile*/ TurnSwitchPin m_rightTurnSwitchPin; //the right turn switch pin management object

    constexpr static int m_leftTurnSwitchPinNo = 4; //the Arduino left turn switch pin no
    /*volatile*/ TurnSwitchPin m_leftTurnSwitchPin; //the left turn switch pin class

    constexpr static int m_rightBlinkPinNo = 6; //the Arduino right blink pin no
    /*volatile*/ BlinkPin m_rightBlinkPin; //the right blink pin management object
    
    constexpr static int m_leftBlinkPinNo =8; //the Arduino left blink pin no
    /*volatile*/ BlinkPin m_leftBlinkPin; //the left blink pin management object

    constexpr static int m_rightBcmPinNo = 10; //the Arduino right BCM signal pin no. BCM stands for Body Control Module or Unitate de Control Habitaclu in Romaninan
    /*volatile*/ BcmSignalPin m_rightBcmPin; //the right BCM signal pin management object

    constexpr static int m_leftBcmPinNo = 12; //the Arduino left BCM signal pin no. BCM stands for Body Control Module or Unitate de Control Habitaclu in Romaninan
    /*volatile*/ BcmSignalPin m_leftBcmPin; //the left BCM signal pin management object
    
    //during tests, when the direction stalk is activated to the end and than coming back to its neutral position it activates sometimes the OneTouch
    //function in the opposite direction. I guess th gravity helps to produce this side effect. The fix is to disable the OneTouch function for one or two second.
    //The member bellow defines if the BCM drive is allowed or not
    /*volatile*/ bool m_allowBCMDrive = true;
    /*volatile*/ bool m_switchLongTurned = false; //true if the turn switch was turned long enough, e.g. for at least one blink
};

//=============================== BlinkCounterPin class =======================================
bool BlinkPin::MaxBlinksCountHit() /*volatile*/
{
    return m_counter >= m_maxBlinksCount;
}

//=============================== OneTouchM3 class =======================================
void OneTouchM3::Sleep()
{
    sleep_cpu();
}

void OneTouchM3::Loop()
{//all object's pin data members are declared with  /*volatile*/ keyword commented out.
 //That's because they accessed only in ISRs and by default, on Arduino, an ISR can't be interrupted by another interrupt
 //If it happens to use a member in this method then enable its /*volatile*/ keyword along with its class methods 
    TR("\nLoop tick ...");
    DumpState();
    //the cpu wakes-up at each programmed pin change interrupt and continues cycling. It must be put to sleep again, awaiting for the next pin interrupt
    Sleep();
}

void OneTouchM3::OnResetBCMDrive()
{
    m_allowBCMDrive = true;
//    AttachPinsInterrupts();
}

void RightTurnSwitchISR();
void LeftTurnSwitchISR();
void ResetBCMDriveISR(); // resets the BCM drive flag after two seconds since the turn switch returned to its neutral position

void OneTouchM3::OnRightTurnSwitch()
{
    HandleTurnSwitch(m_rightTurnSwitchPin, m_leftTurnSwitchPin,
                     m_rightBlinkPin, m_leftBlinkPin,
                     m_rightBcmPin, m_leftBcmPin,
                     RightTurnSwitchISR);
}

void OneTouchM3::OnLeftTurnSwitch()
{
    HandleTurnSwitch(m_leftTurnSwitchPin, m_rightTurnSwitchPin,
                     m_leftBlinkPin, m_rightBlinkPin,
                     m_leftBcmPin, m_rightBcmPin,
                     LeftTurnSwitchISR);
}

void OneTouchM3::OnRightBlink()
{
    HandleBlink(m_rightBlinkPin, m_leftBlinkPin,
                m_rightTurnSwitchPin,
                m_rightBcmPin, m_leftBcmPin);
}

void OneTouchM3::OnLeftBlink()
{
    HandleBlink(m_leftBlinkPin, m_rightBlinkPin,
                m_leftTurnSwitchPin,
                m_leftBcmPin, m_rightBcmPin);
}

void OneTouchM3::DumpState()
{
    TR("Pins state:");
    TR1("  Right turn switch: %s", m_rightTurnSwitchPin.IsHigh() ? "high" : "low");
    TR1("  Left turn switch: %s", m_leftTurnSwitchPin.IsHigh() ? "high" : "low");
    TR1("  Right BCM drive: %s", m_rightBcmPin.IsHigh() ? "yes" : "no");
    TR1("  Left BCM drive: %s", m_leftBcmPin.IsHigh() ? "yes" : "no");
    TR1("  Right blink count: %i", m_rightBlinkPin.Counter());
    TR1("  Left blink count: %i", m_leftBlinkPin.Counter());
    TR1("  BCM drive: %s", m_allowBCMDrive ? "allowed" : "disallowed");
    TR1("  Long turn switch: %s", m_switchLongTurned ? "yes" : "no");
}}
#endif /* ONETOUCHM3_H */

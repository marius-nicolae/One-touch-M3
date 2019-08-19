#include "Pins.h"

namespace Pins
{
//=============================== Pin class =======================================
Pin::Pin(const int pinNo): m_pinNo(pinNo)
{}

//============================= CounterPin class ==================================
CounterPin::CounterPin(const int pinNo): Pin(pinNo), m_counter(0)
{}

//============================= StatePin class ==================================
StatePin::StatePin(const int pinNo, const int initialState): Pin(pinNo), m_state(initialState)
{}

//============================= ToggleStatePin class ==================================
ToggleStatePin::ToggleStatePin(const int pinNo, const int initialState): StatePin(pinNo, initialState)
{}
        
//============================= EventStatePin class ==================================
EventStatePin::EventStatePin(const int pinNo, const int initialState, const int initialExpectedEvent): ToggleStatePin(pinNo), m_event(initialExpectedEvent)
{}

void EventStatePin::Toggle() /*volatile*/
{
    ToggleStatePin::Toggle();
    m_event = m_event == RISING? FALLING : RISING; //toggle also the next expected state
}

//============================= OutStatePin class ==================================
OutStatePin::OutStatePin(const int pinNo, const int initialState): StatePin(pinNo, initialState)
{
    pinMode(pinNo, OUTPUT); digitalWrite(pinNo, initialState);
}

void OutStatePin::SetLow() /*volatile*/
{
    StatePin::SetLow();
    digitalWrite(PinNo(), LOW);
}

void OutStatePin::SetHigh() /*volatile*/
{
    StatePin::SetHigh();
    digitalWrite(PinNo(), HIGH);
}
}

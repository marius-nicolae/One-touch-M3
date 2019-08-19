/* 
 * File:   Pins.h
 * Author: mne
 *
 * Created on November 8, 2018, 3:48 PM
 */

#ifndef PINS_H
#define PINS_H
#include "Arduino.h"

namespace Pins
{

//Generic pin class used as the base for the other pins classes. It aggregates an Arduino pin number
class Pin
{
public:
    
    Pin(const int pinNo);
    
    inline int PinNo() const /*volatile*/;
protected:
    const int m_pinNo;
};

//Pin class with counting capabilities. Useful for blink pins where the number of FALLING transitions needs to be counted
class CounterPin: public Pin
{
public:
    CounterPin(const int pinNo);
    inline int Counter() const /*volatile*/; //return the current counter
    inline void Reset() /*volatile*/; //reset the counter to zero
    inline void operator ++() /*volatile*/; //pre-increment operator (more efficient then post-increment), increment the counter
protected:
    /*volatile*/ int m_counter;
};

//Pin class with current state associated. Is useful for building state machines where logic can be built based on a pin previous value
class StatePin: public Pin
{
public:
    StatePin(const int pinNo, const int initialState = LOW);
    inline bool IsLow() const /*volatile*/; //states if the pin state is low (as of m_state member)
    inline bool IsHigh() const /*volatile*/; //states if the pin state is high (as of m_state member)
    inline void SetLow() /*volatile*/; //sets the state (m_state member) to low
    inline void SetHigh() /*volatile*/; //sets the state (m_state member) to high
protected:
    /*volatile*/ int m_state;
};

//A pin with state superclass also with toggleable state property
class ToggleStatePin: public StatePin
{
public:
    ToggleStatePin(const int pinNo, const int initialState = LOW);
    inline void Toggle() /*volatile*/; //toggle state (from LOW to HIGH and the other way around)
};

//Toggleable pin class with a next expected (RISING or FALLING) event.
class EventStatePin: public ToggleStatePin
{
public:
    EventStatePin(const int pinNo, const int initialState = LOW, const int initialExpectedEvent = RISING);
    void Toggle() /*volatile*/; ////toggle state (from LOW to HIGH and the other way around) and the next expected event (from RISING to FALLING  and the other way around)
    inline int Event() /*volatile*/; //return the next expected event (as of m_event member)
protected:
    /*volatile*/ int m_event;
};

//Class with associated state for an output pin. It actually have pin drive capabilities
class OutStatePin: public StatePin
{
public:
    OutStatePin(const int pinNo, const int initialState = LOW); //also set the pin mode to OUTPUT and sets its initial state
    void SetLow() /*volatile*/; //drive output pin to LOW
    void SetHigh() /*volatile*/; //drive output pin to HIGH
};

//=============================== Pin class =======================================
int Pin::PinNo() const /*volatile*/
{
    return m_pinNo;
}

//============================= CounterPin class ==================================
int CounterPin::Counter() const /*volatile*/
{
    return m_counter;
}

void CounterPin::Reset() /*volatile*/
{
    m_counter = 0;
}

void CounterPin::operator ++() /*volatile*/
{
    m_counter++;
}

//=============================== MaxCountPin template class =======================================
//template<class Derived> 
//MaxCountPin::MaxCountPin(const int pinNo, const int maxCount): CounterPin(pinNo), m_maxCount(maxCount)
//{}

//============================= StatePin class ==================================

bool StatePin::IsLow() const /*volatile*/
{
    return m_state == LOW;
}

bool StatePin::IsHigh() const /*volatile*/
{
    return m_state == HIGH;
}

void StatePin::SetLow() /*volatile*/
{
    m_state = LOW;
}

void StatePin::SetHigh() /*volatile*/
{
    m_state = HIGH;
}

//============================= ToggleStatePin class ==================================
void ToggleStatePin::Toggle() /*volatile*/
{
    if(IsLow())
        SetHigh();
    else
        SetLow();
}

//============================= EventStatePin class ==================================
int EventStatePin::Event() /*volatile*/
{
    return m_event;
}
}
#endif /* PINS_H */

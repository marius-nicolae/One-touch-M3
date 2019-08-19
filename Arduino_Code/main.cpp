#include "OneTouchM3.h"
#include "Version.h"

namespace OneTouchM3
{
    OneTouchM3& g_theOneTouchM3 = OneTouchM3::GetInstance();
}

using namespace OneTouchM3;

void setup()
{
    InitTraceingFramework(); //init traces subsystem (available only for debug builds)
    TR3("OneTouchM3 version %i.%i.%i", MAJOR_VERSION, MINOR_VERSION, REVISION);
    //Power saving
   // disable ADC. Analog pins will be unavailable
    ADCSRA = 0;
    //set the power down sleep mode. The INT1, INT0 and Pin Change interrupts will still wake the CPU
    //According to http://www.gammon.com.au/power the power consumption should drop to 0.36 mA
    set_sleep_mode (SLEEP_MODE_PWR_DOWN);
    noInterrupts (); // make sure we don't get interrupted before we sleep
    //sleep_mode (); // here the device is actually put to sleep!!
    sleep_enable (); // enables the sleep bit in the mcucr register

    g_theOneTouchM3.Setup();
    interrupts (); // interrupts allowed now, next instruction WILL be executed
    g_theOneTouchM3.Sleep();  // here the device is put to sleep
}

void loop()
{
    g_theOneTouchM3.Loop();
}

#include "DbgUtils.h"
#include <stdio.h>
#include <stdarg.h>

void InitTraceingFramework()
{
#ifdef _TRACE
    Serial.setTimeout(2000);
    Serial.begin(115200);
#endif
}

#ifdef _TRACE
// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp)
{//PAY ATTENTION when using it in ISRs. They create unexpected strange behaviors like resets or immediately recalling the ISR with crazy variables values. See ISR_TR<no> macros
    Serial.println("");
    // transmit diagnostic informations through serial link. 
    TR1("Assertion failed in function: %s", __func);
    TR2("Location: %s:%i", __file, __lineno);
    TR1("Failed condition: \"%s\"", __sexp);
    // abort program execution.
    abort();
}

void _Trace(const char* traceFormatStr, ...)
{//PAY ATTENTION when using it in ISRs. They create unexpected strange behaviors like resets or immediately recalling the ISR with crazy variables values. See ISR_TR<no> macros
    constexpr int traceStrLen = 1000;
    char traceStr[traceStrLen];
    va_list args;
    va_start(args, traceFormatStr);
    vsnprintf(traceStr, traceStrLen, traceFormatStr, args);
    Serial.println(traceStr);
    Serial.flush();
}
#endif

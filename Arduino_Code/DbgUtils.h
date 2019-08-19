/* 
 * File:   Trace.h
 * Author: mne
 *
 * Created on November 2, 2018, 9:48 PM
 */

#ifndef TRACE_H
#define TRACE_H
#include "Arduino.h"

#ifdef _TRACE
    #define __ASSERT_USE_STDERR
    #include <assert.h>
#else
    #ifdef NDEBUG
        //NDEBUG defined. Just include assert.h
        #include <assert.h>
    #else
        //automatically define NDEBUG for Release version, in case it's not defined, for disabling assertions expanding into the code
        #define NDEBUG
        #include <assert.h>
        #undef NDEBUG
    #endif
#endif

#ifdef _TRACE
extern HardwareSerial Serial;

//void _Trace(const char* traceStr);
void _Trace(const char* traceFormatStr, ...);
#define TR(traceStr) _Trace(traceStr)
#define TR1(traceStr, p1) _Trace(traceStr, p1)
#define TR2(traceStr, p1, p2) _Trace(traceStr, p1, p2)
#define TR3(traceStr, p1, p2, p3) _Trace(traceStr, p1, p2, p3)
#define TR4(traceStr, p1, p2, p3, p4) _Trace(traceStr, p1, p2, p3, p4)
#define TR5(traceStr, p1, p2, p3, p4, p5) _Trace(traceStr, p1, p2, p3, p4, p5)
#define TR6(traceStr, p1, p2, p3, p4, p5, p6) _Trace(traceStr, p1, p2, p3, p4, p5, p6)
#define TR7(traceStr, p1, p2, p3, p4, p5, p6, p7) _Trace(traceStr, p1, p2, p3, p4, p5, p6, p7)
#define TR8(traceStr, p1, p2, p3, p4, p5, p6, p7, p8) _Trace(traceStr, p1, p2, p3, p4, p5, p6, p7, p8)
#define TR9(traceStr, p1, p2, p3, p4, p5, p6, p7, p8, p9) _Trace(traceStr, p1, p2, p3, p4, p5, p6, p7, p8, p9)

//WARNING: serial printing from ISRs can cause unexpected behavior such as sudden reset in the middle of print or immediately re-calling the ISR with crazy variables values
//Activate the _ISR_TRACE and use the ISR_TR<no> with caution, only shortly to debug ISRs although they should be simple enough
#ifdef _ISR_TRACE
#define ISR_TR(traceStr) TR(traceStr)
#define ISR_TR1(traceStr, p1) TR1(traceStr, p1)
#define ISR_TR2(traceStr, p1, p2) TR2(traceStr, p1, p2)
#define ISR_TR3(traceStr, p1, p2, p3) TR3(traceStr, p1, p2, p3)
#define ISR_TR4(traceStr, p1, p2, p3) TR4(traceStr, p1, p2, p3)
#define ISR_TR5(traceStr, p1, p2, p3, p4, p5) TR5(traceStr, p1, p2, p3, p4, p5)
#define ISR_TR6(traceStr, p1, p2, p3, p4, p5, p6) TR6(traceStr, p1, p2, p3, p4, p5, p6)
#define ISR_TR7(traceStr, p1, p2, p3, p4, p5, p6, p7) TR7(traceStr, p1, p2, p3, p4, p5, p6, p7)
#define ISR_TR8(traceStr, p1, p2, p3, p4, p5, p6, p7, p8) TR8(traceStr, p1, p2, p3, p4, p5, p6, p7, p8)
#define ISR_TR9(traceStr, p1, p2, p3, p4, p5, p6, p7, p8, p9) TR9(traceStr, p1, p2, p3, p4, p5, p6, p7, p8, p9)
#else
#define ISR_TR(traceStr)
#define ISR_TR1(traceStr, p1)
#define ISR_TR2(traceStr, p1, p2)
#define ISR_TR3(traceStr, p1, p2, p3)
#define ISR_TR4(traceStr, p1, p2, p3)
#define ISR_TR5(traceStr, p1, p2, p3, p4, p5)
#define ISR_TR6(traceStr, p1, p2, p3, p4, p5, p6)
#define ISR_TR7(traceStr, p1, p2, p3, p4, p5, p6, p7)
#define ISR_TR8(traceStr, p1, p2, p3, p4, p5, p6, p7, p8)
#define ISR_TR9(traceStr, p1, p2, p3, p4, p5, p6, p7, p8, p9)
#endif

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp);
#else
#define TR(traceStr)
#define TR1(traceStr, p1)
#define TR2(traceStr, p1, p2)
#define TR3(traceStr, p1, p2, p3)
#define TR4(traceStr, p1, p2, p3, p4)
#define TR5(traceStr, p1, p2, p3, p4, p5)
#define TR6(traceStr, p1, p2, p3, p4, p5, p6)
#define TR7(traceStr, p1, p2, p3, p4, p5, p6, p7)
#define TR8(traceStr, p1, p2, p3, p4, p5, p6, p7, p8)
#define TR9(traceStr, p1, p2, p3, p4, p5, p6, p7, p8, p9)

#define ISR_TR(traceStr)
#define ISR_TR1(traceStr, p1)
#define ISR_TR2(traceStr, p1, p2)
#define ISR_TR3(traceStr, p1, p2, p3)
#define ISR_TR4(traceStr, p1, p2, p3)
#define ISR_TR5(traceStr, p1, p2, p3, p4, p5)
#define ISR_TR6(traceStr, p1, p2, p3, p4, p5, p6)
#define ISR_TR7(traceStr, p1, p2, p3, p4, p5, p6, p7)
#define ISR_TR8(traceStr, p1, p2, p3, p4, p5, p6, p7, p8)
#define ISR_TR9(traceStr, p1, p2, p3, p4, p5, p6, p7, p8, p9)
#endif

void InitTraceingFramework();
#endif /* TRACE_H */


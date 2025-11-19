#ifndef TIMER_H
#define TIMER_H
#include    "common.h"
/*==========================================================================+
|           Constant                                                        |
+==========================================================================*/
#define        TIME_MAX         128

#define        TIME_SUCCESS     0
#define        TIME_E_MAX       1
#define        TIME_E_NOTIMER   2
#define        TIME_E_EXIST     3
/*==========================================================================+
|            Type definition                                                |
+==========================================================================*/
typedef    struct tagTIMER
{
    long*        plCounter;
}TIMER;


void*   TimerRun (void* data);
int     Init_Timer();
int     Destroy_Timer();
int     AddTimer(long* plCounter);
int     DeleteTimer(long* plCounter);

#endif // TIMER_H

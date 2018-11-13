#ifndef EVENTDEF_H
#define EVENTDEF_H
#include "EventId.h"
#include "Event.h"

struct TickEvent : Event
{
    TickEvent(int p_time, int test) : Event(EVT_TICK), time_(p_time), test_(test)
    {}
    ~TickEvent()
    {}
    time_t time_;
    int test_;
};



#endif
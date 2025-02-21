// ArrivalEvent.h
#ifndef ARRIVALEVENT_H
#define ARRIVALEVENT_H

#include "Event.h"
#include "EventTarget.h"

class ArrivalEvent : public Event {
public:
    ArrivalEvent(double eventTime, EventTarget* target)
        : Event(eventTime), target_(target) {}
    virtual ~ArrivalEvent() {}
    virtual void execute() override {
        target_->processArrival(time);
    }
private:
    EventTarget* target_;
};

#endif // ARRIVALEVENT_H

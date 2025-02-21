// DepartureEvent.h
#ifndef DEPARTUREEVENT_H
#define DEPARTUREEVENT_H

#include "Event.h"
#include "EventTarget.h"

class DepartureEvent : public Event {
public:
    DepartureEvent(double eventTime, EventTarget* target)
        : Event(eventTime), target_(target) {}
    virtual ~DepartureEvent() {}
    virtual void execute() override {
        target_->processDeparture(time);
    }
private:
    EventTarget* target_;
};

#endif // DEPARTUREEVENT_H

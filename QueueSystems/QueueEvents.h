#ifndef QUEUEEVENTS_H
#define QUEUEEVENTS_H

#include "Simulation.h"
#include "QueueModel.h"
#include <memory>

// Generic Arrival Event that calls the handleArrival method.
class GenericArrivalEvent : public Event {
public:
    QueueModel* queue;
    GenericArrivalEvent(double time, QueueModel* q) : Event(time), queue(q) {}

    virtual void process(Simulation& sim) override {
        queue->handleArrival(sim);
    }
};

// Generic Departure Event that calls the handleDeparture method.
class GenericDepartureEvent : public Event {
public:
    QueueModel* queue;
    GenericDepartureEvent(double time, QueueModel* q) : Event(time), queue(q) {}

    virtual void process(Simulation& sim) override {
        queue->handleDeparture(sim);
    }
};

#endif // QUEUEEVENTS_H


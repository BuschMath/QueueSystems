#ifndef QUEUEEVENTS_H
#define QUEUEEVENTS_H

#include "Simulation.h"
#include "QueueModel.h"

// ExternalArrivalEvent triggers an external arrival.
class ExternalArrivalEvent : public Event {
public:
    QueueModel* queue;
    ExternalArrivalEvent(double time, QueueModel* q) : Event(time), queue(q) {}

    virtual void process(Simulation& sim) override {
        queue->handleExternalArrival(sim);
    }
};

// InternalArrivalEvent triggers an internal (routed) arrival.
class InternalArrivalEvent : public Event {
public:
    QueueModel* queue;
    InternalArrivalEvent(double time, QueueModel* q) : Event(time), queue(q) {}

    virtual void process(Simulation& sim) override {
        queue->handleInternalArrival(sim);
    }
};

// Departure event remains unchanged.
class GenericDepartureEvent : public Event {
public:
    QueueModel* queue;
    GenericDepartureEvent(double time, QueueModel* q) : Event(time), queue(q) {}

    virtual void process(Simulation& sim) override {
        queue->handleDeparture(sim);
    }
};

#endif // QUEUEEVENTS_H

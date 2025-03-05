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

// ExternalArrivalEvent triggers the normal external arrival behavior.
class ExternalArrivalEvent : public Event {
public:
    QueueModel* queue;
    ExternalArrivalEvent(double time, QueueModel* q) : Event(time), queue(q) {}

    virtual void process(Simulation& sim) override {
        // Process the arrival as external, so schedule the next external arrival.
        // Cast to MM1Queue to access the new handleArrival(bool) method.
        dynamic_cast<MM1Queue*>(queue)->handleArrival(sim, true);
    }
};

// RoutedArrivalEvent processes an arrival that is routed from another node.
// It does not schedule a new external arrival.
class RoutedArrivalEvent : public Event {
public:
    QueueModel* queue;
    RoutedArrivalEvent(double time, QueueModel* q) : Event(time), queue(q) {}

    virtual void process(Simulation& sim) override {
        dynamic_cast<MM1Queue*>(queue)->handleArrival(sim, false);
    }
};

#endif // QUEUEEVENTS_H


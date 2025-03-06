#ifndef QUEUEMODEL_H
#define QUEUEMODEL_H

#include "Simulation.h"

// Abstract base class for queueing systems.
class QueueModel {
public:
    virtual ~QueueModel() {}

    // Handle an external arrival event (e.g. arrivals from outside the network).
    virtual void handleExternalArrival(Simulation& sim) = 0;
    // Handle an internal (routed) arrival event.
    virtual void handleInternalArrival(Simulation& sim) = 0;
    // Handle a departure event.
    virtual void handleDeparture(Simulation& sim) = 0;
};

#endif // QUEUEMODEL_H



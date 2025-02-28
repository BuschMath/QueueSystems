#ifndef QUEUEMODEL_H
#define QUEUEMODEL_H

#include "Simulation.h"

// Abstract base class for queueing systems.
class QueueModel {
public:
    virtual ~QueueModel() {}

    // Handle an arrival event.
    virtual void handleArrival(Simulation& sim) = 0;
    // Handle a departure event.
    virtual void handleDeparture(Simulation& sim) = 0;
};

#endif // QUEUEMODEL_H


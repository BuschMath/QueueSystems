#ifndef MM1QUEUE_H
#define MM1QUEUE_H

#include "QueueSystem.h"
#include "Simulator.h"
#include "ExponentialDistribution.h"
#include "ArrivalEvent.h"
#include "DepartureEvent.h"
#include "EventTarget.h"
#include "Queue.h"
#include "Server.h"
#include "Customer.h"
#include <stdexcept>

/**
 * @file MM1Queue.h
 * @brief Prebuilt simulation module for an M/M/1 queue.
 *
 * MM1Queue now implements EventTarget so that it can be used by generic simulation events.
 * It composes a Queue (for waiting customers) and a Server (for processing customers).
 */
class MM1Queue : public QueueSystem, public EventTarget {
public:
    MM1Queue(double arrivalRate, double serviceRate);
    virtual ~MM1Queue();

    // Analytical Methods
    virtual double getArrivalRate() const override;
    virtual double computeAverageWaitingTime() const override;
    virtual double computeAverageNumberInSystem() const override;

    // Simulation Methods (from QueueSystem)
    virtual void resetSimulationState() override;
    virtual int getCurrentCustomerCount() const override;

    // Methods required by the EventTarget interface.
    virtual void processArrival(double currentTime) override;
    virtual void processDeparture(double currentTime) override;

    // Helper Functions for simulation.
    bool isServerBusy() const;
    int getQueueSize() const;

private:
    double lambda_;  ///< Arrival rate (λ)
    double mu_;      ///< Service rate (μ)

    Queue queue_;    ///< Waiting line for customers.
    Server server_;  ///< Server processing customers.

    Simulator sim;   ///< The simulation engine.
    ExponentialDistribution* interarrivalDist;
    ExponentialDistribution* serviceDist;
};

#endif // MM1QUEUE_H

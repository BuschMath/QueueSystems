#ifndef DD1QUEUE_H
#define DD1QUEUE_H

#include "Simulation.h"
#include "QueueModel.h"
#include "QueueEvents.h"
#include "Observable.h"
#include <memory>

class DD1Queue : public QueueModel, public Observable {
public:
    // Constructor: Takes fixed interarrival and service times
    DD1Queue(Simulation& sim, double interarrivalTime, double serviceTime);

    // Start the simulation by scheduling the first arrival.
    void start();

    // Process arrivals and departures.
    virtual void handleArrival(Simulation& sim) override;
    virtual void handleDeparture(Simulation& sim) override;

    // Expose the state for observers.
    virtual int getState() const override {
        return numInSystem;
    }

    // Accessors for metrics.
    int getTotalArrivals() const;
    int getTotalDepartures() const;

private:
    Simulation& sim;
    double interarrivalTime; // Fixed time between arrivals
    double serviceTime;      // Fixed service time per customer
    int numInSystem;         // Number of customers in the system

    int totalArrivals;
    int totalDepartures;
    double cumulativeTimeWeightedCustomers;
    double lastEventTime;

    // Helper function to update metrics
    void updateMetrics(double currentTime);
};

#endif // DD1QUEUE_H


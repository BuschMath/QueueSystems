#ifndef MM1QUEUE_H
#define MM1QUEUE_H

#include "Simulation.h"
#include "QueueModel.h"
#include "QueueEvents.h"
#include <random>
#include <memory>

// MM1Queue implements a simple M/M/1 queue model.
class MM1Queue : public QueueModel {
public:
    // Constructor takes a reference to the simulation engine and queue parameters.
    MM1Queue(Simulation& sim, double arrivalRate, double serviceRate);

    // Start the simulation by scheduling the first arrival.
    void start();

    // Overrides from QueueModel.
    virtual void handleArrival(Simulation& sim) override;
    virtual void handleDeparture(Simulation& sim) override;

    // Accessors for simulation metrics.
    double getAverageNumberInSystem() const;
    int getTotalArrivals() const;
    int getTotalDepartures() const;

private:
    Simulation& sim;
    double lambda;  // Arrival rate
    double mu;      // Service rate
    int numInSystem;

    // Random number generators for exponential interarrival and service times.
    std::default_random_engine rng;
    std::exponential_distribution<double> arrivalDist;
    std::exponential_distribution<double> serviceDist;

    // Metrics for statistics.
    int totalArrivals;
    int totalDepartures;
    double cumulativeTimeWeightedCustomers;
    double lastEventTime;

    // Helper to update time-weighted metrics.
    void updateMetrics(double currentTime);
};

#endif // MM1QUEUE_H


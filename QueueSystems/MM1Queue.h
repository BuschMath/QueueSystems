#ifndef MM1QUEUE_H
#define MM1QUEUE_H

#include "Simulation.h"
#include "QueueModel.h"
#include "QueueEvents.h"
#include "Observable.h"
#include <optional>
#include <random>
#include <vector>
#include <memory>

// MM1Queue implements a simple M/M/1 queue model.
class MM1Queue : public QueueModel, public Observable {
public:
    // Constructor takes a reference to the simulation engine and queue parameters.
    MM1Queue(Simulation& sim, double arrivalRate, double serviceRate);

    // Start the simulation by scheduling the first arrival.
    void start();

    // Overrides from QueueModel.
    virtual void handleArrival(Simulation& sim) override;
    virtual void handleDeparture(Simulation& sim) override;

    // Expose the state (number of customers in the system) for observers.
    virtual int getState() const override {
        return numInSystem;
    }

    // Accessors for simulation metrics.
    double getAverageNumberInSystem() const;
    int getTotalArrivals() const;
    int getTotalDepartures() const;

    // Helper for obtaining next interarrival time.
    double getNextInterarrivalTime();

private:
    Simulation& sim;
    double lambda;  // Arrival rate
    double mu;      // Service rate
    int numInSystem;

    // Random number generators for exponential interarrival and service times.
    std::default_random_engine rng;
    std::optional<std::exponential_distribution<double>> arrivalDist;
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


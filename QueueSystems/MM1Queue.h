#ifndef MM1QUEUE_H
#define MM1QUEUE_H

#include "Simulation.h"
#include "QueueModel.h"
#include "QueueEvents.h"
#include "Observable.h"
#include <random>
#include <vector>
#include <memory>
#include <optional>
#include <limits>

// MM1Queue implements a simple M/M/1 queue model.
class MM1Queue : public QueueModel, public Observable {
public:
    // Constructor takes a reference to the simulation engine and queue parameters.
    MM1Queue(Simulation& sim, double arrivalRate, double serviceRate);

    // Start the simulation by scheduling the first external arrival.
    void start();

    // New interface for arrivals.
    virtual void handleExternalArrival(Simulation& sim) override;
    virtual void handleInternalArrival(Simulation& sim) override;
    virtual void handleDeparture(Simulation& sim) override;

    // Expose the state (number of customers in the system) for observers.
    virtual int getState() const override { return numInSystem; }

    // Accessors for simulation metrics.
    double getAverageNumberInSystem() const;
    int getTotalArrivals() const;
    int getTotalDepartures() const;

    // Helper for obtaining next interarrival time.
    double getNextInterarrivalTime();

protected:
    Simulation& sim;
    double lambda;  // External arrival rate
    double mu;      // Service rate
    int numInSystem;

    std::default_random_engine rng;
    // Use std::optional to handle zero arrival rate.
    std::optional<std::exponential_distribution<double>> arrivalDist;
    std::exponential_distribution<double> serviceDist;

    // Metrics for statistics.
    int totalArrivals;
    int totalDepartures;
    double cumulativeTimeWeightedCustomers;
    double lastEventTime;

    // Helper to update metrics.
    void updateMetrics(double currentTime);
};

#endif // MM1QUEUE_H

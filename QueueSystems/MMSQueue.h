#ifndef MMSQUEUE_H
#define MMSQUEUE_H

#include "Simulation.h"
#include "QueueModel.h"
#include "QueueEvents.h"
#include "Observable.h"
#include <random>
#include <vector>
#include <memory>
#include <optional>
#include <limits>

// MMSQueue implements an M/M/s queue model.
class MMSQueue : public QueueModel, public Observable {
public:
    // Constructor: takes the simulation engine, arrival rate, service rate, and number of servers.
    MMSQueue(Simulation& sim, double arrivalRate, double serviceRate, int servers);

    // Start the simulation by scheduling the first external arrival.
    void start();

    // New interface for arrivals:
    virtual void handleExternalArrival(Simulation& sim) override;
    virtual void handleInternalArrival(Simulation& sim) override;
    virtual void handleDeparture(Simulation& sim) override;

    // Expose the state (number in the system) for observers.
    virtual int getState() const override { return numInSystem; }

    // Accessors for simulation metrics.
    double getAverageNumberInSystem() const;
    int getTotalArrivals() const;
    int getTotalDepartures() const;

    // Helper for obtaining the next interarrival time.
    double getNextInterarrivalTime();

private:
    Simulation& sim;
    double lambda;  // External arrival rate.
    double mu;      // Service rate.
    int servers;    // Number of servers.

    int numInSystem;  // Total customers (in service + waiting).
    int busyServers;  // Servers currently busy.

    // Random number generators.
    std::default_random_engine rng;
    // Use std::optional so that we only create an exponential distribution if lambda > 0.
    std::optional<std::exponential_distribution<double>> arrivalDist;
    std::exponential_distribution<double> serviceDist;

    // Metrics.
    int totalArrivals;
    int totalDepartures;
    double cumulativeTimeWeightedCustomers;
    double lastEventTime;

    // Helper to update the time-weighted metric.
    void updateMetrics(double currentTime);
};

#endif // MMSQUEUE_H

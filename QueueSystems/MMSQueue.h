#ifndef MMSQUEUE_H
#define MMSQUEUE_H

#include "Simulation.h"
#include "QueueModel.h"
#include "QueueEvents.h"
#include "Observable.h"
#include <random>
#include <vector>
#include <memory>

// MMSQueue implements an M/M/s queue model.
class MMSQueue : public QueueModel, public Observable {
public:
    // Constructor: takes the simulation engine, arrival and service rates, and the number of servers.
    MMSQueue(Simulation& sim, double arrivalRate, double serviceRate, int servers);

    // Start the simulation by scheduling the first arrival event.
    void start();

    // Overrides from QueueModel.
    virtual void handleArrival(Simulation& sim) override;
    virtual void handleDeparture(Simulation& sim) override;

    // Expose the state (number of customers in the system) for observers.
    virtual int getState() const override { return numInSystem; }

    // Accessors for simulation metrics.
    double getAverageNumberInSystem() const;
    int getTotalArrivals() const;
    int getTotalDepartures() const;

private:
    Simulation& sim;
    double lambda;  // Arrival rate
    double mu;      // Service rate
    int servers;    // Number of servers in the system

    int numInSystem;  // Total number of customers (both in service and waiting)
    int busyServers;  // Number of servers currently busy

    // Random number generators for exponential interarrival and service times.
    std::default_random_engine rng;
    std::exponential_distribution<double> arrivalDist;
    std::exponential_distribution<double> serviceDist;

    // Metrics for statistics.
    int totalArrivals;
    int totalDepartures;
    double cumulativeTimeWeightedCustomers;
    double lastEventTime;

    // Update the time-weighted customer metric.
    void updateMetrics(double currentTime);
};

#endif // MMSQUEUE_H


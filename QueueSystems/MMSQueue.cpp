#include "MMSQueue.h"
#include "QueueEvents.h"
#include <limits>
#include <algorithm>

MMSQueue::MMSQueue(Simulation& sim, double arrivalRate, double serviceRate, int servers)
    : sim(sim), lambda(arrivalRate), mu(serviceRate), servers(servers),
    numInSystem(0), busyServers(0),
    rng(std::random_device{}()),
    serviceDist(serviceRate),
    totalArrivals(0), totalDepartures(0),
    cumulativeTimeWeightedCustomers(0.0), lastEventTime(0.0)
{
    // Only create the arrival distribution if lambda > 0.
    if (lambda > 0) {
        arrivalDist.emplace(lambda);
    }
}

double MMSQueue::getNextInterarrivalTime() {
    if (arrivalDist.has_value()) {
        return (*arrivalDist)(rng);
    }
    return std::numeric_limits<double>::infinity();
}

void MMSQueue::start() {
    double firstArrivalTime = sim.getCurrentTime() + getNextInterarrivalTime();
    if (std::isfinite(firstArrivalTime)) {
        // Schedule the first external arrival.
        sim.scheduleEvent(std::make_shared<ExternalArrivalEvent>(firstArrivalTime, this));
    }
}

void MMSQueue::handleExternalArrival(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalArrivals++;
    numInSystem++;

    // If a server is idle, start service immediately.
    if (busyServers < servers) {
        busyServers++;
        double departureTime = currentTime + serviceDist(rng);
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }

    // Schedule the next external arrival.
    double nextArrivalTime = currentTime + getNextInterarrivalTime();
    if (std::isfinite(nextArrivalTime)) {
        sim.scheduleEvent(std::make_shared<ExternalArrivalEvent>(nextArrivalTime, this));
    }
}

void MMSQueue::handleInternalArrival(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalArrivals++;
    numInSystem++;

    // For an internal (routed) arrival, do not schedule the next external arrival.
    if (busyServers < servers) {
        busyServers++;
        double departureTime = currentTime + serviceDist(rng);
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }
}

void MMSQueue::handleDeparture(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalDepartures++;
    numInSystem--;

    // A departure frees a busy server.
    if (busyServers > 0) {
        busyServers--;
    }

    // If there are waiting customers (numInSystem > busyServers) and an idle server is available, start service.
    if (numInSystem > busyServers && busyServers < servers) {
        busyServers++;
        double departureTime = currentTime + serviceDist(rng);
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }
}

double MMSQueue::getAverageNumberInSystem() const {
    return (lastEventTime > 0) ? cumulativeTimeWeightedCustomers / lastEventTime : 0.0;
}

int MMSQueue::getTotalArrivals() const {
    return totalArrivals;
}

int MMSQueue::getTotalDepartures() const {
    return totalDepartures;
}

void MMSQueue::updateMetrics(double currentTime) {
    double interval = currentTime - lastEventTime;
    cumulativeTimeWeightedCustomers += numInSystem * interval;
    lastEventTime = currentTime;
}

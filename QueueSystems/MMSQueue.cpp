#include "MMSQueue.h"
#include "QueueEvents.h"

MMSQueue::MMSQueue(Simulation& sim, double arrivalRate, double serviceRate, int servers)
    : sim(sim), lambda(arrivalRate), mu(serviceRate), servers(servers),
    numInSystem(0), busyServers(0),
    rng(std::random_device{}()),
    arrivalDist(arrivalRate), serviceDist(serviceRate),
    totalArrivals(0), totalDepartures(0),
    cumulativeTimeWeightedCustomers(0.0), lastEventTime(0.0)
{
}

void MMSQueue::start() {
    if (lambda > 0)
    {
        double firstArrivalTime = sim.getCurrentTime() + arrivalDist(rng);
        sim.scheduleEvent(std::make_shared<GenericArrivalEvent>(firstArrivalTime, this));
    }
}

void MMSQueue::updateMetrics(double currentTime) {
    double interval = currentTime - lastEventTime;
    cumulativeTimeWeightedCustomers += numInSystem * interval;
    lastEventTime = currentTime;
}

void MMSQueue::handleArrival(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalArrivals++;
    numInSystem++;

    // If at least one server is idle, start service immediately.
    if (busyServers < servers) {
        busyServers++;
        double departureTime = currentTime + serviceDist(rng);
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }

    // Schedule the next arrival event.
    double nextArrivalTime = currentTime + arrivalDist(rng);
    sim.scheduleEvent(std::make_shared<GenericArrivalEvent>(nextArrivalTime, this));
}

void MMSQueue::handleDeparture(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalDepartures++;
    numInSystem--;

    // A departure frees one busy server.
    if (busyServers > 0) {
        busyServers--;
    }

    // If there are still waiting customers (i.e. more customers in system than busy servers)
    // and an idle server is available, start service for one waiting customer.
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

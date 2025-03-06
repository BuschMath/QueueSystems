#include "MM1Queue.h"
#include "QueueEvents.h"
#include <limits>
#include <algorithm>

MM1Queue::MM1Queue(Simulation& sim, double arrivalRate, double serviceRate)
    : sim(sim), lambda(arrivalRate), mu(serviceRate),
    numInSystem(0), rng(std::random_device{}()),
    serviceDist(serviceRate),
    totalArrivals(0), totalDepartures(0),
    cumulativeTimeWeightedCustomers(0.0), lastEventTime(0.0)
{
    if (lambda > 0) {
        arrivalDist.emplace(lambda);
    }
}

double MM1Queue::getNextInterarrivalTime() {
    if (arrivalDist.has_value()) {
        return (*arrivalDist)(rng);
    }
    return std::numeric_limits<double>::infinity();
}

void MM1Queue::start() {
    double firstArrivalTime = sim.getCurrentTime() + getNextInterarrivalTime();
    if (std::isfinite(firstArrivalTime)) {
        sim.scheduleEvent(std::make_shared<ExternalArrivalEvent>(firstArrivalTime, this));
    }
}

void MM1Queue::handleExternalArrival(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalArrivals++;
    numInSystem++;

    // Schedule the next external arrival.
    double nextArrivalTime = currentTime + getNextInterarrivalTime();
    if (std::isfinite(nextArrivalTime)) {
        sim.scheduleEvent(std::make_shared<ExternalArrivalEvent>(nextArrivalTime, this));
    }

    // If server was idle, schedule a departure.
    if (numInSystem == 1) {
        double departureTime = currentTime + serviceDist(rng);
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }
}

void MM1Queue::handleInternalArrival(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalArrivals++;
    numInSystem++;

    // Note: Do not schedule the next external arrival.
    if (numInSystem == 1) {
        double departureTime = currentTime + serviceDist(rng);
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }
}

void MM1Queue::handleDeparture(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalDepartures++;
    numInSystem--;

    if (numInSystem > 0) {
        double departureTime = currentTime + serviceDist(rng);
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }
}

double MM1Queue::getAverageNumberInSystem() const {
    return (lastEventTime > 0) ? cumulativeTimeWeightedCustomers / lastEventTime : 0.0;
}

int MM1Queue::getTotalArrivals() const {
    return totalArrivals;
}

int MM1Queue::getTotalDepartures() const {
    return totalDepartures;
}

void MM1Queue::updateMetrics(double currentTime) {
    double interval = currentTime - lastEventTime;
    cumulativeTimeWeightedCustomers += numInSystem * interval;
    lastEventTime = currentTime;
}

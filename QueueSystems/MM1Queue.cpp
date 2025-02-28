#include "MM1Queue.h"
#include "QueueEvents.h"

MM1Queue::MM1Queue(Simulation& sim, double arrivalRate, double serviceRate)
    : sim(sim), lambda(arrivalRate), mu(serviceRate),
    numInSystem(0), rng(std::random_device{}()),
    arrivalDist(arrivalRate), serviceDist(serviceRate),
    totalArrivals(0), totalDepartures(0),
    cumulativeTimeWeightedCustomers(0.0), lastEventTime(0.0)
{
}

// Schedule the first arrival event.
void MM1Queue::start() {
    double firstArrivalTime = sim.getCurrentTime() + arrivalDist(rng);
    sim.scheduleEvent(std::make_shared<GenericArrivalEvent>(firstArrivalTime, this));
}

// Update the time-weighted metric based on elapsed time.
void MM1Queue::updateMetrics(double currentTime) {
    double interval = currentTime - lastEventTime;
    cumulativeTimeWeightedCustomers += numInSystem * interval;
    lastEventTime = currentTime;
}

// Process an arrival event.
void MM1Queue::handleArrival(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalArrivals++;
    numInSystem++;

    // Schedule the next arrival.
    double nextArrivalTime = currentTime + arrivalDist(rng);
    sim.scheduleEvent(std::make_shared<GenericArrivalEvent>(nextArrivalTime, this));

    // If the server was idle, immediately schedule a departure.
    if (numInSystem == 1) {
        double departureTime = currentTime + serviceDist(rng);
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }
}

// Process a departure event.
void MM1Queue::handleDeparture(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalDepartures++;
    numInSystem--;

    // If there are still customers waiting, schedule the next departure.
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

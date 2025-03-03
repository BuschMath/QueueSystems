#include "DD1Queue.h"
#include "QueueEvents.h"

DD1Queue::DD1Queue(Simulation& sim, double interarrivalTime, double serviceTime)
    : sim(sim), interarrivalTime(interarrivalTime), serviceTime(serviceTime),
    numInSystem(0), totalArrivals(0), totalDepartures(0),
    cumulativeTimeWeightedCustomers(0.0), lastEventTime(0.0)
{
}

// Schedule the first arrival event.
void DD1Queue::start() {
    double firstArrivalTime = sim.getCurrentTime() + interarrivalTime;
    sim.scheduleEvent(std::make_shared<GenericArrivalEvent>(firstArrivalTime, this));
}

// Update time-weighted metrics.
void DD1Queue::updateMetrics(double currentTime) {
    double interval = currentTime - lastEventTime;
    cumulativeTimeWeightedCustomers += numInSystem * interval;
    lastEventTime = currentTime;
}

// Process an arrival event.
void DD1Queue::handleArrival(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalArrivals++;
    numInSystem++;

    // Notify observers (StateLogger) of the queue state change
    notifyObservers(currentTime);

    // Schedule the next arrival.
    double nextArrivalTime = currentTime + interarrivalTime;
    sim.scheduleEvent(std::make_shared<GenericArrivalEvent>(nextArrivalTime, this));

    // If the server is idle, immediately schedule a departure.
    if (numInSystem == 1) {
        double departureTime = currentTime + serviceTime;
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }
}

// Process a departure event.
void DD1Queue::handleDeparture(Simulation& sim) {
    double currentTime = sim.getCurrentTime();
    updateMetrics(currentTime);
    totalDepartures++;
    numInSystem--;

    // Notify observers (StateLogger) of the queue state change
    notifyObservers(currentTime);

    // If there are still customers waiting, schedule the next departure.
    if (numInSystem > 0) {
        double departureTime = currentTime + serviceTime;
        sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
    }
}

// Accessor for total arrivals.
int DD1Queue::getTotalArrivals() const {
    return totalArrivals;
}

// Accessor for total departures.
int DD1Queue::getTotalDepartures() const {
    return totalDepartures;
}

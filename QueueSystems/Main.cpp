#include <iostream>
#include "Simulator.h"
#include "ExponentialDistribution.h"
#include "MM1Queue.h"
#include "ArrivalEvent.h"
#include "DepartureEvent.h"

// We assume that our Simulator has methods: isEmpty(), popNextEvent(),
// getCurrentTime(), and setCurrentTime(double).

int main() {
    // Simulation parameters.
    double arrivalRate = 0.5;     // λ = 0.5 (mean interarrival time = 2 time units)
    double serviceRate = 1.0;     // μ = 1.0 (mean service time = 1 time unit)
    double simulationEndTime = 100.0;  // Run simulation until time 100

    // Create the simulation engine.
    Simulator sim;

    // Create our prebuilt MM1Queue simulation module.
    MM1Queue mm1(arrivalRate, serviceRate);

    // Create exponential distributions for interarrival and service times.
    ExponentialDistribution interarrivalDist(arrivalRate);
    ExponentialDistribution serviceDist(serviceRate);

    // Schedule the first arrival event at time 0.
    sim.scheduleEvent(new ArrivalEvent(0.0, &mm1));

    // Main event-driven simulation loop.
    while (!sim.isEmpty() && sim.getCurrentTime() < simulationEndTime) {
        // Get the next event.
        Event* event = sim.popNextEvent();
        double eventTime = event->getTime();
        sim.setCurrentTime(eventTime);  // update simulation time

std::cout << "Processing event at time " << eventTime << std::endl;
std::cout << "Current number of customers in system: " << mm1.getCurrentCustomerCount() << std::endl;

        // Execute the event.
        event->execute();

        // Determine the type of event using dynamic_cast.
        // We assume our events are decoupled (they just call processArrival or processDeparture on the target).
        if (dynamic_cast<ArrivalEvent*>(event)) {
            // Schedule next arrival.
            double nextInterarrival = interarrivalDist.sample();
            double nextArrivalTime = eventTime + nextInterarrival;
            if (nextArrivalTime < simulationEndTime) {
                sim.scheduleEvent(new ArrivalEvent(nextArrivalTime, &mm1));
            }

            // If the server is idle (and there is a waiting customer), schedule a departure.
            if (!mm1.isServerBusy() && mm1.getQueueSize() > 0) {
                double serviceTime = serviceDist.sample();
                double departureTime = eventTime + serviceTime;
                sim.scheduleEvent(new DepartureEvent(departureTime, &mm1));
            }
        }
        else if (dynamic_cast<DepartureEvent*>(event)) {
            // After a departure, if the queue is non-empty, schedule the next departure.
            if (mm1.getQueueSize() > 0 || mm1.isServerBusy()) {
                double serviceTime = serviceDist.sample();
                double departureTime = eventTime + serviceTime;
                sim.scheduleEvent(new DepartureEvent(departureTime, &mm1));
            }
        }

        delete event;
    }

    std::cout << "Simulation finished at time " << sim.getCurrentTime() << std::endl;
    std::cout << "Final number of customers in system: " << mm1.getCurrentCustomerCount() << std::endl;

    return 0;
}

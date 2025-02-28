#include "Simulation.h"
#include "MM1Queue.h"
#include <iostream>

int main() {
    // Create the simulation engine.
    Simulation sim;

    // Define arrival and service rates.
    double lambda = 1.0; // Average of one arrival per time unit.
    double mu = 1.2;     // Service rate is slightly faster than the arrival rate.

    // Create the M/M/1 queue model.
    MM1Queue queue(sim, lambda, mu);
    queue.start();  // Schedule the first arrival.

    // Run the simulation for 100 time units.
    sim.run(100.0);

    // Output simulation metrics.
    std::cout << "Total Arrivals: " << queue.getTotalArrivals() << std::endl;
    std::cout << "Total Departures: " << queue.getTotalDepartures() << std::endl;
    std::cout << "Average Number in System: " << queue.getAverageNumberInSystem() << std::endl;

    return 0;
}

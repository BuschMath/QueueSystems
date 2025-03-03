#include <iostream>
#include "Simulation.h"
#include "DD1Queue.h"
#include "StateLogger.h"

int main() {
    // Create the simulation engine
    Simulation sim;

    // Define queue parameters (fixed interarrival and service times)
    double interarrivalTime = 2.0; // Every 2 time units
    double serviceTime = 1.5;      // Each service takes 1.5 time units

    // Create a D/D/1 queue
    DD1Queue queue(sim, interarrivalTime, serviceTime);

    // Attach a state logger to the queue
    StateLogger logger;
    queue.attach(&logger);

    // Start the queue simulation
    queue.start();

    // Run the simulation for 20 time units
    sim.run(20.0);

    // Print results
    std::cout << "Simulation completed.\n";
    std::cout << "Total Arrivals: " << queue.getTotalArrivals() << "\n";
    std::cout << "Total Departures: " << queue.getTotalDepartures() << "\n";

    // Retrieve and print the state log
    const auto& log = logger.getLog();
    std::cout << "\nTime\tQueue Size\n";
    std::cout << "------------------\n";
    for (const auto& entry : log) {
        std::cout << entry.time << "\t" << entry.state << "\n";
    }

    return 0;
}

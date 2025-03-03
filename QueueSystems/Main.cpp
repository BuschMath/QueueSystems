#include "Simulation.h"
#include "MM1Queue.h"
#include "MeasurementEvent.h"
#include "StateLogger.h"
#include <iostream>

int main() {
    // Create the simulation engine.
    Simulation sim;

    // Define arrival and service rates.
    double lambda = 1.0; // Average of one arrival per time unit.
    double mu = 1.2;     // Service rate is slightly faster than the arrival rate.
    double sampleInterval = 0.5; // Interval for sampling the system state.

    // Create the M/M/1 queue model.
    MM1Queue queue(sim, lambda, mu);

    StateLogger logger;
    queue.attach(&logger);

    queue.start();  // Schedule the first arrival.

    // Schedule the first measurement event.
    double firstMeasurementTime = sim.getCurrentTime() + sampleInterval;
    sim.scheduleEvent(std::make_shared<MeasurementEvent>(firstMeasurementTime, &queue, sampleInterval));

    // Run the simulation for 100 time units.
    sim.run(100.0);

    // Output simulation metrics.
    std::cout << "Total Arrivals: " << queue.getTotalArrivals() << std::endl;
    std::cout << "Total Departures: " << queue.getTotalDepartures() << std::endl;
    std::cout << "Average Number in System: " << queue.getAverageNumberInSystem() << std::endl;

    // Output the state log collected by the observer.
    const auto& log = logger.getLog();
    std::cout << "\nTime, Number in System:" << std::endl;
    for (const auto& entry : log) {
        std::cout << entry.time << ", " << entry.state << std::endl;
    }

    return 0;
}

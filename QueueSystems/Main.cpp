#include <iostream>
#include "Simulation.h"
#include "MMSQueue.h"
#include "StateLogger.h"
#include "MeasurementEvent.h"

int main() {
    // Create the simulation instance.
    Simulation sim;

    // Parameters for the MMS queue:
    double arrivalRate = 2.0;
    double serviceRate = 3.0;
    int numServers = 2;

    // Create the MMSQueue instance.
    MMSQueue queue(sim, arrivalRate, serviceRate, numServers);

    // Create a state logger and attach it to the queue.
    StateLogger logger;
    queue.attach(&logger);

    // Start the MMSQueue simulation by scheduling the first arrival.
    queue.start();

    // Schedule the measurement events to log the queue's state.
    // The first measurement event is scheduled at sampleInterval.
    double sampleInterval = 0.5;
    sim.scheduleEvent(std::make_shared<MeasurementEvent>(sampleInterval, &queue, sampleInterval));

    // Run the simulation until time 10.0.
    sim.run(10.0);

    // Output simulation metrics.
    std::cout << "Simulation finished at time: " << sim.getCurrentTime() << std::endl;
    std::cout << "Total Arrivals: " << queue.getTotalArrivals() << std::endl;
    std::cout << "Total Departures: " << queue.getTotalDepartures() << std::endl;
    std::cout << "Average Number in System: " << queue.getAverageNumberInSystem() << std::endl;

    // Print the state log collected by the StateLogger.
    std::cout << "\nState Log:" << std::endl;
    const auto& log = logger.getLog();
    for (const auto& entry : log) {
        std::cout << "Time: " << entry.time << ", Number in system: " << entry.state << std::endl;
    }

    return 0;
}

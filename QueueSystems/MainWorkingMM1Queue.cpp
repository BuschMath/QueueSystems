#include "Simulation.h"
#include "MM1Queue.h"
#include "MeasurementEvent.h"
#include "StateLogger.h"
#include <iostream>
#include <fstream>
#include <memory>

int main() {
    // Create the simulation engine.
    Simulation sim;

    // Define queue parameters.
    double arrivalRate = 5.0;  // external arrivals per time unit
    double serviceRate = 10.0; // services per time unit

    // Create an MM1Queue object.
    MM1Queue queue(sim, arrivalRate, serviceRate);

    // Create a StateLogger to record the queue state.
    StateLogger logger;

    // Attach the logger to the queue (MM1Queue inherits from Observable).
    queue.attach(&logger);

    // Schedule a measurement event to sample the queue state every 1.0 time unit.
    // Note: MeasurementEvent expects an Observable*, and queue qualifies.
    sim.scheduleEvent(std::make_shared<MeasurementEvent>(0.0, &queue, 1.0));

    // Start the queue (this schedules the first arrival if lambda > 0).
    queue.start();

    // Run the simulation until time 100.
    double simulationEndTime = 100.0;
    sim.run(simulationEndTime);

    // Extract simulation metrics.
    double averageNumber = queue.getAverageNumberInSystem();
    int totalArrivals = queue.getTotalArrivals();
    int totalDepartures = queue.getTotalDepartures();

    // Compute theoretical average number in system.
    double rho = arrivalRate / serviceRate; // 0.5
    double theoreticalAverage = rho / (1 - rho); // 0.5/0.5 = 1

    // Write the results to output.txt.
    std::ofstream outFile("output.txt");
    if (outFile.is_open()) {
        outFile << "MM1 Queue Simulation Results\n";
        outFile << "-----------------------------\n";
        outFile << "Simulation time: " << simulationEndTime << "\n";
        outFile << "External arrival rate (λ): " << arrivalRate << "\n";
        outFile << "Service rate (μ): " << serviceRate << "\n";
        outFile << "Utilization (ρ): " << rho << "\n";
        outFile << "Theoretical Average Number in System (L): " << theoreticalAverage << "\n\n";

        outFile << "Simulated Metrics:\n";
        outFile << "  Total Arrivals: " << totalArrivals << "\n";
        outFile << "  Total Departures: " << totalDepartures << "\n";
        outFile << "  Average Number in System: " << averageNumber << "\n\n";

        outFile << "Measurement Log:\n";
        const auto& log = logger.getLog();
        for (const auto& entry : log) {
            outFile << "  Time: " << entry.time << ", State: " << entry.state << "\n";
        }
        outFile.close();
    }
    else {
        std::cerr << "Error opening output.txt for writing.\n";
    }

    return 0;
}

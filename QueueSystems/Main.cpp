#include "Simulation.h"
#include "JacksonNetwork.h"
#include "MeasurementEvent.h"
#include "StateLogger.h"
#include "Observable.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

int main() {
    // Create the simulation engine.
    Simulation sim;

    // Create a Jackson network.
    JacksonNetwork network(sim);

    // Add nodes:
    // Node 0: M/M/1 queue with an external arrival rate of 5 and service rate of 10.
    int node0 = network.addMM1Queue(5, 10);
    // Node 1: M/M/1 queue with no external arrivals and service rate of 7.
    int node1 = network.addMM1Queue(0, 7);

    // Define the routing matrix:
    // From Node 0: 30% of departures are routed to Node 1 (70% exit the network).
    // From Node 1: 20% of departures are routed to Node 0 (80% exit the network).
    std::vector<std::vector<double>> routing = {
        { 0.0, 0.3 },
        { 0.2, 0.0 }
    };
    network.setRoutingMatrix(routing);

    // Create StateLoggers for each node.
    StateLogger logger0, logger1;
    if (auto n0 = network.getNode(node0))
        dynamic_cast<Observable*>(n0)->attach(&logger0);
    if (auto n1 = network.getNode(node1))
        dynamic_cast<Observable*>(n1)->attach(&logger1);

    // Schedule measurement events on each node (sampling every 1.0 time unit).
    if (auto obs0 = dynamic_cast<Observable*>(network.getNode(node0))) {
        sim.scheduleEvent(std::make_shared<MeasurementEvent>(0.0, obs0, 1.0));
    }
    if (auto obs1 = dynamic_cast<Observable*>(network.getNode(node1))) {
        sim.scheduleEvent(std::make_shared<MeasurementEvent>(0.0, obs1, 1.0));
    }

    // Start the network (schedules the first external arrival for each node, if applicable).
    network.start();

    // Run the simulation until time 100.
    double simulationTime = 100.0;
    sim.run(simulationTime);

    // For theoretical analysis:
    // The effective arrival rates satisfy:
    //   Λ0 = 5 + 0.2 * Λ1, and Λ1 = 0.3 * Λ0.
    // Solving gives Λ0 ≈ 5.3191 and Λ1 ≈ 1.5957.
    // Then, for an M/M/1 queue, L = ρ / (1-ρ) with ρ = Λ/μ.
    // Node 0: ρ0 = 5.3191/10 ≈ 0.53191, so L0 ≈ 1.137.
    // Node 1: ρ1 = 1.5957/7 ≈ 0.22796, so L1 ≈ 0.295.

    // Downcast to access metrics from the JacksonMM1Queue objects.
    auto node0Ptr = dynamic_cast<JacksonMM1Queue*>(network.getNode(node0));
    auto node1Ptr = dynamic_cast<JacksonMM1Queue*>(network.getNode(node1));

    // Open output file.
    std::ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error opening output.txt for writing.\n";
        return 1;
    }

    outFile << "Jackson Network Simulation Results\n";
    outFile << "----------------------------------\n";
    outFile << "Simulation Time: " << simulationTime << "\n\n";

    // Theoretical Metrics.
    outFile << "Theoretical Metrics:\n";
    outFile << "  Node 0 effective arrival rate: ~5.32 per time unit\n";
    outFile << "  Node 0 average number in system: ~1.14\n";
    outFile << "  Node 1 effective arrival rate: ~1.60 per time unit\n";
    outFile << "  Node 1 average number in system: ~0.30\n\n";

    // Simulated Metrics for Node 0.
    if (node0Ptr) {
        outFile << "Node 0 (MM1Queue) Simulation Metrics:\n";
        outFile << "  Total Arrivals: " << node0Ptr->getTotalArrivals() << "\n";
        outFile << "  Total Departures: " << node0Ptr->getTotalDepartures() << "\n";
        outFile << "  Average Number in System: " << node0Ptr->getAverageNumberInSystem() << "\n\n";
    }
    else {
        outFile << "Error retrieving metrics for Node 0.\n\n";
    }

    // Simulated Metrics for Node 1.
    if (node1Ptr) {
        outFile << "Node 1 (MM1Queue) Simulation Metrics:\n";
        outFile << "  Total Arrivals: " << node1Ptr->getTotalArrivals() << "\n";
        outFile << "  Total Departures: " << node1Ptr->getTotalDepartures() << "\n";
        outFile << "  Average Number in System: " << node1Ptr->getAverageNumberInSystem() << "\n\n";
    }
    else {
        outFile << "Error retrieving metrics for Node 1.\n\n";
    }

    // Write measurement logs.
    outFile << "Measurement Log for Node 0:\n";
    const auto& log0 = logger0.getLog();
    for (const auto& entry : log0) {
        outFile << "  Time: " << entry.time << ", State: " << entry.state << "\n";
    }

    outFile << "\nMeasurement Log for Node 1:\n";
    const auto& log1 = logger1.getLog();
    for (const auto& entry : log1) {
        outFile << "  Time: " << entry.time << ", State: " << entry.state << "\n";
    }

    outFile.close();
    return 0;
}

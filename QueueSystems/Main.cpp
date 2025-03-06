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
    // Node 0: MM1Queue with external arrival rate 4 and service rate 8.
    int node0 = network.addMM1Queue(4, 8);
    // Node 1: MMSQueue with external arrival rate 1, service rate 10, and 2 servers.
    int node1 = network.addMMSQueue(1, 10, 2);
    // Node 2: MM1Queue with external arrival rate 0 and service rate 6.
    int node2 = network.addMM1Queue(0, 6);

    // Define routing matrix (3x3):
    // Row i represents the routing probabilities from Node i to Nodes 0, 1, 2.
    // The remaining probability in each row is for departures exiting the network.
    std::vector<std::vector<double>> routing = {
        { 0.0, 0.2, 0.1 }, // From Node 0: 20% to Node 1, 10% to Node 2, 70% exit.
        { 0.2, 0.0, 0.3 }, // From Node 1: 20% to Node 0, 30% to Node 2, 50% exit.
        { 0.1, 0.2, 0.0 }  // From Node 2: 10% to Node 0, 20% to Node 1, 70% exit.
    };
    network.setRoutingMatrix(routing);

    // Create StateLoggers for each node.
    StateLogger logger0, logger1, logger2;
    if (auto n0 = network.getNode(node0))
        dynamic_cast<Observable*>(n0)->attach(&logger0);
    if (auto n1 = network.getNode(node1))
        dynamic_cast<Observable*>(n1)->attach(&logger1);
    if (auto n2 = network.getNode(node2))
        dynamic_cast<Observable*>(n2)->attach(&logger2);

    // Schedule measurement events on each node (sample every 1 time unit).
    if (auto obs0 = dynamic_cast<Observable*>(network.getNode(node0)))
        sim.scheduleEvent(std::make_shared<MeasurementEvent>(0.0, obs0, 1.0));
    if (auto obs1 = dynamic_cast<Observable*>(network.getNode(node1)))
        sim.scheduleEvent(std::make_shared<MeasurementEvent>(0.0, obs1, 1.0));
    if (auto obs2 = dynamic_cast<Observable*>(network.getNode(node2)))
        sim.scheduleEvent(std::make_shared<MeasurementEvent>(0.0, obs2, 1.0));

    // Start the network (each node schedules its first external arrival if applicable).
    network.start();

    // Run the simulation until time 100.
    double simulationTime = 100.0;
    sim.run(simulationTime);

    // Open output file.
    std::ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error opening output.txt for writing.\n";
        return 1;
    }

    outFile << "Jackson Network Simulation Results (3 Nodes)\n";
    outFile << "----------------------------------------------\n";
    outFile << "Simulation Time: " << simulationTime << "\n\n";

    // Retrieve and print metrics for each node.

    // Node 0 metrics (MM1Queue).
    auto node0Ptr = dynamic_cast<JacksonMM1Queue*>(network.getNode(node0));
    if (node0Ptr) {
        outFile << "Node 0 (MM1Queue) Simulation Metrics:\n";
        outFile << "  Total Arrivals: " << node0Ptr->getTotalArrivals() << "\n";
        outFile << "  Total Departures: " << node0Ptr->getTotalDepartures() << "\n";
        outFile << "  Average Number in System: " << node0Ptr->getAverageNumberInSystem() << "\n\n";
    }
    else {
        outFile << "Error retrieving metrics for Node 0.\n\n";
    }

    // Node 1 metrics (MMSQueue).
    auto node1Ptr = dynamic_cast<JacksonMMSQueue*>(network.getNode(node1));
    if (node1Ptr) {
        outFile << "Node 1 (MMSQueue) Simulation Metrics:\n";
        outFile << "  Total Arrivals: " << node1Ptr->getTotalArrivals() << "\n";
        outFile << "  Total Departures: " << node1Ptr->getTotalDepartures() << "\n";
        outFile << "  Average Number in System: " << node1Ptr->getAverageNumberInSystem() << "\n\n";
    }
    else {
        outFile << "Error retrieving metrics for Node 1.\n\n";
    }

    // Node 2 metrics (MM1Queue).
    auto node2Ptr = dynamic_cast<JacksonMM1Queue*>(network.getNode(node2));
    if (node2Ptr) {
        outFile << "Node 2 (MM1Queue) Simulation Metrics:\n";
        outFile << "  Total Arrivals: " << node2Ptr->getTotalArrivals() << "\n";
        outFile << "  Total Departures: " << node2Ptr->getTotalDepartures() << "\n";
        outFile << "  Average Number in System: " << node2Ptr->getAverageNumberInSystem() << "\n\n";
    }
    else {
        outFile << "Error retrieving metrics for Node 2.\n\n";
    }

    // Write measurement logs.
    outFile << "Measurement Log for Node 0:\n";
    for (const auto& entry : logger0.getLog()) {
        outFile << "  Time: " << entry.time << ", State: " << entry.state << "\n";
    }

    outFile << "\nMeasurement Log for Node 1:\n";
    for (const auto& entry : logger1.getLog()) {
        outFile << "  Time: " << entry.time << ", State: " << entry.state << "\n";
    }

    outFile << "\nMeasurement Log for Node 2:\n";
    for (const auto& entry : logger2.getLog()) {
        outFile << "  Time: " << entry.time << ", State: " << entry.state << "\n";
    }

    outFile.close();
    return 0;
}

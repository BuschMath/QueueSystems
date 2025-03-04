#include "Simulation.h"
#include "JacksonNetwork.h"
#include "MeasurementEvent.h"
#include "StateLogger.h"
#include <memory>
#include <vector>
#include <iostream>

int main() {
    // Create the simulation engine.
    Simulation sim;

    // Create a Jackson network.
    JacksonNetwork network(sim);

    // Add nodes. For instance, add one M/M/1 node and one M/M/s (with 2 servers) node.
    int node0 = network.addMM1Queue(0.0833, 0.1667); // arrival rate 0.0833, service rate 0.1667
	int node1 = network.addMM1Queue(0.00000001, 0.1167); // arrival rate 0, service rate 0.1167

    // Define routing probabilities:
    // For node0, 30% go to node1; for node1, 20% go back to node0.
    // The remaining probability in each row corresponds to departures leaving the network.
    std::vector<std::vector<double>> routing = {
        { 0.0, 0.3 }, // From node0: 0 to node0, 0.3 to node1, 0.7 leave.
        { 0.2, 0.0 }  // From node1: 0.2 to node0, 0 to node1, 0.8 leave.
    };
    network.setRoutingMatrix(routing);

    // Optionally, attach observers to nodes for monitoring.
    StateLogger logger;
    if (auto n0 = network.getNode(node0))
        dynamic_cast<Observable*>(n0)->attach(&logger);
    if (auto n1 = network.getNode(node1))
        dynamic_cast<Observable*>(n1)->attach(&logger);

    // Instead of scheduling the measurement event on the logger,
    // schedule measurement events on the observable nodes.
    if (auto obs0 = dynamic_cast<Observable*>(network.getNode(node0))) {
        sim.scheduleEvent(std::make_shared<MeasurementEvent>(0.0, obs0, 1.0));
    }
    if (auto obs1 = dynamic_cast<Observable*>(network.getNode(node1))) {
        sim.scheduleEvent(std::make_shared<MeasurementEvent>(0.0, obs1, 1.0));
    }

    // Start the network.
    network.start();

    // Run the simulation until time 60.
    sim.run(60.0);

    // After simulation, you can extract metrics (for example, average number in system)
    // by downcasting to JacksonMM1Queue or JacksonMMSQueue as needed.
    auto mm1Node = dynamic_cast<JacksonMM1Queue*>(network.getNode(node0));
    auto mmsNode = dynamic_cast<JacksonMM1Queue*>(network.getNode(node1));

    if (mm1Node) {
        std::cout << "Node0 (MM1Queue) Metrics:\n";
        std::cout << "  Total Arrivals: " << mm1Node->getTotalArrivals() << "\n";
        std::cout << "  Total Departures: " << mm1Node->getTotalDepartures() << "\n";
        std::cout << "  Average Number in System: " << mm1Node->getAverageNumberInSystem() << "\n";
    }
    else {
        std::cout << "Failed to retrieve MM1Queue metrics.\n";
    }

    if (mmsNode) {
        std::cout << "Node1 (MMSQueue) Metrics:\n";
        std::cout << "  Total Arrivals: " << mmsNode->getTotalArrivals() << "\n";
        std::cout << "  Total Departures: " << mmsNode->getTotalDepartures() << "\n";
        std::cout << "  Average Number in System: " << mmsNode->getAverageNumberInSystem() << "\n";
    }
    else {
        std::cout << "Failed to retrieve MMSQueue metrics.\n";
    }

    // Extract and print the measurement log from the logger.
    const auto& log = logger.getLog();
    std::cout << "\nMeasurement Log:\n";
    for (const auto& entry : log) {
        std::cout << "  Time: " << entry.time << ", State: " << entry.state << "\n";
    }

    return 0;
}

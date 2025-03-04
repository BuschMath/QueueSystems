#include "JacksonNetwork.h"
#include <numeric>
#include <random>
#include <iostream>

// -------------------------
// JacksonMM1Queue Implementation
// -------------------------
JacksonMM1Queue::JacksonMM1Queue(Simulation& sim, double arrivalRate, double serviceRate, int nodeId, JacksonNetwork* network)
    : MM1Queue(sim, arrivalRate, serviceRate), nodeId(nodeId), network(network)
{
}

void JacksonMM1Queue::handleDeparture(Simulation& sim) {
    // Process the departure as in a regular MM1 queue.
    MM1Queue::handleDeparture(sim);
    // After handling departure, route the departing customer.
    network->routeCustomer(nodeId, sim.getCurrentTime());
}

// -------------------------
// JacksonMMSQueue Implementation
// -------------------------
JacksonMMSQueue::JacksonMMSQueue(Simulation& sim, double arrivalRate, double serviceRate, int servers, int nodeId, JacksonNetwork* network)
    : MMSQueue(sim, arrivalRate, serviceRate, servers), nodeId(nodeId), network(network)
{
}

void JacksonMMSQueue::handleDeparture(Simulation& sim) {
    MMSQueue::handleDeparture(sim);
    network->routeCustomer(nodeId, sim.getCurrentTime());
}

// -------------------------
// JacksonNetwork Implementation
// -------------------------
JacksonNetwork::JacksonNetwork(Simulation& sim)
    : sim(sim), rng(std::random_device{}())
{
}

int JacksonNetwork::addMM1Queue(double arrivalRate, double serviceRate) {
    int nodeId = static_cast<int>(nodes.size());
    // Create a new JacksonMM1Queue and store it.
    JacksonMM1Queue* node = new JacksonMM1Queue(sim, arrivalRate, serviceRate, nodeId, this);
    nodes.push_back(node);
    return nodeId;
}

int JacksonNetwork::addMMSQueue(double arrivalRate, double serviceRate, int servers) {
    int nodeId = static_cast<int>(nodes.size());
    JacksonMMSQueue* node = new JacksonMMSQueue(sim, arrivalRate, serviceRate, servers, nodeId, this);
    nodes.push_back(node);
    return nodeId;
}

void JacksonNetwork::setRoutingMatrix(const std::vector<std::vector<double>>& matrix) {
    routingMatrix = matrix;
}

void JacksonNetwork::start() {
    // Start each node by calling its start() method.
    // We assume that all nodes are either JacksonMM1Queue or JacksonMMSQueue,
    // both of which inherit the start() method from MM1Queue/MMSQueue.
    for (auto node : nodes) {
        // Downcast is safe given our usage.
        if (auto mm1 = dynamic_cast<JacksonMM1Queue*>(node)) {
            mm1->start();
        }
        else if (auto mms = dynamic_cast<JacksonMMSQueue*>(node)) {
            mms->start();
        }
    }
}

void JacksonNetwork::routeCustomer(int fromNodeId, double currentTime) {
    // Check that we have a routing row for this node.
    if (fromNodeId >= routingMatrix.size())
        return;

    const std::vector<double>& row = routingMatrix[fromNodeId];

    // Sum of routing probabilities for departures from node fromNodeId.
    double sumProb = std::accumulate(row.begin(), row.end(), 0.0);

    // Draw a random number in [0,1].
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double r = dist(rng);

    // Determine destination by checking cumulative probabilities.
    double cumulative = 0.0;
    int destination = -1;
    for (size_t j = 0; j < row.size(); j++) {
        cumulative += row[j];
        if (r < cumulative) {
            destination = static_cast<int>(j);
            break;
        }
    }

    // If destination remains -1 then the customer leaves the network.
    if (destination >= 0 && destination < nodes.size()) {
std::cout << "Routing customer from node " << fromNodeId << " to node " << destination << " at time " << currentTime << std::endl;
if(fromNodeId == 0 && destination == 1)
     node0to1Counter++;
if(fromNodeId == 1 && destination == 0)
	 node1to0Counter++;
std::cout << "node0to1Counter: " << node0to1Counter << std::endl;
std::cout << "node1to0Counter: " << node1to0Counter << std::endl;
        // Schedule an arrival event for the destination node immediately.
        sim.scheduleEvent(std::make_shared<GenericArrivalEvent>(currentTime, nodes[destination]));
    }
}

QueueModel* JacksonNetwork::getNode(int nodeId) {
    if (nodeId >= 0 && nodeId < static_cast<int>(nodes.size()))
        return nodes[nodeId];
    return nullptr;
}

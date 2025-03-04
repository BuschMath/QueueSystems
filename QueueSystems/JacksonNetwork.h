#ifndef JACKSON_NETWORK_H
#define JACKSON_NETWORK_H

#include "Simulation.h"
#include "QueueModel.h"
#include "MM1Queue.h"
#include "MMSQueue.h"
#include "QueueEvents.h"
#include <vector>
#include <random>
#include <memory>

// Forward declaration
class JacksonNetwork;

// Wrapper for an M/M/1 queue that routes departures.
class JacksonMM1Queue : public MM1Queue {
public:
    int nodeId;                   // Unique id for this node.
    JacksonNetwork* network;      // Back-pointer to the Jackson network simulator.

    JacksonMM1Queue(Simulation& sim, double arrivalRate, double serviceRate, int nodeId, JacksonNetwork* network);

    // Override to add routing after departure.
    virtual void handleDeparture(Simulation& sim) override;
};

// Wrapper for an M/M/s queue that routes departures.
class JacksonMMSQueue : public MMSQueue {
public:
    int nodeId;
    JacksonNetwork* network;

    JacksonMMSQueue(Simulation& sim, double arrivalRate, double serviceRate, int servers, int nodeId, JacksonNetwork* network);

    virtual void handleDeparture(Simulation& sim) override;
};

// JacksonNetwork class simulates a network of queues where departures from one node
// can be probabilistically routed to another node (or leave the network).
class JacksonNetwork {
public:
    // Constructor takes a reference to the simulation engine.
    JacksonNetwork(Simulation& sim);

    // Add a new M/M/1 queue node. Returns the node id.
    int addMM1Queue(double arrivalRate, double serviceRate);

    // Add a new M/M/s queue node. Returns the node id.
    int addMMSQueue(double arrivalRate, double serviceRate, int servers);

    // Set the routing matrix. For node i, routingMatrix[i][j] is the probability that a departing
    // customer will be routed to node j. (The row may sum to less than one; the remainder is the
    // probability the customer leaves the network.)
    void setRoutingMatrix(const std::vector<std::vector<double>>& routingMatrix);

    // Start the network by starting all nodes.
    void start();

    // Called by a node (via the wrapper) when a departure occurs.
    // currentTime is the simulation time at departure.
    void routeCustomer(int fromNodeId, double currentTime);

    // Optionally, provide access to a node.
    QueueModel* getNode(int nodeId);

private:
    Simulation& sim;
    std::vector<QueueModel*> nodes;  // Stores pointers to our Jackson queue nodes.
    std::vector<std::vector<double>> routingMatrix;
    std::default_random_engine rng;

    int node0to1Counter = 0;
    int node1to0Counter = 0;
};

#endif // JACKSON_NETWORK_H


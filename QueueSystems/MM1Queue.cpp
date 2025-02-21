#include "MM1Queue.h"

MM1Queue::MM1Queue(double arrivalRate, double serviceRate)
    : lambda_(arrivalRate), mu_(serviceRate), queue_(), server_(serviceRate)
{
    if (arrivalRate >= serviceRate) {
        throw std::invalid_argument("Unstable system: arrival rate must be less than service rate (λ < μ).");
    }
}

MM1Queue::~MM1Queue() {
    // Clean up any remaining customers from the queue.
    while (!queue_.isEmpty()) {
        Customer* customer = queue_.dequeue();
        delete customer;
    }
    // If the server is busy, finish service and clean up the customer.
    if (!server_.isIdle()) {
        Customer* customer = server_.finishService(0.0); // Using 0.0 as a dummy time.
        delete customer;
    }
}

// --- Analytical Methods ---

double MM1Queue::getArrivalRate() const {
    return lambda_;
}

double MM1Queue::computeAverageWaitingTime() const {
    // For an M/M/1 queue, average waiting time in the system W = 1 / (μ - λ)
    return 1.0 / (mu_ - lambda_);
}

double MM1Queue::computeAverageNumberInSystem() const {
    // For an M/M/1 queue, average number in the system L = λ / (μ - λ)
    return lambda_ / (mu_ - lambda_);
}

// --- Simulation Methods ---

void MM1Queue::processArrival(double currentTime) {
    // Create and enqueue a new Customer.
    Customer* customer = new Customer(currentTime);
    queue_.enqueue(customer);

    // If server is idle, start service immediately.
    if (!isServerBusy() && !queue_.isEmpty()) {
        Customer* nextCustomer = queue_.dequeue();
        server_.startService(nextCustomer, currentTime);
    }
}

void MM1Queue::processDeparture(double currentTime) {
    // Finish service for the current customer.
    Customer* finishedCustomer = server_.finishService(currentTime);
    if (finishedCustomer) {
        delete finishedCustomer;
    }
    // If there are customers waiting, start service for the next customer.
    if (!queue_.isEmpty()) {
        Customer* nextCustomer = queue_.dequeue();
        server_.startService(nextCustomer, currentTime);
    }
}

int MM1Queue::getCurrentCustomerCount() const {
    // Total customers equals those waiting in the queue plus one if the server is busy.
    int count = queue_.size();
    if (!server_.isIdle()) {
        count++;
    }
    return count;
}

void MM1Queue::resetSimulationState() {
    // Clear the queue.
    while (!queue_.isEmpty()) {
        Customer* customer = queue_.dequeue();
        delete customer;
    }
    // Reset the server if it is busy.
    if (!server_.isIdle()) {
        Customer* customer = server_.finishService(0.0);
        delete customer;
    }
}

bool MM1Queue::isServerBusy() const {
    // The server is busy if it is not idle.
    return !server_.isIdle();
}

int MM1Queue::getQueueSize() const {
    return queue_.size();
}

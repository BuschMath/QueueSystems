#include "MM1Queue.h"
#include <stdexcept>

/**
 * @brief Constructor for MM1Queue.
 *
 * Initializes the arrival and service rates and sets the simulation state to zero customers.
 * Throws an exception if the system is unstable (λ >= μ).
 *
 * @param arrivalRate The arrival rate (λ) of customers.
 * @param serviceRate The service rate (μ) of the server.
 */
MM1Queue::MM1Queue(double arrivalRate, double serviceRate)
    : lambda_(arrivalRate), mu_(serviceRate), currentCustomerCount_(0)
{
    if (arrivalRate >= serviceRate) {
        throw std::invalid_argument("System is unstable: arrival rate must be less than service rate (λ < μ).");
    }
}

/**
 * @brief Destructor for MM1Queue.
 */
MM1Queue::~MM1Queue() {
    // No dynamic memory cleanup required.
}

/**
 * @brief Get the arrival rate (λ) for the queue.
 *
 * @return double The arrival rate.
 */
double MM1Queue::getArrivalRate() const {
    return lambda_;
}

/**
 * @brief Compute the average waiting time in the system (W).
 *
 * For an M/M/1 queue, W = 1 / (μ - λ).
 *
 * @return double The average waiting time.
 */
double MM1Queue::computeAverageWaitingTime() const {
    return 1.0 / (mu_ - lambda_);
}

/**
 * @brief Compute the average number of customers in the system (L).
 *
 * For an M/M/1 queue, L = ρ / (1 - ρ), where ρ = λ / μ.
 *
 * @return double The average number of customers in the system.
 */
double MM1Queue::computeAverageNumberInSystem() const {
    double rho = lambda_ / mu_;
    return rho / (1.0 - rho);
}

/**
 * @brief Compute the average waiting time in the queue (Wq).
 *
 * For an M/M/1 queue, Wq = ρ / (μ - λ), where ρ = λ / μ.
 *
 * @return double The average waiting time in the queue.
 */
double MM1Queue::computeAverageWaitingTimeQueue() const {
    double rho = lambda_ / mu_;
    return rho / (mu_ - lambda_);
}

/**
 * @brief Compute the average number of customers in the queue (Lq).
 *
 * For an M/M/1 queue, Lq = ρ^2 / (1 - ρ), where ρ = λ / μ.
 *
 * @return double The average number of customers in the queue.
 */
double MM1Queue::computeAverageNumberInQueue() const {
    double rho = lambda_ / mu_;
    return (rho * rho) / (1.0 - rho);
}

// --- Simulation Methods Implementation ---

/**
 * @brief Process a customer arrival.
 *
 * Updates the simulation state by incrementing the current customer count.
 * Additional simulation-specific actions (like recording the arrival time) can be added here.
 *
 * @param currentTime The simulation time at which the arrival occurs.
 */
void MM1Queue::processArrival(double currentTime) {
    // Update state: increment the customer count.
    currentCustomerCount_++;
    // (Optional: record currentTime for statistical analysis)
}

/**
 * @brief Process a customer departure.
 *
 * Updates the simulation state by decrementing the current customer count.
 * Additional simulation-specific actions (like computing waiting time) can be added here.
 *
 * @param currentTime The simulation time at which the departure occurs.
 */
void MM1Queue::processDeparture(double currentTime) {
    // Ensure that there is at least one customer to depart.
    if (currentCustomerCount_ > 0) {
        currentCustomerCount_--;
    }
    // (Optional: update statistics such as total waiting time)
}

/**
 * @brief Get the current number of customers in the system.
 *
 * @return int The current customer count.
 */
int MM1Queue::getCurrentCustomerCount() const {
    return currentCustomerCount_;
}

/**
 * @brief Reset the simulation state.
 *
 * Resets the current customer count to zero. Additional statistics can be reset here as well.
 */
void MM1Queue::resetSimulationState() {
    currentCustomerCount_ = 0;
}

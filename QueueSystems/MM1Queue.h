#ifndef MM1QUEUE_H
#define MM1QUEUE_H

#include "QueueSystem.h"

/**
 * @file MM1Queue.h
 * @brief Concrete class for an M/M/1 queueing system with simulation capabilities.
 *
 * This class represents a single-server M/M/1 queue. In addition to providing analytical
 * formulas (e.g., average waiting time, average number in system), it supports simulation by
 * maintaining the current system state and providing methods to process arrival and departure events.
 */
class MM1Queue : public QueueSystem {
public:
    /**
     * @brief Constructor for the M/M/1 queue.
     *
     * @param arrivalRate The arrival rate (λ) of customers.
     * @param serviceRate The service rate (μ) of the server.
     *
     * Throws an exception if λ >= μ (unstable system).
     */
    MM1Queue(double arrivalRate, double serviceRate);

    /**
     * @brief Destructor.
     */
    virtual ~MM1Queue();

    // Analytical Methods

    /**
     * @brief Get the arrival rate (λ) for the queue.
     *
     * @return double The arrival rate.
     */
    virtual double getArrivalRate() const override;

    /**
     * @brief Compute the average waiting time in the system (W).
     *
     * For an M/M/1 queue, W = 1 / (μ - λ).
     *
     * @return double The average waiting time.
     */
    virtual double computeAverageWaitingTime() const override;

    /**
     * @brief Compute the average number of customers in the system (L).
     *
     * For an M/M/1 queue, L = ρ / (1 - ρ), where ρ = λ / μ.
     *
     * @return double The average number in the system.
     */
    virtual double computeAverageNumberInSystem() const override;

    /**
     * @brief Compute the average waiting time in the queue (Wq).
     *
     * For an M/M/1 queue, Wq = ρ / (μ - λ), where ρ = λ / μ.
     *
     * @return double The average waiting time in the queue.
     */
    double computeAverageWaitingTimeQueue() const;

    /**
     * @brief Compute the average number of customers in the queue (Lq).
     *
     * For an M/M/1 queue, Lq = ρ^2 / (1 - ρ), where ρ = λ / μ.
     *
     * @return double The average number in the queue.
     */
    double computeAverageNumberInQueue() const;

    // Simulation Methods

    /**
     * @brief Process a customer arrival at the given simulation time.
     *
     * This method updates the system state when an arrival event occurs.
     *
     * @param currentTime The simulation time at which the arrival occurs.
     */
    virtual void processArrival(double currentTime) override;

    /**
     * @brief Process a customer departure at the given simulation time.
     *
     * This method updates the system state when a departure event occurs.
     *
     * @param currentTime The simulation time at which the departure occurs.
     */
    virtual void processDeparture(double currentTime) override;

    /**
     * @brief Get the current number of customers in the system.
     *
     * @return int The current number of customers.
     */
    virtual int getCurrentCustomerCount() const override;

    /**
     * @brief Reset the simulation state to initial conditions.
     *
     * This allows the system to be reused for multiple simulation runs.
     */
    virtual void resetSimulationState() override;

private:
    double lambda_; ///< Arrival rate (λ)
    double mu_;     ///< Service rate (μ)

    // Simulation state variables
    int currentCustomerCount_; ///< Current number of customers in the system.
};

#endif // MM1QUEUE_H

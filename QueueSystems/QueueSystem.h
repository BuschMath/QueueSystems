#ifndef QUEUESYSTEM_H
#define QUEUESYSTEM_H

/**
 * @file QueueSystem.h
 * @brief Abstract base class for queueing system models with simulation capabilities.
 *
 * This class defines the interface for both analytical and simulation functionalities.
 * Derived classes must implement methods for computing performance metrics and for processing
 * simulation events such as customer arrivals and departures.
 */
class QueueSystem {
public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures that the destructors of derived classes are called properly.
     */
    virtual ~QueueSystem();

    // Analytical Methods

    /**
     * @brief Get the arrival rate (λ) for the queueing system.
     * @return double The arrival rate.
     */
    virtual double getArrivalRate() const = 0;

    /**
     * @brief Compute the average waiting time in the system (analytical calculation).
     * @return double The average waiting time.
     */
    virtual double computeAverageWaitingTime() const = 0;

    /**
     * @brief Compute the average number of customers in the system (analytical calculation).
     * @return double The average number in the system.
     */
    virtual double computeAverageNumberInSystem() const = 0;

    // Simulation Methods

    /**
     * @brief Process a customer arrival at the given simulation time.
     *
     * This method updates the system state (e.g., increments the customer count, records arrival time)
     * and is invoked by the simulation engine when an arrival event occurs.
     *
     * @param currentTime The simulation time at which the arrival occurs.
     */
    virtual void processArrival(double currentTime) = 0;

    /**
     * @brief Process a customer departure at the given simulation time.
     *
     * This method updates the system state (e.g., decrements the customer count, computes waiting time)
     * and is invoked by the simulation engine when a departure event occurs.
     *
     * @param currentTime The simulation time at which the departure occurs.
     */
    virtual void processDeparture(double currentTime) = 0;

    /**
     * @brief Get the current number of customers in the system.
     *
     * This function returns the dynamic state of the system as maintained by the simulation.
     *
     * @return int The current number of customers.
     */
    virtual int getCurrentCustomerCount() const = 0;

    /**
     * @brief Reset the simulation state to initial conditions.
     *
     * Useful for running multiple simulation replications without re-instantiating the object.
     */
    virtual void resetSimulationState() = 0;
};

#endif // QUEUESYSTEM_H

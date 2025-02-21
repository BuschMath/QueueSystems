#ifndef CUSTOMER_H
#define CUSTOMER_H

/**
 * @file Customer.h
 * @brief Represents a customer in the simulation.
 *
 * This class stores key information about a customer such as the time of arrival,
 * the time when service begins, and the time of departure. This data is used to
 * compute performance metrics (e.g., waiting time, total time in system).
 */
class Customer {
public:
    /**
     * @brief Constructor for Customer.
     *
     * @param arrivalTime The simulation time at which the customer arrives.
     */
    Customer(double arrivalTime);

    /**
     * @brief Get the arrival time of the customer.
     * @return double The arrival time.
     */
    double getArrivalTime() const;

    /**
     * @brief Set the service start time for the customer.
     *
     * @param time The simulation time when service for this customer begins.
     */
    void setServiceStartTime(double time);

    /**
     * @brief Get the service start time.
     * @return double The service start time.
     */
    double getServiceStartTime() const;

    /**
     * @brief Set the departure time for the customer.
     *
     * @param time The simulation time when the customer departs.
     */
    void setDepartureTime(double time);

    /**
     * @brief Get the departure time.
     * @return double The departure time.
     */
    double getDepartureTime() const;

private:
    double arrivalTime_;         ///< The time at which the customer arrives.
    double serviceStartTime_;    ///< The time when service begins (initialized to -1).
    double departureTime_;       ///< The time when the customer departs (initialized to -1).
};

#endif // CUSTOMER_H


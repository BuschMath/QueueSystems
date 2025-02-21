#ifndef SERVER_H
#define SERVER_H

#include "Customer.h"

/**
 * @file Server.h
 * @brief Class representing a server that processes customers.
 *
 * The Server class maintains the current state of the server (busy or idle),
 * its service rate, and a pointer to the customer currently being served (if any).
 * It provides methods to assign a customer for service and to finish the service.
 */
class Server {
public:
    /**
     * @brief Constructor for Server.
     *
     * @param serviceRate The service rate (μ) of the server.
     */
    Server(double serviceRate);

    /**
     * @brief Destructor for Server.
     */
    ~Server();

    /**
     * @brief Check if the server is idle.
     *
     * @return true If no customer is being served.
     * @return false If a customer is currently in service.
     */
    bool isIdle() const;

    /**
     * @brief Assign a customer to the server to begin service.
     *
     * Sets the server status to busy and stores the pointer to the customer.
     * Also records the service start time in the Customer object.
     *
     * @param customer Pointer to the Customer to be served.
     * @param currentTime The current simulation time.
     */
    void startService(Customer* customer, double currentTime);

    /**
     * @brief Complete service for the current customer.
     *
     * Records the departure time for the customer, clears the server,
     * and returns the pointer to the customer that just finished service.
     *
     * @param currentTime The current simulation time.
     * @return Customer* Pointer to the customer that has been served.
     *         Returns nullptr if the server was idle.
     */
    Customer* finishService(double currentTime);

    /**
     * @brief Get the service rate (μ) of the server.
     *
     * @return double The service rate.
     */
    double getServiceRate() const;

private:
    double serviceRate_;      ///< Service rate (μ) of the server.
    Customer* currentCustomer_; ///< Pointer to the customer currently being served (nullptr if idle).
};

#endif // SERVER_H


#include "Customer.h"

/**
 * @brief Constructor implementation.
 *
 * Initializes the arrival time and sets the service start and departure times
 * to -1 to indicate that they haven't been set yet.
 *
 * @param arrivalTime The simulation time at which the customer arrives.
 */
Customer::Customer(double arrivalTime)
    : arrivalTime_(arrivalTime), serviceStartTime_(-1.0), departureTime_(-1.0)
{
}

/**
 * @brief Get the arrival time.
 * @return double The arrival time.
 */
double Customer::getArrivalTime() const {
    return arrivalTime_;
}

/**
 * @brief Set the service start time.
 * @param time The time when service begins.
 */
void Customer::setServiceStartTime(double time) {
    serviceStartTime_ = time;
}

/**
 * @brief Get the service start time.
 * @return double The service start time.
 */
double Customer::getServiceStartTime() const {
    return serviceStartTime_;
}

/**
 * @brief Set the departure time.
 * @param time The time when the customer departs.
 */
void Customer::setDepartureTime(double time) {
    departureTime_ = time;
}

/**
 * @brief Get the departure time.
 * @return double The departure time.
 */
double Customer::getDepartureTime() const {
    return departureTime_;
}

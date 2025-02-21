#include "Server.h"

Server::Server(double serviceRate)
    : serviceRate_(serviceRate), currentCustomer_(nullptr) {
}

Server::~Server() {
    // Note: If the Server owns the currentCustomer_, ensure it is properly deleted.
    // For now, we assume external management of Customer memory.
}

bool Server::isIdle() const {
    return currentCustomer_ == nullptr;
}

void Server::startService(Customer* customer, double currentTime) {
    if (customer == nullptr) return;
    currentCustomer_ = customer;
    // Record the service start time in the customer.
    currentCustomer_->setServiceStartTime(currentTime);
}

Customer* Server::finishService(double currentTime) {
    if (currentCustomer_ == nullptr) {
        return nullptr;
    }
    // Record the departure time for the customer.
    currentCustomer_->setDepartureTime(currentTime);
    Customer* finishedCustomer = currentCustomer_;
    currentCustomer_ = nullptr; // Mark server as idle.
    return finishedCustomer;
}

double Server::getServiceRate() const {
    return serviceRate_;
}

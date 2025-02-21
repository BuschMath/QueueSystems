#include "Queue.h"

Queue::Queue() {
    // No initialization needed for std::queue.
}

Queue::~Queue() {
    // Optionally, delete remaining Customer objects if ownership is held here.
    while (!customerQueue_.empty()) {
        // If Queue owns the Customer memory, delete them:
        // delete customerQueue_.front();
        customerQueue_.pop();
    }
}

void Queue::enqueue(Customer* customer) {
    customerQueue_.push(customer);
}

Customer* Queue::dequeue() {
    if (customerQueue_.empty()) {
        return nullptr;
    }
    Customer* frontCustomer = customerQueue_.front();
    customerQueue_.pop();
    return frontCustomer;
}

bool Queue::isEmpty() const {
    return customerQueue_.empty();
}

int Queue::size() const {
    return static_cast<int>(customerQueue_.size());
}

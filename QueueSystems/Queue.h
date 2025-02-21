#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include "Customer.h"

/**
 * @file Queue.h
 * @brief Class for managing a FIFO queue of customers.
 *
 * The Queue class maintains a FIFO (first-in-first-out) ordering of Customer objects.
 * It provides methods to add a customer, remove a customer, check if the queue is empty,
 * and get the current number of waiting customers.
 */
class Queue {
public:
    /**
     * @brief Constructor for Queue.
     */
    Queue();

    /**
     * @brief Destructor for Queue.
     *
     * Clears any remaining customers from the queue.
     */
    ~Queue();

    /**
     * @brief Add a customer to the back of the queue.
     *
     * @param customer Pointer to the Customer object to be added.
     */
    void enqueue(Customer* customer);

    /**
     * @brief Remove a customer from the front of the queue.
     *
     * @return Customer* Pointer to the customer removed from the queue.
     *         Returns nullptr if the queue is empty.
     */
    Customer* dequeue();

    /**
     * @brief Check if the queue is empty.
     *
     * @return true If no customers are waiting.
     * @return false Otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Get the current number of customers in the queue.
     *
     * @return int The number of waiting customers.
     */
    int size() const;

private:
    std::queue<Customer*> customerQueue_; ///< Underlying container for storing Customer pointers.
};

#endif // QUEUE_H


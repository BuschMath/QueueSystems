#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>
#include "Event.h"

/**
 * @file EventQueue.h
 * @brief A priority queue wrapper for simulation events.
 *
 * The EventQueue class maintains a min-heap of Event pointers, using EventComparator to
 * order events by their scheduled time in ascending order.
 */
class EventQueue {
public:
    /**
     * @brief Destructor.
     *
     * Cleans up any remaining events.
     */
    ~EventQueue();

    /**
     * @brief Schedule (push) an event into the queue.
     *
     * @param event Pointer to the Event to schedule.
     */
    void scheduleEvent(Event* event);

    /**
     * @brief Check whether the queue is empty.
     *
     * @return true if no events are scheduled, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Retrieve and remove the next event (with the smallest time) from the queue.
     *
     * @return Event* Pointer to the next scheduled Event.
     */
    Event* popNextEvent();

private:
    // Using std::priority_queue with a vector container and our custom comparator.
    std::priority_queue<Event*, std::vector<Event*>, EventComparator> queue_;
};

#endif // EVENTQUEUE_H

#include "EventQueue.h"
#include <stdexcept>

EventQueue::~EventQueue() {
    // Clean up any remaining events in the queue.
    while (!queue_.empty()) {
        delete queue_.top();
        queue_.pop();
    }
}

void EventQueue::scheduleEvent(Event* event) {
    queue_.push(event);
}

bool EventQueue::isEmpty() const {
    return queue_.empty();
}

Event* EventQueue::popNextEvent() {
    if (queue_.empty()) {
        throw std::runtime_error("EventQueue is empty.");
    }
    Event* nextEvent = queue_.top();
    queue_.pop();
    return nextEvent;
}

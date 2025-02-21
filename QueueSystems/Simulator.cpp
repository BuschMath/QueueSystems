#include "Simulator.h"
#include <iostream>
#include <limits>

Simulator::Simulator()
    : currentTime_(0.0) {
}

Simulator::~Simulator() {
    // The eventQueue_ destructor will clean up any remaining events.
}

void Simulator::scheduleEvent(Event* event) {
    eventQueue_.scheduleEvent(event);
}

double Simulator::getCurrentTime() const {
    return currentTime_;
}

void Simulator::run(double endTime) {
    // Process events until the event queue is empty or currentTime exceeds endTime.
    while (!eventQueue_.isEmpty() && currentTime_ <= endTime) {
        // Retrieve the next event.
        Event* event = eventQueue_.popNextEvent();
        // Update simulation time to the time of the event.
        currentTime_ = event->getTime();

        // Optionally, print out debug information.
        std::cout << "Simulator time: " << currentTime_ << std::endl;

        // Execute the event.
        event->execute();

        // Clean up the event after execution.
        delete event;
    }
    std::cout << "Simulation finished at time " << currentTime_ << std::endl;
}

void Simulator::setCurrentTime(double time) {
    currentTime_ = time;
}

bool Simulator::isEmpty() const {
    return eventQueue_.isEmpty();
}

Event* Simulator::popNextEvent() {
    return eventQueue_.popNextEvent();
}
#include "ArrivalEvent.h"
#include <iostream>

/**
 * @brief Constructor for ArrivalEvent.
 *
 * Initializes the event time and stores the pointer to the QueueSystem.
 *
 * @param eventTime The simulation time when the arrival occurs.
 * @param qs Pointer to the QueueSystem affected by the arrival.
 */
ArrivalEvent::ArrivalEvent(double eventTime, QueueSystem* qs)
    : Event(eventTime), queueSystem_(qs) {}

/**
 * @brief Destructor for ArrivalEvent.
 */
ArrivalEvent::~ArrivalEvent() {
    // No dynamic memory allocated here.
}

/**
 * @brief Execute the arrival event.
 *
 * This method invokes processArrival() on the associated QueueSystem using the event's time.
 */
void ArrivalEvent::execute() {
    // For debugging or tracing, you might print the event details.
    std::cout << "Executing ArrivalEvent at time " << time << std::endl;
    if (queueSystem_) {
        queueSystem_->processArrival(time);
    }
    // Optionally, schedule the next arrival event here using your simulation engine.
}

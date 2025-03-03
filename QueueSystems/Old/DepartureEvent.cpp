#include "DepartureEvent.h"
#include <iostream>

/**
 * @brief Constructor for DepartureEvent.
 *
 * Initializes the event time and stores the pointer to the QueueSystem.
 *
 * @param eventTime The simulation time when the departure occurs.
 * @param qs Pointer to the QueueSystem affected by the departure.
 */
DepartureEvent::DepartureEvent(double eventTime, QueueSystem* qs)
    : Event(eventTime), queueSystem_(qs) {}

/**
 * @brief Destructor for DepartureEvent.
 */
DepartureEvent::~DepartureEvent() {
    // No dynamic memory allocated here.
}

/**
 * @brief Execute the departure event.
 *
 * This method invokes processDeparture() on the associated QueueSystem using the event's time.
 */
void DepartureEvent::execute() {
    std::cout << "Executing DepartureEvent at time " << time << std::endl;
    if (queueSystem_) {
        queueSystem_->processDeparture(time);
    }
    // Optionally, additional logic could be added here (e.g., scheduling the next departure).
}

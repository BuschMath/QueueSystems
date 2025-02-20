#ifndef DEPARTUREEVENT_H
#define DEPARTUREEVENT_H

#include "Event.h"
#include "QueueSystem.h"

/**
 * @file DepartureEvent.h
 * @brief Represents a customer departure event in the simulation.
 *
 * When executed, this event calls the processDeparture() method of the associated
 * QueueSystem, updating the system state (such as reducing the customer count).
 */
class DepartureEvent : public Event {
public:
    /**
     * @brief Constructor for a DepartureEvent.
     *
     * @param eventTime The simulation time when this departure occurs.
     * @param qs Pointer to the QueueSystem that this event affects.
     */
    DepartureEvent(double eventTime, QueueSystem* qs);

    /**
     * @brief Destructor.
     */
    virtual ~DepartureEvent();

    /**
     * @brief Execute the departure event.
     *
     * Calls the processDeparture() method of the associated QueueSystem.
     */
    virtual void execute() override;

private:
    QueueSystem* queueSystem_; ///< Pointer to the QueueSystem that processes this departure.
};

#endif // DEPARTUREEVENT_H


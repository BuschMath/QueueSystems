#ifndef ARRIVALEVENT_H
#define ARRIVALEVENT_H

#include "Event.h"
#include "QueueSystem.h"

/**
 * @file ArrivalEvent.h
 * @brief Represents a customer arrival event in the simulation.
 *
 * When executed, this event calls the processArrival() method of the associated
 * QueueSystem, updating the system state. Additional functionality, such as scheduling
 * the next arrival, can be integrated within the execute() method.
 */
class ArrivalEvent : public Event {
public:
    /**
     * @brief Constructor for an ArrivalEvent.
     *
     * @param eventTime The simulation time when this arrival occurs.
     * @param qs Pointer to the QueueSystem that this event affects.
     */
    ArrivalEvent(double eventTime, QueueSystem* qs);

    /**
     * @brief Destructor.
     */
    virtual ~ArrivalEvent();

    /**
     * @brief Execute the arrival event.
     *
     * Calls the processArrival() method of the associated QueueSystem.
     */
    virtual void execute() override;

private:
    QueueSystem* queueSystem_; ///< Pointer to the QueueSystem that processes this arrival.
};

#endif // ARRIVALEVENT_H


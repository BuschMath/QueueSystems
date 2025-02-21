#ifndef EVENTTARGET_H
#define EVENTTARGET_H

/**
 * @file EventTarget.h
 * @brief Abstract interface for objects that can process simulation events.
 *
 * This interface defines the methods required by simulation events (such as arrivals and departures).
 * Any system that can receive simulation events (like our MM1Queue) should implement this interface.
 */
class EventTarget {
public:
    virtual ~EventTarget() {}

    /**
     * @brief Process a customer arrival event at the given simulation time.
     * @param currentTime The simulation time when the arrival occurs.
     */
    virtual void processArrival(double currentTime) = 0;

    /**
     * @brief Process a customer departure event at the given simulation time.
     * @param currentTime The simulation time when the departure occurs.
     */
    virtual void processDeparture(double currentTime) = 0;
};

#endif // EVENTTARGET_H

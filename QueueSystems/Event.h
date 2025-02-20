#ifndef EVENT_H
#define EVENT_H

/**
 * @file Event.h
 * @brief Abstract base class for simulation events.
 *
 * This class defines the interface for simulation events. Each event is associated with
 * a simulation time (the time at which it should be executed) and must implement the
 * execute() method to update the system state.
 */
class Event {
public:
    /**
     * @brief Constructor.
     *
     * @param eventTime The simulation time at which this event is scheduled.
     */
    Event(double eventTime) : time(eventTime) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~Event() {}

    /**
     * @brief Execute the event.
     *
     * This pure virtual function must be overridden in derived classes to perform the
     * specific action associated with the event.
     */
    virtual void execute() = 0;

    /**
     * @brief Get the scheduled time for the event.
     *
     * @return double The simulation time when the event is scheduled.
     */
    double getTime() const { return time; }

protected:
    double time; ///< The simulation time at which the event occurs.
};

/**
 * @brief Comparator for Event pointers.
 *
 * This functor orders events by their scheduled time in ascending order.
 * It is useful when using a priority queue to manage simulation events.
 */
struct EventComparator {
    bool operator()(const Event* a, const Event* b) const {
        return a->getTime() > b->getTime(); // lower time has higher priority
    }
};

#endif // EVENT_H


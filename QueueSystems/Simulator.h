#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "EventQueue.h"

/**
 * @file Simulator.h
 * @brief Class for running the simulation.
 *
 * The Simulator class maintains the simulation clock and processes events
 * in time order using an EventQueue.
 */
class Simulator {
public:
    /**
     * @brief Constructor.
     */
    Simulator();

    /**
     * @brief Destructor.
     */
    ~Simulator();

    /**
     * @brief Schedule an event in the simulation.
     *
     * @param event Pointer to the Event to schedule.
     */
    void scheduleEvent(Event* event);

    /**
     * @brief Run the simulation.
     *
     * Processes events in order until the event queue is empty or until
     * a specified end time is reached.
     *
     * @param endTime Optional simulation end time (default is infinity).
     */
    void run(double endTime = 1e12);

    /**
     * @brief Get the current simulation time.
     *
     * @return double The current simulation time.
     */
    double getCurrentTime() const;

    /**
     * @brief Set the current simulation time.
     *
     * @param time The new simulation time.
     */
    void setCurrentTime(double time);

    /**
     * @brief Check whether the event queue is empty.
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
    double currentTime_; ///< Current simulation time.
    EventQueue eventQueue_; ///< The priority queue holding simulation events.
};

#endif // SIMULATOR_H


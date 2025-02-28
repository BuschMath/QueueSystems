#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include <vector>
#include <memory>
#include <limits>

// Forward declaration of Simulation is required for the Event class.
class Simulation;

//----------------------------------------------------------------
// Event Base Class
//----------------------------------------------------------------
class Event {
public:
    double eventTime;  // Scheduled simulation time for the event

    // Constructor that sets the event time.
    Event(double time) : eventTime(time) {}

    // Virtual destructor to ensure derived classes clean up properly.
    virtual ~Event() {}

    // Pure virtual function to process the event.
    virtual void process(Simulation& sim) = 0;
};

//----------------------------------------------------------------
// Comparator for the event priority queue (min-heap based on eventTime)
//----------------------------------------------------------------
struct EventComparator {
    bool operator()(const std::shared_ptr<Event>& e1, const std::shared_ptr<Event>& e2) {
        // The event with the smaller time has higher priority.
        return e1->eventTime > e2->eventTime;
    }
};

//----------------------------------------------------------------
// Simulation Engine Class
//----------------------------------------------------------------
class Simulation {
private:
    double currentTime;  // Current simulation time.
    bool running;        // Flag indicating whether the simulation is running.

    // Priority queue to store events in order of their scheduled time.
    std::priority_queue<
        std::shared_ptr<Event>,
        std::vector<std::shared_ptr<Event>>,
        EventComparator
    > eventQueue;

public:
    // Constructor initializes simulation time to zero.
    Simulation() : currentTime(0.0), running(false) {}

    // Returns the current simulation time.
    double getCurrentTime() const {
        return currentTime;
    }

    // Schedule a new event by adding it to the event queue.
    void scheduleEvent(const std::shared_ptr<Event>& event) {
        eventQueue.push(event);
    }

    // Run the simulation until no events remain or until the specified end time is reached.
    void run(double endTime = std::numeric_limits<double>::infinity()) {
        running = true;
        while (!eventQueue.empty() && running) {
            auto event = eventQueue.top();
            if (event->eventTime > endTime)
                break;  // Stop if the next event is beyond the simulation end time.
            eventQueue.pop();
            currentTime = event->eventTime;  // Advance simulation time.
            event->process(*this);           // Process the event.
        }
    }

    // Stop the simulation externally.
    void stop() {
        running = false;
    }
};

#endif // SIMULATION_H



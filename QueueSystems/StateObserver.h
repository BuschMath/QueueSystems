#ifndef STATE_OBSERVER_H
#define STATE_OBSERVER_H

// A simple structure to hold state data.
struct StateData {
    double time;
    int state; // For example, number in a queue.
};

// Observer interface that can receive state updates.
class StateObserver {
public:
    virtual ~StateObserver() {}
    virtual void update(const StateData& data) = 0;
};

#endif // STATE_OBSERVER_H


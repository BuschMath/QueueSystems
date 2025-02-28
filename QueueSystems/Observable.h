#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "StateObserver.h"
#include <vector>
#include <algorithm>

// Mixin class that enables an object to be observed.
class Observable {
public:
    virtual ~Observable() {}

    // Must be implemented by the observable subject.
    virtual int getState() const = 0;

    // Attach an observer.
    void attach(StateObserver* observer) {
        observers.push_back(observer);
    }

    // Detach an observer.
    void detach(StateObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // Notify all attached observers with the current state and time.
    void notifyObservers(double time) {
        StateData data{ time, getState() };
        for (auto observer : observers) {
            observer->update(data);
        }
    }

private:
    std::vector<StateObserver*> observers;
};

#endif // OBSERVABLE_H


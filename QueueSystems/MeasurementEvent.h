#ifndef MEASUREMENT_EVENT_H
#define MEASUREMENT_EVENT_H

#include "Simulation.h"
#include "Observable.h"
#include <memory>

class MeasurementEvent : public Event {
public:
    MeasurementEvent(double time, Observable* observable, double interval)
        : Event(time), observable(observable), sampleInterval(interval) {}

    virtual void process(Simulation& sim) override {
        double currentTime = sim.getCurrentTime();
        // Notify observers with the current state.
        observable->notifyObservers(currentTime);

        // Schedule the next measurement.
        double nextTime = currentTime + sampleInterval;
        sim.scheduleEvent(std::make_shared<MeasurementEvent>(nextTime, observable, sampleInterval));
    }

private:
    Observable* observable;
    double sampleInterval;
};

#endif // MEASUREMENT_EVENT_H


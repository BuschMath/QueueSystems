#ifndef STATE_LOGGER_H
#define STATE_LOGGER_H

#include "StateObserver.h"
#include <vector>

class StateLogger : public StateObserver {
public:
    // Log the received state update.
    virtual void update(const StateData& data) override {
        log.push_back(data);
    }

    // Retrieve the collected state log.
    const std::vector<StateData>& getLog() const {
        return log;
    }

private:
    std::vector<StateData> log;
};

#endif // STATE_LOGGER_H


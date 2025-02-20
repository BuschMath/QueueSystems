#include "QueueSystem.h"

/**
 * @brief Virtual destructor for QueueSystem.
 *
 * Although no resources are directly managed by the base class,
 * this destructor ensures that derived class destructors are called.
 */
QueueSystem::~QueueSystem() {
    // No specific cleanup required in base class.
}

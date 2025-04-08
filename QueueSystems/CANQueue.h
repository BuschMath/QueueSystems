#ifndef CAN_QUEUE_H 
#define CAN_QUEUE_H

#include "MMSQueue.h" 
#include "QueueEvents.h" // for the event types 
#include <memory>

// CANQueue expands on the MMSQueue model by incorporating: 
// 1) A finite capacity (maxCapacity) for the number of customers. 
// 2) Downstream blocking: if a downstream queue is full, a customer completing service is held. 
// 3) Suspension of starting new service while holding a customer. 
class CANQueue : public MMSQueue
{
public: // Constructor: takes the simulation engine, arrival rate, service rate, number of servers, 
	// and the finite capacity for the queue. 
	CANQueue(Simulation& sim, double arrivalRate, double serviceRate, int servers, int capacity);

	// Override arrival and departure handlers.
	virtual void handleExternalArrival(Simulation& sim) override;
	virtual void handleInternalArrival(Simulation& sim) override;
	virtual void handleDeparture(Simulation& sim) override;

	// Attempt to forward a held customer to the downstream queue.
	// This method should be called (or scheduled) when it is believed that the downstream queue may have freed space.
	void attemptForward(Simulation& sim);

	// Set (or change) the downstream queue pointer.
	void setDownstream(CANQueue* downstreamQueue);

	// Return true if this queue is full (i.e. state has reached maxCapacity).
	bool isFull() const;

	// (Inherited getState() returns the number of customers in the system.)
private:
	int maxCapacity; // Maximum number of customers the queue can hold. 
	bool blocked; // True if a finished customer is currently held waiting for the downstream queue. 
	CANQueue* downstream; // Pointer to the downstream queue; may be nullptr if not set. };
};
#endif // CAN_QUEUE_H
#include "CANQueue.h" 
#include <limits> 
#include <iostream> // Optional: for logging (can be removed if not desired)

// A small forwarding delay constant (can also be defined in a common header) 
static const double forwardDelay = 0.01;

CANQueue::CANQueue(Simulation& sim, double arrivalRate, double serviceRate, int servers, int capacity)
	: MMSQueue(sim, arrivalRate, serviceRate, servers), maxCapacity(capacity), blocked(false), downstream(nullptr) 
{ 
	// Note: The base class MMSQueue initializes metrics and distributions. 
}

bool CANQueue::isFull() const 
{ 
	// Use getState() from the base class (which returns the current count) 
	return (this->getState() >= maxCapacity); 
}

void CANQueue::setDownstream(CANQueue* downstreamQueue) 
{ 
	downstream = downstreamQueue; 
}

void CANQueue::handleExternalArrival(Simulation& sim)
{
	double currentTime = sim.getCurrentTime();
	// Reject arrival if capacity is reached.
	if (this->getState() >= maxCapacity) {
		// (Optional logging:)
		// std::cout << "External arrival rejected at time " << currentTime << " (queue full)." << std::endl; 
		return;
	}

	updateMetrics(currentTime);
	totalArrivals++;
	numInSystem++;

	// Only start new service if the queue is not blocked.
	if (!blocked && busyServers < servers) {
		busyServers++;
		double departureTime = currentTime + serviceDist(rng);
		sim.scheduleEvent(std::make_shared<GenericDepartureEvent>(departureTime, this));
	}

	// Schedule the next external arrival (even if this arrival was rejected, new arrivals may come later).
	double nextArrivalTime = currentTime + getNextInterarrivalTime();
	if (std::isfinite(nextArrivalTime)) {
		sim.scheduleEvent(std::make_shared<ExternalArrivalEvent>(nextArrivalTime, this));
	}
}

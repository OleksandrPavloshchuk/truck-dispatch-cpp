/**
 * output-events.hpp
 */
 
#pragma once

#include "domain.hpp"

struct TruckWaitsOutputEvent {
	const Truck truck_;
		
	TruckWaitsOutputEvent(const Truck &truck) : 
		truck_(truck) {}
};

struct ShipmentWaitsOutputEvent {
	const Shipment shipment_;
		
	ShipmentWaitsOutputEvent(const Shipment &shipment) : 
		shipment_(shipment) {}
};

struct AssignmentCreatedOutputEvent {
	const Assignment assignment_;
	
	AssignmentCreatedOutputEvent(const Assignment &assignment) : 
		assignment_(assignment) {}
};

/**
 * output-events.hpp
 */
 
#pragma once

#include "domain.hpp"

struct TruckWaitsOutputEvent {
	const Truck truck;
		
	TruckWaitsOutputEvent(const Truck &truck) : 
		truck(truck) {}
};

struct ShipmentWaitsOutputEvent {
	const Shipment shipment;
		
	ShipmentWaitsOutputEvent(const Shipment &shipment) : 
		shipment(shipment) {}
};

struct AssignmentCreatedOutputEvent {
	const Assignment assignment;
	
	AssignmentCreatedOutputEvent(const Assignment &assignment) : 
		assignment(assignment) {}
};

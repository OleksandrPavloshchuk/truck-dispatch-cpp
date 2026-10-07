/**
 * input-events.hpp
 */
 
#pragma once

#include "domain.hpp"

struct TruckArrivedInputEvent {
	const Truck truck;
		
	TruckArrivedInputEvent(const Truck &truck) : 
		truck(truck) {}
};

struct ShipmentArrivedInputEvent {
	const Shipment shipment;
		
	ShipmentArrivedInputEvent(const Shipment &shipment) : 
		shipment(shipment) {}
};

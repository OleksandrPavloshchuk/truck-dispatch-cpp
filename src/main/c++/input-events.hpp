/**
 * input-events.hpp
 */
 
#pragma once

#include "domain.hpp"

struct TruckArrivedInputEvent {
	const Truck truck_;
		
	TruckArrivedInputEvent(const Truck &truck) : 
		truck_(truck) {}
};

struct ShipmentArrivedInputEvent {
	const Shipment shipment_;
		
	ShipmentArrivedInputEvent(const Shipment &shipment) : 
		shipment_(shipment) {}
};

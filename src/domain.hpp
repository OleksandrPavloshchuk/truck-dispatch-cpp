/**
 * domain.hpp
 */
 
#pragma once

#include <string>

struct Truck {
	const std::string name;
	const float capacity;
	
	Truck(
		const std::string &name, 
		const float capacity
	): 
		name(name), 
		capacity(capacity) {}
};

struct Shipment {
	const std::string name;
	const float weight;
	
	Shipment(
		const std::string &name, 
		const float weight
	): 
		name(name), 
		weight(weight) {}
};

struct Assignment {
	const Truck truck;
	const Shipment shipment;
	
	Assignment(
		const Truck &truck,
		const Shipment &shipment
	) :
		 truck(truck),
		 shipment(shipment) {}
};

/**
 * domain.hpp
 */
 
#pragma once

#include <string>

struct Truck {
	const std::string name_;
	const double capacity_;
	
	Truck(
		const std::string &name, 
		const double capacity
	): 
		name_(name), 
		capacity_(capacity) {}
};

struct Shipment {
	const std::string name_;
	const double weight_;
	
	Shipment(
		const std::string &name, 
		const double weight
	): 
		name_(name), 
		weight_(weight) {}
};

struct Assignment {
	const Truck truck_;
	const Shipment shipment_;
	
	Assignment(
		const Truck &truck,
		const Shipment &shipment
	) :
		 truck_(truck),
		 shipment_(shipment) {}
};

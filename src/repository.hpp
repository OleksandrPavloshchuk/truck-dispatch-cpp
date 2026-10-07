/**
 * repository.hpp
 */
 
#pragma once

#include <optional>
#include "domain.hpp"

class Repository {
public:
	virtual void addTruck(const Truck &truck) = 0;
	virtual void addShipment(const Truck &shipment) = 0;
	virtual std::optional<Truck> getLightestTruckForWeight(const double weight) = 0;
	virtual std::optional<Truck> getHeaviestShipmentForCapacity(const double capacity) = 0;
};

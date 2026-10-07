/**
 * repository.hpp
 */
 
#pragma once

#include <optional>
#include "domain.hpp"

class Repository {
public:
	virtual bool addTruck(const Truck &truck) = 0;
	virtual bool addShipment(const Shipment &shipment) = 0;
	virtual std::optional<Truck> getLightestTruckForWeight(const double weight) = 0;
	virtual std::optional<Shipment> getHeaviestShipmentForCapacity(const double capacity) = 0;
};

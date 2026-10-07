/**
 * in-memory-repository.hpp
 */
 
#pragma once

#include <vector>
#include <string>
#include "repository.hpp"

class InMemoryRepository : public Repository {
public:
	bool addTruck(const Truck &truck);
	bool addShipment(const Shipment &shipment);
	std::optional<Truck> getLightestTruckForWeight(const double weight);
	std::optional<Shipment> getHeaviestShipmentForCapacity(const double capacity);
	
private:
	std::vector<Truck> trucks;
	std::vector<Shipment> shipments;
	
};

/**
 * repository.hpp
 */
 
#pragma once

#include <string>
#include <functional>
#include "../domain.hpp"

using OnSuccessAdd = std::function<void()>;
using OnError = std::function<void(const std::string&)>;


class Repository {
public:
	virtual ~Repository() = default;
	virtual void addTruck(const Truck &truck, OnSuccessAdd onSuccessAdd, OnError onError) = 0;
/*
	virtual bool addTruck(const Truck &truck) = 0;
	virtual bool addShipment(const Shipment &shipment) = 0;
	virtual void addAssignment(const Assignment &assignment) = 0;
	virtual std::optional<Truck> getLightestTruckForWeight(const double weight) = 0;
	virtual std::optional<Shipment> getHeaviestShipmentForCapacity(const double capacity) = 0;
*/
};

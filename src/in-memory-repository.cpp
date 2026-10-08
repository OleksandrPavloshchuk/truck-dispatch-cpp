/**
 * in-memory-repository.cpp
 */

#include <algorithm>
#include "in-memory-repository.hpp"

template <typename T> bool sameName(const T &a, const T &b) {
	return b.name == a.name;
}

template <typename T> bool addIfAbsents(std::vector<T> &vector, const T &val) {
	if (std::ranges::any_of(vector, [&val](const auto& existing) { return sameName(val, existing); })) {
		return false;
	}
	vector.push_back(val);
	return true;
}

bool InMemoryRepository::addTruck(const Truck &truck) {
	return addIfAbsents(trucks, truck);
}

bool InMemoryRepository::addShipment(const Shipment &shipment) {
	return addIfAbsents(shipments, shipment);
}

void InMemoryRepository::addAssignment(const Assignment &assignment) {
	assignments.push_back(assignment);
}

std::optional<Truck> InMemoryRepository::getLightestTruckForWeight(const double weight) {
	std::optional<Truck> result;
	
	for (const auto &truck : trucks) {
		if (isBusy(truck)) {
			continue;
		}
		if (truck.capacity < weight) {
			continue;
		}
		if (!result || truck.capacity < result->capacity) {
			result.emplace(truck);
		}
	} 
	return result;
}

std::optional<Shipment> InMemoryRepository::getHeaviestShipmentForCapacity(const double capacity) {
	std::optional<Shipment> result;
	for (const auto &shipment : shipments) {
		if (isBusy(shipment)) {
			continue;
		}
		if (shipment.weight > capacity) {
			continue;
		}
		if (!result || shipment.weight > result->weight) {
			result.emplace(shipment);
		}
	} 
	return result;
}

bool InMemoryRepository::isBusy(const Truck &truck) {
	for (const auto &assignment : assignments) {
		if (assignment.truck.name == truck.name) {
			return true;
		}
	}
	return false;
}

bool InMemoryRepository::isBusy(const Shipment &shipment) {
	for (const auto &assignment : assignments) {
		if (assignment.shipment.name == shipment.name) {
			return true;
		}
	}
	return false;
}


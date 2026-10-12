/**
 * repository.hpp
 */
 
#pragma once
 
#include "../../src/repository/repository.hpp"


class MockRepository : public Repository {
public:
	void addTruck(const Truck &truck, OnSuccessAdd onSuccessAdd, OnError onError) {}
	void addShipment(const Shipment &shipment, OnSuccessAdd onSuccessAdd, OnError onError) {}
	void addAssignment(const Assignment &assignment, OnSuccessAdd onSuccessAdd, OnError onError) {}
	void getLightestTruckForWeight(const double weight, OnSuccessGetTruck onSuccessGetTruck, OnError onError) {}
	void getHeaviestShipmentForCapacity(const double capacity, OnSuccessGetShipment onSuccessGetShipment, OnError onError) {}
};

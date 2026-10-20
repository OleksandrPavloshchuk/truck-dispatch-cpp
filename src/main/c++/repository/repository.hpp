/**
 * repository.hpp
 */
 
#pragma once

#include <string>
#include <functional>
#include <optional>
#include "../domain.hpp"

using OnSuccessAdd = std::function<void()>;
using OnError = std::function<void(const std::string&)>;
using OnSuccessGetTruck = std::function<void(std::optional<Truck>)>;
using OnSuccessGetShipment = std::function<void(std::optional<Shipment>)>;

struct DatabaseMetrics {
	DatabaseMetrics(
		std::int64_t shipmentsTotal,
		std::int64_t trucksTotal,
		std::int64_t assignmentsTotal): 
			shipmentsTotal_(shipmentsTotal),
			trucksTotal_(trucksTotal),
			assignmentsTotal_(assignmentsTotal) {}
			
	const std::int64_t shipmentsTotal_;
	const std::int64_t trucksTotal_;
	const std::int64_t assignmentsTotal_;
};

using OnSuccessGetDatabaseMetrics = std::function<void(const DatabaseMetrics&)>;

class Repository {
public:
	virtual ~Repository() = default;
	virtual void addTruck(const Truck &truck, OnSuccessAdd onSuccessAdd, OnError onError) = 0;
	virtual void addShipment(const Shipment &shipment, OnSuccessAdd onSuccessAdd, OnError onError) = 0;
	virtual void addAssignment(const Assignment &assignment, OnSuccessAdd onSuccessAdd, OnError onError) = 0;
	virtual void getLightestTruckForWeight(const double weight, OnSuccessGetTruck onSuccessGetTruck, OnError onError) = 0;
	virtual void getHeaviestShipmentForCapacity(const double capacity, OnSuccessGetShipment onSuccessGetShipment, OnError onError) = 0;
	virtual void getDatabaseMetrics(OnSuccessGetDatabaseMetrics onSuccessGetDatabaseMetrics, OnError onError) = 0;
};

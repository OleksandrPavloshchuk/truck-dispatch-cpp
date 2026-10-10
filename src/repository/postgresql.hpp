/**
 * repositorysql.hpp
 */
 
#pragma once

#include <vector>
#include <string>
#include <drogon/orm/DbClient.h>
#include "repository.hpp"

class PostgresqlRepository : public Repository {
public:
	PostgresqlRepository(std::shared_ptr<drogon::orm::DbClient> dbClient): dbClient() {}
	bool addTruck(const Truck &truck);
	bool addShipment(const Shipment &shipment);
	std::optional<Truck> getLightestTruckForWeight(const double weight);
	std::optional<Shipment> getHeaviestShipmentForCapacity(const double capacity);
	void addAssignment(const Assignment &assignment);
	
private:
	std::shared_ptr<drogon::orm::DbClient> dbClient;
};

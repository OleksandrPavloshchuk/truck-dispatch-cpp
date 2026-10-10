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
	
	void addTruck(const Truck &truck, OnSuccessAdd onSuccessAdd, OnError onError);
	void addShipment(const Shipment &shipment, OnSuccessAdd onSuccessAdd, OnError onError);
	void addAssignment(const Assignment &assignment, OnSuccessAdd onSuccessAdd, OnError onError);
	void getLightestTruckForWeight(const double weight, OnSuccessGetTruck onSuccessGetTruck, OnError onError);
	void getHeaviestShipmentForCapacity(const double capacity, OnSuccessGetShipment onSuccessGetShipment, OnError onError);
	
private:
	std::shared_ptr<drogon::orm::DbClient> dbClient;
	
};

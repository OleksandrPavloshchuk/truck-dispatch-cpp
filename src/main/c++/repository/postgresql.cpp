/**
 * postgresql.cpp
 */

#include <iostream>
#include "postgresql.hpp"

void PostgresqlRepository::addTruck(const Truck &truck, OnSuccessAdd onSuccessAdd, OnError onError) {

	dbClient_->execSqlAsync(
		"INSERT INTO trucks(name, capacity) VALUES ($1, $2)",
		[onSuccessAdd = std::move(onSuccessAdd)](const drogon::orm::Result&) {
			onSuccessAdd();
		},
		[onError = std::move(onError)](const drogon::orm::DrogonDbException&) {
			LOG_ERROR << "Can't add truck";
			// TODO return more complex object
			onError("Can't add truck");
		},
		truck.name_,
		truck.capacity_
	);
}

void PostgresqlRepository::addShipment(const Shipment &shipment, OnSuccessAdd onSuccessAdd, OnError onError) {
	dbClient_->execSqlAsync(
		"INSERT INTO shipments(name, weight) VALUES ($1, $2)",
		[onSuccessAdd = std::move(onSuccessAdd)](const drogon::orm::Result&) {
			onSuccessAdd();
		},
		[onError = std::move(onError)](const drogon::orm::DrogonDbException&) {
			LOG_ERROR << "Can't add shipment";
			// TODO return more complex object
			onError("Can't add shipment");
		},
		shipment.name_,
		shipment.weight_
	);		
}

void PostgresqlRepository::addAssignment(const Assignment &assignment, OnSuccessAdd onSuccessAdd, OnError onError) {
	dbClient_->execSqlAsync(
		"INSERT INTO assignments(truck_name, shipment_name) VALUES ($1, $2)",
		[onSuccessAdd = std::move(onSuccessAdd)](const drogon::orm::Result&) {
			onSuccessAdd();
		},
		[onError = std::move(onError)](const drogon::orm::DrogonDbException&) {
			LOG_ERROR << "Can't add assignment";
			// TODO return more complex object
			onError("Can't add assignment");
		},
		assignment.truck_.name_,
		assignment.shipment_.name_
	);			
}

void PostgresqlRepository::getLightestTruckForWeight(const double weight, OnSuccessGetTruck onSuccessGetTruck, OnError onError) {
	const std::string sql = R"(
	       	SELECT name, capacity FROM trucks
        	WHERE capacity in (SELECT min(capacity)
                FROM trucks
                WHERE capacity >= $1
                AND name NOT IN (SELECT truck_name FROM assignments))
                LIMIT 1
        )";
        dbClient_->execSqlAsync(sql,
        	[onSuccessGetTruck = std::move(onSuccessGetTruck)](const drogon::orm::Result &result) {
        		for (const auto& row : result) {
        			const Truck truck(row[0].as<std::string>(), row[1].as<double>());
	        		onSuccessGetTruck(truck);
        			return;
        		}
        		onSuccessGetTruck(std::nullopt);
        	},
		[onError = std::move(onError)](const drogon::orm::DrogonDbException&) {
			LOG_ERROR << "Can't select truck";
			// TODO return more complex object
			onError("Can't select truck");
		},
		weight
	);
}

void PostgresqlRepository::getHeaviestShipmentForCapacity(const double capacity, OnSuccessGetShipment onSuccessGetShipment, OnError onError) {
	const std::string sql = R"(
        	SELECT name, weight FROM shipments
        	WHERE weight in (SELECT max(weight)
               	FROM shipments
               	WHERE weight <= $1
              	AND name NOT IN (SELECT shipment_name FROM assignments))
        	LIMIT 1
        )";
        dbClient_->execSqlAsync(sql,
        	[onSuccessGetShipment = std::move(onSuccessGetShipment)](const drogon::orm::Result &result) {
        		for (const auto& row : result) {
        			const Shipment shipment(row[0].as<std::string>(), row[1].as<double>());
	        		onSuccessGetShipment(shipment);
        			return;
        		}
        		onSuccessGetShipment(std::nullopt);
        	},
		[onError = std::move(onError)](const drogon::orm::DrogonDbException&) {
			LOG_ERROR << "Can't select shipment";
			// TODO return more complex object
			onError("Can't select shipment");
		},
		capacity
	);	
}

void PostgresqlRepository::getDatabaseMetrics(OnSuccessGetDatabaseMetrics onSuccessGetDatabaseMetrics, OnError onError) {
	const std::string sql = R"(
        	SELECT 
		(SELECT count(*) FROM shipments) AS shipments_total
        )";
        dbClient_->execSqlAsync(sql,
        	[onSuccessGetDatabaseMetrics = std::move(onSuccessGetDatabaseMetrics)](const drogon::orm::Result &result) {
        		for (const auto& row : result) {
        			const DatabaseMetrics metrics(row[0].as<int64_t>());
        			onSuccessGetDatabaseMetrics(metrics);
        			return;
        		}
        	},
		[onError = std::move(onError)](const drogon::orm::DrogonDbException&) {
			LOG_ERROR << "Can't get database metrics";
			// TODO return more complex object
			onError("Can't get database metrics");
		}
	);		
	
	
}

/*

SELECT
    (SELECT count(*) FROM shipments) AS shipments_total,
    (SELECT count(*) FROM trucks) AS trucks_total;

*/



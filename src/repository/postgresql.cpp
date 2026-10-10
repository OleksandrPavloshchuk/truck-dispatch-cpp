/**
 * postgresql.cpp
 */

#include <iostream>
#include "postgresql.hpp"

void PostgresqlRepository::addTruck(const Truck &truck, OnSuccessAdd onSuccessAdd, OnError onError) {
	dbClient->execSqlAsync(
		"INSERT INTO trucks(name, capacity) VALUES ($1, $2)",
		[onSuccessAdd = std::move(onSuccessAdd)](const drogon::orm::Result&) {
			onSuccessAdd();
		},
		[onError = std::move(onError)](const drogon::orm::DrogonDbException&) {
			LOG_ERROR << "Can't add truck";
			// TODO return more complex object
			onError("Can't add truck");
		},
		truck.name,
		truck.capacity
	);	
}

/*
dbClient_->execSqlAsync(
    "UPDATE trucks SET status = $1 WHERE id = $2",
    [](const drogon::orm::Result& result) {
        // Запит виконано успішно
        const auto affectedRows = result.affectedRows();
    },
    [](const drogon::orm::DrogonDbException& error) {
        // Помилка виконання SQL
    },
    "available",
    truckId
);
*/

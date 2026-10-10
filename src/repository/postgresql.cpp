/**
 * postgresql.cpp
 */

#include <iostream>
#include "postgresql.hpp"

void PostgresqlRepository::addTruck(const Truck &truck, OnSuccessAdd &onSuccessAdd, OnError &onError) {
	// TODO	
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

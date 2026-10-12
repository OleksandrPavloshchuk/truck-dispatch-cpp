/**
 * main.cpp
 */
 
#include <memory>
#include <utility> 
#include <string>
#include <variant>
#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>

#include "config.hpp"
#include "repository/postgresql.hpp"
#include "service.hpp"
#include "controller/add-shipment.hpp"
#include "controller/add-truck.hpp"

std::shared_ptr<drogon::orm::DbClient> createDatabaseClient(const Config &config) {
	auto connectStr = "host=" + config.getDatabaseHost()
		+ " port=" + config.getDatabasePort()
		+ " dbname=" + config.getDatabase()
		+ " user=" + config.getDatabaseUser()
		+ " password=" + config.getDatabasePassword();
	return drogon::orm::DbClient::newPgClient(connectStr, 2);	
}

// Entry point:
int main() {

    	Config config;
	auto dbClient = createDatabaseClient(config);
	    	
	PostgresqlRepository repository(dbClient);
	Service service(repository);

	AddShipmentController addShipmentController(service);
	AddTruckController addTruckController(service);
	
	drogon::app()
    		.setFloatPrecisionInJson(3, "decimal");	
	
	drogon::app()
		.addListener("0.0.0.0", config.getHttpPort())
		.registerHandler("/td/shipment", 
			[&addShipmentController](const drogon::HttpRequestPtr& req, Callback &&callback) {			
				addShipmentController.handle(req, std::move(callback));		
			}
		)
		.registerHandler("/td/truck", 
			[&addTruckController](const drogon::HttpRequestPtr& req, Callback &&callback) {
				addTruckController.handle(req, std::move(callback));
			}
		)
		.run();

	return 0;
}

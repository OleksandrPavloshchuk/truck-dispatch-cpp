/**
 * main.cpp
 */
 
#include <iostream>
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
#include "controller/metrics.hpp"

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
	MetricsController metricsController(service);
	
	auto &app = drogon::app();
	
	app.setFloatPrecisionInJson(3, "decimal");	
	
	app
		.addListener(
			"0.0.0.0", 
			config.getHttpPort(),
			true,
			config.getSslCetrificatePath(),
			config.getSslKeyPath()
		)
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
		.registerHandler("/metrics", 
			[&metricsController](const drogon::HttpRequestPtr&, Callback &&callback) {
				metricsController.handle(std::move(callback));
			}
		);
	
	std::cout << "Truck Dispatch application is started and accept requests on port " << config.getHttpPort() << std::endl;
	
		
	app.run();

	std::cout << "Truck Dispatch application shutdown" << std::endl;
	
	return 0;
}

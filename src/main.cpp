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
		
	dbClient->execSqlAsync(
        	"SELECT current_database(), current_user",
       	 	[](const drogon::orm::Result& result) {
            	for (const auto& row : result) {
                	LOG_INFO << "Database: "
                         	<< row[0].as<std::string>()
                         	<< ", user: "
                         	<< row[1].as<std::string>();
    	        	}
    	    	},
    	    	[](const std::exception_ptr& e) {
    	        	try {
    	        	    if (e) {
    	        	        std::rethrow_exception(e);
    	        	    }
    	        	} catch (const std::exception& ex) {
                		LOG_ERROR << "Database query failed: " << ex.what();
    	        	}
    	    	}
    	);
    	
	PostgresqlRepository repository(dbClient);
	Service service(repository);

	AddShipmentController addShipmentController(service);
	AddTruckController addTruckController(service);
	
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

/**
 * main.cpp
 */
 
#include <string>
#include <variant>
#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>

#include "repository/in-memory.hpp"
#include "service.hpp"
#include "controller/add-shipment.hpp"
#include "controller/add-truck.hpp"

// Get required parameter from configuration:
std::string getRequiredEnv(const char *name) {
    const char *value = std::getenv(name);
    if (value == nullptr || *value == '\0') {
        throw std::runtime_error(
            std::string("Required environment variable is not set: ") + name
        );
    }
    return value;
}

// Entry point:
int main() {

	auto connectStr = "host=" + getRequiredEnv("DB_HOST")
		+ " port=" + getRequiredEnv("DB_PORT")
		+ " dbname=" + getRequiredEnv("DB_DATABASE")
		+ " user=" + getRequiredEnv("DB_USER")
		+ " password=" + getRequiredEnv("DB_PASSWORD");
		
	auto dbClient = drogon::orm::DbClient::newPgClient(connectStr, 2);
		
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

	const int port = std::stoi(getRequiredEnv("HTTP_PORT"));
	
	InMemoryRepository repository;
	Service service(repository);

	AddShipmentController addShipmentController(service);
	AddTruckController addTruckController(service);
	
	drogon::app()
		.addListener("0.0.0.0", port)
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

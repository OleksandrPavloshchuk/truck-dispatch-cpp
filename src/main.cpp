/**
 * main.cpp
 */
 
#include <string>
#include <iostream>
#include <variant>
#include <drogon/drogon.h>

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

	const int port = std::stoi(getRequiredEnv("HTTP_PORT"));
	
	std::cout << "Configuration:" << std::endl;
	std::cout << "\tHTTP port: " << port << std::endl;
	
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

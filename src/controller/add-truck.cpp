/**
 * add-truck-controller.cpp
 */
 
#include "add-truck.hpp"

bool AddTruckController::validate(const Json::Value &json) {
	return json.isMember("name") 
		&& json["name"].isString() 
		&& json.isMember("capacity") 
		&& json["capacity"].isNumeric();
}

void AddTruckController::doHandle(const Json::Value &src, Callback &callback) {
	const Truck truck(src["name"].asString(), src["capacity"].asDouble());
	service.onTruckArrived(truck,
		[this, truck, callback](std::variant<TruckWaitsOutputEvent, AssignmentCreatedOutputEvent> result) {
			std::visit(EventHandler{callback, *this}, result);			
		},
		[this, callback](const std::string &error) {
			conflict(error, callback);
		}
	);	
}

Json::Value AddTruckController::toJson(const TruckWaitsOutputEvent &event) {
	Json::Value result;
        result["type"] = "truckWaits";
        result["truck"] = toJson(event.truck);
        return result;		
}

Json::Value AddTruckController::toJson(const TruckDuplicateOutputEvent &event) {
	Json::Value result;
        result["type"] = "truckDuplicate";
        result["truck"] = toJson(event.truck);
        return result;		
}

void AddTruckController::EventHandler::operator()(const TruckWaitsOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(controller.toJson(event)));
}

void AddTruckController::EventHandler::operator()(const TruckDuplicateOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(controller.toJson(event)));
}

void AddTruckController::EventHandler::operator()(const AssignmentCreatedOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(controller.toJson(event)));
}

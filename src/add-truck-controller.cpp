/**
 * add-truck-controller.cpp
 */
 
#include "add-truck-controller.hpp"

bool AddTruckController::validate(const Json::Value &json) {
	return json.isMember("name") 
		&& json["name"].isString() 
		&& json.isMember("capacity") 
		&& json["capacity"].isNumeric();
}

void AddTruckController::doHandle(const Json::Value &src, Callback &callback) {
	const Truck truck(src["name"].asString(), src["capacity"].asDouble());
	std::visit(
		EventHandler{callback},
		service.onTruckArrived(truck)
	);
}

Json::Value AddTruckController::toJson(const TruckWaitsOutputEvent &event) {
	Json::Value result;
        result["type"] = "truckWaits";
        result["truck"] = toJson(event.truck);
        return result;		
}

void AddTruckController::EventHandler::operator()(const TruckWaitsOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(AddTruckController::toJson(event)));
}

void AddTruckController::EventHandler::operator()(const AssignmentCreatedOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(Controller::toJson(event)));
}

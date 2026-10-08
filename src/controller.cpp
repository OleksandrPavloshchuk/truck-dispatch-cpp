/**
 * controller.cpp
 */
 
#include "controller.hpp"

void Controller::handle(const drogon::HttpRequestPtr& request, Callback &&callback) {
	auto json = request->getJsonObject();
	if (!json) {
		invalidJson(callback);
		return;
        }
	const auto& body = *json;
	if (!validate(body)) {
		invalidInput(callback);
		return;
	}
	doHandle(body, callback); 
}

void Controller::invalidJson(Callback &callback) {
	auto response = drogon::HttpResponse::newHttpJsonResponse(Json::Value{{"error", "Invalid JSON"}});
	response->setStatusCode(drogon::k400BadRequest);
	callback(response);
}

void Controller::invalidInput(Callback &callback) {
	auto response = drogon::HttpResponse::newHttpJsonResponse(Json::Value{{"error", "Invalid value"}});
        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
}

Json::Value Controller::toJson(const Assignment &assignment) {
	Json::Value result;
	result["truck"] = toJson(assignment.truck);
	result["shipment"] = toJson(assignment.shipment);
	return result;
}

Json::Value Controller::toJson(const Truck &truck) {
	Json::Value result;
        result["name"] = truck.name;
        result["capacity"] = truck.capacity;
        return result;
}

Json::Value Controller::toJson(const Shipment &shipment) {
	Json::Value result;
        result["name"] = shipment.name;
        result["weight"] = shipment.weight;
        return result;	
}

Json::Value Controller::toJson(const AssignmentCreatedOutputEvent &event) {
	Json::Value result;
        result["type"] = "assignmentCreated";
        result["assignment"] = toJson(event.assignment);
        return result;		
}

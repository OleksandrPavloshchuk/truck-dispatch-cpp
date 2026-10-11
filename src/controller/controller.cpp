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

void Controller::conflict(const std::string &error, const Callback &callback) {
	Json::Value body(Json::objectValue);
    	body["error"] = error;
	auto response = drogon::HttpResponse::newHttpJsonResponse(body);
        response->setStatusCode(drogon::k409Conflict);
        callback(response);
}

Json::Value Controller::toJson(const Assignment &assignment) {
	Json::Value result;
	result["truck"] = toJson(assignment.truck_);
	result["shipment"] = toJson(assignment.shipment_);
	return result;
}

Json::Value Controller::toJson(const Truck &truck) {
	Json::Value result;
        result["name"] = truck.name_;
        result["capacity"] = truck.capacity_;
        return result;
}

Json::Value Controller::toJson(const Shipment &shipment) {
	Json::Value result;
        result["name"] = shipment.name_;
        result["weight"] = shipment.weight_;
        return result;	
}

Json::Value Controller::toJson(const AssignmentCreatedOutputEvent &event) {
	Json::Value result;
        result["type"] = "assignmentCreated";
        result["assignment"] = toJson(event.assignment_);
        return result;		
}

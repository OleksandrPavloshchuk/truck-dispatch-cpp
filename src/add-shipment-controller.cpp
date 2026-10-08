/**
 * add-shipment-controller.cpp
 */
 
#include "add-shipment-controller.hpp"

bool AddShipmentController::validate(const Json::Value &json) {
	return json.isMember("name") 
		&& json["name"].isString() 
		&& json.isMember("weight") 
		&& json["weight"].isNumeric();
}

void AddShipmentController::doHandle(const Json::Value &src, Callback &callback) {
	const Shipment shipment(src["name"].asString(), src["weight"].asDouble());
	std::visit(
		EventHandler{callback},
		service.onShipmentArrived(shipment)
	);
}

Json::Value AddShipmentController::toJson(const ShipmentWaitsOutputEvent &event) {
	Json::Value result;
        result["type"] = "shipmentWaits";
        result["shipment"] = toJson(event.shipment);
        return result;		
}

void AddShipmentController::EventHandler::operator()(const ShipmentWaitsOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(AddShipmentController::toJson(event)));
}

void AddShipmentController::EventHandler::operator()(const AssignmentCreatedOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(Controller::toJson(event)));
}

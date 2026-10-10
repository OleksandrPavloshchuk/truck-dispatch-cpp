/**
 * add-shipment.cpp
 */
 
#include "add-shipment.hpp"

bool AddShipmentController::validate(const Json::Value &json) {
	return json.isMember("name") 
		&& json["name"].isString() 
		&& json.isMember("weight") 
		&& json["weight"].isNumeric();
}

void AddShipmentController::doHandle(const Json::Value &src, Callback &callback) {
	const Shipment shipment(src["name"].asString(), src["weight"].asDouble());
	service.onShipmentArrived(shipment,
		[this, shipment, callback](std::variant<ShipmentWaitsOutputEvent, AssignmentCreatedOutputEvent> result) {
			std::visit(EventHandler{callback, *this}, result);			
		},
		[this, callback](const std::string &error) {
			internalError(error, callback);
		}
	);	
}

Json::Value AddShipmentController::toJson(const ShipmentWaitsOutputEvent &event) {
	Json::Value result;	
        result["type"] = "shipmentWaits";
        result["shipment"] = toJson(event.shipment);
        return result;		
}

Json::Value AddShipmentController::toJson(const ShipmentDuplicateOutputEvent &event) {
	Json::Value result;	
        result["type"] = "shipmentDuplicate";
        result["shipment"] = toJson(event.shipment);
        return result;		
}

void AddShipmentController::EventHandler::operator()(const ShipmentWaitsOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(controller.toJson(event)));
}

void AddShipmentController::EventHandler::operator()(const ShipmentDuplicateOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(controller.toJson(event)));
}

void AddShipmentController::EventHandler::operator()(const AssignmentCreatedOutputEvent &event) const {
	callback(drogon::HttpResponse::newHttpJsonResponse(controller.toJson(event)));
}

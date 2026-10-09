/**
 * add-shipment-controller.hpp
 */
 
#pragma once

#include "controller.hpp"

class AddShipmentController : public Controller {
public:
	AddShipmentController(Service &service) : Controller(service) {}
protected:
	bool validate(const Json::Value &json);
	void doHandle(const Json::Value &json, Callback &callback);
private:
	using Controller::toJson;
	
	Json::Value toJson(const ShipmentWaitsOutputEvent &event);
	Json::Value toJson(const ShipmentDuplicateOutputEvent &event);
	
	struct EventHandler {
		void operator()(const ShipmentWaitsOutputEvent &event) const;
		void operator()(const ShipmentDuplicateOutputEvent &event) const;
		void operator()(const AssignmentCreatedOutputEvent &event) const;
		
		Callback &callback;
		AddShipmentController &controller;
	};
};

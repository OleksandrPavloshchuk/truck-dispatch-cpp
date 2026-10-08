/**
 * add-shipment-controller.hpp
 */
 
#pragma once

#include "controller.hpp"

class AddShipmentController : public Controller {
protected:
	bool validate(const Json::Value &json);
	void doHandle(const Json::Value &json, Callback &callback);
};

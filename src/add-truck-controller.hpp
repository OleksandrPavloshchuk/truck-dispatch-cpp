/**
 * add-truck-controller.hpp
 */
 
#pragma once

#include "controller.hpp"

class AddTruckController : public Controller {
public:
	AddTruckController(Service &service) : Controller(service) {}
protected:
	bool validate(const Json::Value &json);
	void doHandle(const Json::Value &json, Callback &callback);
private:
	static Json::Value toJson(const TruckWaitsOutputEvent &event);
	
	struct EventHandler {
		void operator()(const TruckWaitsOutputEvent &event) const;
		void operator()(const AssignmentCreatedOutputEvent &event) const;
		
		Callback &callback;
	};
};

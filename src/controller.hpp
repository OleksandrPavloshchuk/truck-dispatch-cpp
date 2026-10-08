/**
 * controller.hpp
 */
 
#pragma once

#include <string>
#include <variant>
#include <drogon/drogon.h>

#include "service.hpp"

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

class Controller {
public:
	Controller(Service &service) : service(service) {}
	void handle(const drogon::HttpRequestPtr& request, Callback &&callback);
protected:
	virtual bool validate(const Json::Value &json) = 0;
	virtual void doHandle(const Json::Value &src, Callback &callback) = 0;
	
	static Json::Value toJson(const Assignment &assignment);
	static Json::Value toJson(const Truck &truck);
	static Json::Value toJson(const Shipment &shipment);
	static Json::Value toJson(const AssignmentCreatedOutputEvent &event);
	
	Service &service;
	
private:
	void invalidJson(Callback &callback);
	void invalidInput(Callback &callback);
};

/**
 * metrics.hpp
 */
 
#pragma once

#include <string>
#include <drogon/drogon.h>

#include "../service.hpp"

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

class MetricsController {
public:
	MetricsController(IService &service) : service_(service) {}
	void handle(Callback &&callback);

private:
	IService &service_;
	
	void databaseError(const std::string &error, Callback &callback);
	void success(long shipmentsTotal, Callback &callback);
};

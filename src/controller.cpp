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
	auto response = drogon::HttpResponse::newHttpJsonResponse(Json::Value{{"error", "Invalid shipment"}});
        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
}

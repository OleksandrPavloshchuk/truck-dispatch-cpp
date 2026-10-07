/**
 * controller.hpp
 */
 
#pragma once

#include <string>
#include <variant>
#include <drogon/drogon.h>

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

class Controller {
public:
	void handle(const drogon::HttpRequestPtr& request, Callback &&callback);
protected:
	virtual bool validate(const Json::Value &json) = 0;
	virtual void doHandle(const Json::Value &json, Callback &&callback) = 0;
private:
	void invalidJson(Callback &&callback);
	void invalidInput(Callback &&callback);
	
};

/*
        	[](const drogon::HttpRequestPtr& request,
        		std::function<void(const drogon::HttpResponsePtr&)>&& callback) {

            		auto json = request->getJsonObject();

            		if (!json) {
                		auto response = drogon::HttpResponse::newHttpJsonResponse(Json::Value{{"error", "Invalid JSON"}});
	        	        response->setStatusCode(drogon::k400BadRequest);
        		        callback(response);
        		        return;
            		}

            		const auto& body = *json;

            		if (!body.isMember("name") || !body["name"].isString() || !body.isMember("weight") || !body["weight"].isNumeric()) {
                		auto response = drogon::HttpResponse::newHttpJsonResponse(Json::Value{{"error", "Invalid shipment"}});
                		response->setStatusCode(drogon::k400BadRequest);
                		callback(response);
                		return;
            		}

	            	const auto name = body["name"].asString();
        	    	const auto weight = body["weight"].asDouble();
        	    	
        	    	

        	    	Json::Value response;
        	    	response["name"] = name;
        	    	response["weight"] = weight;

        	    	callback(drogon::HttpResponse::newHttpJsonResponse(result));
        	})
*/

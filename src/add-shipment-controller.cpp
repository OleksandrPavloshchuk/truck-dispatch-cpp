/**
 * shipment-controller.cpp
 */
 
#include "add-shipment-controller.hpp"

bool AddShipmentController::validate(const Json::Value &json) {
	return json.isMember("name") 
		&& json["name"].isString() 
		&& json.isMember("weight") 
		&& json["weight"].isNumeric();
}


void AddShipmentController::doHandle(const Json::Value &src, Callback &callback) {
	// TODO


	            	const auto name = src["name"].asString();
        	    	const auto weight = src["weight"].asDouble();
        	    	
        	    	

        	    	Json::Value response;
        	    	response["name"] = name;
        	    	response["weight"] = weight;

        	    	callback(drogon::HttpResponse::newHttpJsonResponse(response));

}

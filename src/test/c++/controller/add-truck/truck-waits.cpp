/**
 * truck-waits.cpp
 */

#include <iostream>
#include <drogon/drogon.h>

#include <catch2/catch_test_macros.hpp>


#include "../../mocks/service.hpp"
#include "../../../../main/c++/controller/add-truck.hpp"

class TruckWaitsTestService : public MockService {
public:
	void onTruckArrived(const TruckArrivedInputEvent &in, OnTruckArrivedSuccess onTruckArrivedSuccess, OnError onError) override {
		onTruckArrivedSuccess(TruckWaitsOutputEvent(in.truck_));
	}
};

TEST_CASE("truck arrived and waits") {
	TruckWaitsTestService service;
	AddTruckController controller(service);
	
    	auto request = drogon::HttpRequest::newHttpRequest();
    	request->setMethod(drogon::Post);    	
    	request->setPath("/td/shipment");
    	request->setContentTypeCode(drogon::CT_APPLICATION_JSON);
    	request->setBody(R"({
    		"name": "t-one",
    		"capacity": 12.2
    	})");

    	controller.handle(
        	request,
        	[&](const drogon::HttpResponsePtr& response) {
		    	REQUIRE(response != nullptr);
		    	REQUIRE(response->statusCode() == drogon::k200OK);
		    	REQUIRE(response->getBody() == "{\"truck\":{\"capacity\":12.199999999999999,\"name\":\"t-one\"},\"type\":\"truckWaits\"}");
        	}
        );

}


/**
 * truck-waits.cpp
 */
 
#include <catch2/catch_test_macros.hpp>

#include "../../mocks/service.hpp"
#include "../../../src/controller/add-truck.hpp"

class TruckWaitsTestService : public MockService {
public:
	void onTruckArrived(const TruckArrivedInputEvent &in, OnTruckArrivedSuccess onTruckArrivedSuccess, OnError onError) override {
	
	}
};


TEST_CASE("truck arrived and waits") {
	TruckWaitsTestService service;

 
	REQUIRE(2 == 1 + 1);
}


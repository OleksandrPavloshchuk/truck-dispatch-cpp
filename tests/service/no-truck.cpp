/**
 * no-truck.cpp
 */

#include <iostream>
#include <catch2/catch_test_macros.hpp>

#include "../../src/service.hpp"
#include "../mocks/repository.hpp"

class TestRepository : public MockRepository {
public:
	void addShipment(const Shipment &shipment, OnSuccessAdd onSuccessAdd, OnError onError) override {
		onSuccessAdd();
	}
	
	void getLightestTruckForWeight(const double weight, OnSuccessGetTruck onSuccessGetTruck, OnError onError) {
		capturedWeight_ = weight;
		onSuccessGetTruck(std::nullopt);
	}
	
	double capturedWeight_;
};

TEST_CASE("no truck") {
	TestRepository repository;
	Service service(repository);
	ShipmentArrivedInputEvent in(Shipment("s2", 4.0));
	
    	bool successCalled = false;
    	std::string actualError;
	
	service.onShipmentArrived(in, 
		[&](std::variant<ShipmentWaitsOutputEvent, AssignmentCreatedOutputEvent> result) {
			successCalled = true;	
		}, 
		[&](const std::string &error) {
			actualError = error;
		});
	
	REQUIRE_FALSE(successCalled);
	REQUIRE_FALSE(actualError == "");
}

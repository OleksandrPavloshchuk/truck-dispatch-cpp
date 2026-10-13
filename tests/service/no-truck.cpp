/**
 * no-truck.cpp
 */

#include <catch2/catch_test_macros.hpp>

#include "../../src/service.hpp"
#include "../mocks/repository.hpp"

class NoTruckTestRepository : public MockRepository {
public:
	void addShipment(const Shipment &shipment, OnSuccessAdd onSuccessAdd, OnError onError) override {
		onSuccessAdd();
	}
	
	void getLightestTruckForWeight(const double weight, OnSuccessGetTruck onSuccessGetTruck, OnError onError) override {
		capturedWeight_ = weight;
		onSuccessGetTruck(std::nullopt);
	}
	
	double capturedWeight_{-1.0};
};

TEST_CASE("no truck") {

	NoTruckTestRepository repository;
	Service service(repository);
	ShipmentArrivedInputEvent in(Shipment("s2", 7.0));
	
    	bool successCalled = false;
	std::string actualError;	
	
	service.onShipmentArrived(in, 
		[&](std::variant<ShipmentWaitsOutputEvent, AssignmentCreatedOutputEvent> result) {
			successCalled = true;
			REQUIRE(std::holds_alternative<ShipmentWaitsOutputEvent>(result));
			const auto &event = std::get<ShipmentWaitsOutputEvent>(result);	
			REQUIRE(event.shipment_.name_ == "s2");
			REQUIRE(event.shipment_.weight_ == 7);					
		}, 
		[&](const std::string &error) {
			actualError = error;
		});
	
	REQUIRE(successCalled);
	REQUIRE(actualError == "");
	REQUIRE(repository.capturedWeight_==7);
}

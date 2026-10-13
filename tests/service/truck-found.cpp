/**
 * truck-found.cpp
 */

#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "../../src/service.hpp"
#include "../mocks/repository.hpp"

class TruckFoundTestRepository : public MockRepository {
public:
	void addShipment(const Shipment &shipment, OnSuccessAdd onSuccessAdd, OnError onError) override {
		onSuccessAdd();
	}
	
	void getLightestTruckForWeight(const double weight, OnSuccessGetTruck onSuccessGetTruck, OnError onError) override {
		onSuccessGetTruck(Truck("t1", 4.1));
	}
	
	void addAssignment(const Assignment &assignment, OnSuccessAdd onSuccessAdd, OnError onError) override {
		captured_.truckName_ = assignment.truck_.name_;
		captured_.truckCapacity_ = assignment.truck_.capacity_;
		captured_.shipmentName_ = assignment.shipment_.name_;
		captured_.shipmentWeight_ = assignment.shipment_.weight_;
		
		onSuccessAdd();
	}
	
	struct {
		std::string truckName_;
		double truckCapacity_;
		std::string shipmentName_;
		double shipmentWeight_;
	} captured_;
};

TEST_CASE("truck found") { 

	TruckFoundTestRepository repository;
	Service service(repository);
	ShipmentArrivedInputEvent in(Shipment("s3", 4.0));
	
    	bool successCalled = false;
	std::string actualError;	
	
	service.onShipmentArrived(in, 
		[&](std::variant<ShipmentWaitsOutputEvent, AssignmentCreatedOutputEvent> result) {
			successCalled = true;
			REQUIRE(std::holds_alternative<AssignmentCreatedOutputEvent>(result));
			const auto &event = std::get<AssignmentCreatedOutputEvent>(result);
			const auto assignment = event.assignment_;
			REQUIRE(assignment.truck_.name_ == repository.captured_.truckName_);
			REQUIRE(assignment.truck_.capacity_ == repository.captured_.truckCapacity_);
			REQUIRE(assignment.shipment_.name_ == repository.captured_.shipmentName_);
			REQUIRE(assignment.shipment_.weight_ == repository.captured_.shipmentWeight_);
		}, 
		[&](const std::string &error) {
			actualError = error;
		});
	
	REQUIRE(successCalled);
	REQUIRE(actualError == "");
}

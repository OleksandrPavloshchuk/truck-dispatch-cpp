/**
 * cant-add-shipment.cpp
 */

#include <catch2/catch_test_macros.hpp>

#include "../../src/service.hpp"
#include "../mocks/repository.hpp"

class CantAddShipmentTestRepository : public MockRepository {
public:
	void addShipment(const Shipment &shipment, OnSuccessAdd onSuccessAdd, OnError onError) override {
		captured_.weight_ = shipment.weight_;
		captured_.name_ = shipment.name_;
		
		onError("Something wrong");		
	}
	
	struct {
		std::string name_;
		double weight_;
	} captured_;
};

TEST_CASE("can't add shipment") {
	CantAddShipmentTestRepository repository;
	Service service(repository);
	ShipmentArrivedInputEvent in(Shipment("s1", 2.0));
	
    	bool successCalled = false;
	std::string actualError;	
	
	service.onShipmentArrived(in, 
		[&](auto) {
			successCalled = true;	
		}, 
		[&](const std::string &error) {
			actualError = error;
		});
	
	REQUIRE(repository.captured_.name_ == "s1");
	REQUIRE(repository.captured_.weight_ == 2);
	REQUIRE_FALSE(successCalled);
	REQUIRE(actualError == "Something wrong");
}

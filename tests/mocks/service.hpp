/**
 * service.hpp
 */
 
#pragma once 
 
#include "../../src/service.hpp" 

class MockService : public IService {
public:	
	void onShipmentArrived(
		const ShipmentArrivedInputEvent &in, 
		OnShipmentArrivedSuccess onShipmentArrivedSuccess,
		OnError onError) {}

	void onTruckArrived(
		const TruckArrivedInputEvent &in, 
		OnTruckArrivedSuccess onTruckArrivedSuccess,
		OnError onError) {}
			
};

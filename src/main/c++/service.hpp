/**
 * service.hpp
 */
 
#pragma once

#include <variant>
#include <functional>

#include "input-events.hpp"
#include "output-events.hpp"
#include "repository/repository.hpp"

using OnShipmentArrivedSuccess = std::function<void(std::variant<
	ShipmentWaitsOutputEvent, 
	AssignmentCreatedOutputEvent
>)>;
using OnTruckArrivedSuccess = std::function<void(std::variant<
	TruckWaitsOutputEvent, 
	AssignmentCreatedOutputEvent
>)>;
using OnSuccessGetTotal = std::function<void(const long)>;

class IService {
public:
	virtual void onShipmentArrived(
		const ShipmentArrivedInputEvent &in, 
		OnShipmentArrivedSuccess onShipmentArrivedSuccess,
		OnError onError) = 0;

	virtual void onTruckArrived(
		const TruckArrivedInputEvent &in, 
		OnTruckArrivedSuccess onTruckArrivedSuccess,
		OnError onError) = 0;
		
	virtual void getShipmentsTotal(
		OnSuccessGetTotal onSuccessGetTotal,
		OnError onError) = 0;
			
};

class Service : public IService {
public:
	Service(Repository &repository) : repository_(repository) {}
	
	void onShipmentArrived(
		const ShipmentArrivedInputEvent &in, 
		OnShipmentArrivedSuccess onShipmentArrivedSuccess,
		OnError onError);

	void onTruckArrived(
		const TruckArrivedInputEvent &in, 
		OnTruckArrivedSuccess onTruckArrivedSuccess,
		OnError onError);
		
	void getShipmentsTotal(
		OnSuccessGetTotal onSuccessGetTotal,
		OnError onError);
		
			
private:
	Repository &repository_;
};



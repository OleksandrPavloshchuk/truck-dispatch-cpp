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

class Service {
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
			
private:
	Repository &repository_;
};



/**
 * service.hpp
 */
 
#pragma once

#include <variant>

#include "input-events.hpp"
#include "output-events.hpp"
#include "repository.hpp"

class Service {
public:
	Service(Repository &repository) : repository(repository) {}

	std::variant<ShipmentWaitsOutputEvent, AssignmentCreatedOutputEvent> onShipmentArrived(
			const ShipmentArrivedInputEvent &in);

	std::variant<TruckWaitsOutputEvent, AssignmentCreatedOutputEvent> onTruckArrived(
			const TruckArrivedInputEvent &in);
			
private:
	Repository &repository;
};



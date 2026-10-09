/**
 * service.hpp
 */
 
#pragma once

#include <variant>

#include "input-events.hpp"
#include "output-events.hpp"
#include "repository/repository.hpp"

class Service {
public:
	Service(Repository &repository) : repository(repository) {}

	std::variant<
		ShipmentWaitsOutputEvent, 
		ShipmentDuplicateOutputEvent, 
		AssignmentCreatedOutputEvent
	> onShipmentArrived(
			const ShipmentArrivedInputEvent &in);

	std::variant<
		TruckWaitsOutputEvent, 
		TruckDuplicateOutputEvent, 
		AssignmentCreatedOutputEvent
	> onTruckArrived(
			const TruckArrivedInputEvent &in);
			
private:
	Repository &repository;
};



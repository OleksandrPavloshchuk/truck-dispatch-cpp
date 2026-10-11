/**
 * service.cpp
 */
#include <memory>
#include <utility> 

#include "service.hpp"

void Service::onShipmentArrived(
		const ShipmentArrivedInputEvent &in, 
		OnShipmentArrivedSuccess onShipmentArrivedSuccess,
		OnError onError) {
		
	const auto errorHandler = std::make_shared<OnError>(std::move(onError));
	const auto successHandler = std::make_shared<OnShipmentArrivedSuccess>(std::move(onShipmentArrivedSuccess));
	const Shipment &shipment = in.shipment;

	repository.addShipment(shipment, 
		[this, shipment, successHandler, errorHandler]() {
			repository.getLightestTruckForWeight(shipment.weight, 
				[this, shipment, successHandler, errorHandler](std::optional<Truck> truck) {
					if (truck) {
						const Assignment assignment(*truck, shipment);
						repository.addAssignment(assignment, 
							[this, assignment, successHandler, errorHandler]() {
								(*successHandler)(AssignmentCreatedOutputEvent(assignment));							
							},
							[errorHandler](const std::string &error) {(*errorHandler)(error);}
						);
					} else {
						(*successHandler)(ShipmentWaitsOutputEvent(shipment));
					}
				},
				[errorHandler](const std::string &error) {(*errorHandler)(error);}
			);
		},
		[errorHandler](const std::string &error) {(*errorHandler)(error);}
	);	
}

void Service::onTruckArrived(
		const TruckArrivedInputEvent &in, 
		OnTruckArrivedSuccess onTruckArrivedSuccess,
		OnError onError) {

	const auto errorHandler = std::make_shared<OnError>(std::move(onError));
	const auto successHandler = std::make_shared<OnTruckArrivedSuccess>(std::move(onTruckArrivedSuccess));
	const Truck &truck = in.truck;

	repository.addTruck(truck, 
		[this, truck, successHandler, errorHandler]() {
			repository.getHeaviestShipmentForCapacity(truck.capacity, 
				[this, truck, successHandler, errorHandler](std::optional<Shipment> shipment) {
					
					if (shipment) {
						const Assignment assignment(truck, *shipment);
						repository.addAssignment(assignment, 
							[this, assignment, successHandler, errorHandler]() {
								(*successHandler)(AssignmentCreatedOutputEvent(assignment));							
							},
							[errorHandler](const std::string &error) {(*errorHandler)(error);}
						);
					} else {
						(*successHandler)(TruckWaitsOutputEvent(truck));
					}
				},
				[errorHandler](const std::string &error) {(*errorHandler)(error);}
			);
		},
		[errorHandler](const std::string &error) {(*errorHandler)(error);}
	);	
}

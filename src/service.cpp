/**
 * service.cpp
 */

#include "service.hpp"

std::variant<ShipmentWaitsOutputEvent, AssignmentCreatedOutputEvent> 
	Service::onShipmentArrived(const ShipmentArrivedInputEvent &in) {
	
	const Shipment &shipment = in.shipment;
	// TODO throw exception in case of doubles?
	repository.addShipment(shipment);
	
	const std::optional<Truck> truckOpt = repository.getLightestTruckForWeight(shipment.weight);
	if (truckOpt) {
		const Assignment assignment(*truckOpt, shipment);
		repository.addAssignment(assignment);
		return AssignmentCreatedOutputEvent(assignment);
	} else {
		return ShipmentWaitsOutputEvent(shipment);	
	}
}

std::variant<TruckWaitsOutputEvent, AssignmentCreatedOutputEvent> 
	Service::onTruckArrived(const TruckArrivedInputEvent &in) {
	
	const Truck &truck = in.truck;
	// TODO throw exception in case of doubles?
	repository.addTruck(truck);
	
	const std::optional<Shipment> shipmentOpt = repository.getHeaviestShipmentForCapacity(truck.capacity);
	if (shipmentOpt) {
		const Assignment assignment(truck, *shipmentOpt);
		repository.addAssignment(assignment);
		return AssignmentCreatedOutputEvent(assignment);
	} else {
		return TruckWaitsOutputEvent(truck);	
	}
}			


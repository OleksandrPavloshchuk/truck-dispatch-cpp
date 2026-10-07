/**
 * service.cpp
 */
 
#include "service.hpp"

std::variant<ShipmentWaitsOutputEvent, AssignmentCreatedOutputEvent> 
	Service::onShipmentArrived(const ShipmentArrivedInputEvent &in) {
	
	const Shipment &shipment = in.shipment;
	const std::optional<Truck> truckOpt = repository.getLightestTruckForWeight(shipment.weight);
	if (truckOpt) {
		const Assignment assignment(*truckOpt, shipment);
		return AssignmentCreatedOutputEvent(assignment);
	} else {
		return ShipmentWaitsOutputEvent(shipment);	
	}
}

std::variant<TruckWaitsOutputEvent, AssignmentCreatedOutputEvent> 
	Service::onTruckArrived(const TruckArrivedInputEvent &in) {
	
	const Truck &truck = in.truck;
	const std::optional<Shipment> shipmentOpt = repository.getHeaviestShipmentForCapacity(truck.capacity);
	if (shipmentOpt) {
		const Assignment assignment(truck, *shipmentOpt);
		return AssignmentCreatedOutputEvent(assignment);
	} else {
		return TruckWaitsOutputEvent(truck);	
	}
}			


#ifndef __MICHAL_HPP
#define __MICHAL_HPP
#include <unordered_map>

#include "api.hpp"

#include <algorithm>

int TIME = 0;
std::vector<order> orders;

inline bool cmp(const order& o1, const order& o2) {
	return o1.products.size() < o2.products.size();
}

void initOrders() {
	for (int i = 0; i < numOfOrders; ++i) {
		order current;
		current.destination = orderDestination[i];
		current.products = numberOfProductsPerOrder[i];
		current.orderId = i;
		orders.push_back(current);
	}
}

bool warehouseHasAllProducts(int warehouseId, std::unordered_map<int, int>& orderProducts) {
	productsPerTypeVector& warehouse = productsPerWarehousePerType[warehouseId];
	
	for (auto product : orderProducts) {
		if (warehouse[product.first] < product.second)
			return false;
	}
	
	return true;
}

std::unordered_map<int, int> generateOrderProducts(int orderId) {
	std::unordered_map<int, int> orderProducts;
	order& o = orders[orderId];
	for (size_t i = 0; i < o.products.size(); i++) {
		orderProducts[o.products[i]]++;
	}

	return orderProducts;
}

// positive if found, -1 if not
int findWarehouseForOrder(int orderId, std::unordered_map<int, int>& orderProducts) {
	for (int warehouseId = 0; warehouseId < numOfWarehouse; warehouseId++) {
		if (warehouseHasAllProducts(warehouseId, orderProducts)) {
			return warehouseId;
		}
	}
	
	return -1;
}

void sendDrone(int warehouseId, int drone, int currentOrder, std::unordered_map<int, int>& orderProducts, int newTime) {
	productsPerTypeVector& warehouse = productsPerWarehousePerType[warehouseId];
	
	for (auto product : orderProducts) {
		// first type
		// second quantity
		std::cerr << "CHUJ: " << product.first << " " << product.second << std::endl;
		warehouse[product.first] = warehouse[product.first] - product.second;
		droneCommands.push_back(load(drone, warehouseId, product.first, product.second));
	}
	
	registerDroneBusy(newTime, drone);
	
	for (auto product : orderProducts) {
		droneCommands.push_back(deliver(drone, orders[currentOrder].orderId, product.first, product.second));
	}
}

bool tooHeavyOrder(std::unordered_map<int, int>& orderProducts) {
	int load = 0;
	for (auto product : orderProducts) {
		load += productsWeight[product.first] * product.second;
	}
	
	return load > maxPayload;
}

void calculate() {
	std::cerr << "hello calculate\n";
	initOrders();
	std::sort(orders.begin(), orders.end(), cmp);
	
	
	
	for (int i = 0; i < numOfOrders; i++) {
		
		int currentOrder = i;
		std::unordered_map<int, int> orderProducts = generateOrderProducts(currentOrder);
		if (tooHeavyOrder(orderProducts))
			continue;
		
		int warehouse = findWarehouseForOrder(currentOrder, orderProducts);
		if (warehouse >= 0) {
			std::pair<int, int> droneRecord = getSoonestFreeDrone();
			TIME = droneRecord.first;
			
			int newTime = getTimeForDrone(warehouse, droneRecord.second, orders[currentOrder], orderProducts);
			std::cerr << "TIME: " << newTime << std::endl; 
			if (newTime <= turns)
				sendDrone(warehouse, droneRecord.second, currentOrder, orderProducts, newTime);
		}

	}
	
	
	
	std::cerr << "end calculate\n";
}

#endif

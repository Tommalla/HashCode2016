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

// positive if found, -1 if not
int findWarehouseForOrder(int orderId) {
	std::unordered_map<int, int> orderProducts;
	order& o = orders[orderId];
	for (size_t i = 0; i < o.products.size(); i++) {
		if (orderProducts.find(o.products[i]) != orderProducts.end()) {
			orderProducts.insert({o.products[i], 1});
		}
		orderProducts.insert({o.products[i], orderProducts[o.products[i]] + 1});
	}
		
	for (int warehouseId = 0; warehouseId < numOfWarehouse; warehouseId++) {
		if (warehouseHasAllProducts(warehouseId, orderProducts)) {
			return warehouseId;
		}
	}
	
	return -1;
}

void sendDrone(int warehosueId, int drone, int currentOrder, int newTime) {
	
	
}


void calculate() {
	std::cerr << "hello calculate\n";
	initOrders();
	std::sort(orders.begin(), orders.end(), cmp);
	
	for (int i = 0; i < numOfOrders; i++) {
		int currentOrder = i;
		int warehouse = findWarehouseForOrder(currentOrder);
		if (warehouse >= 0) {
			std::pair<int, int> droneRecord = getSoonestFreeDrone();
			TIME = droneRecord.first;
			
			int newTime = getTimeForDrone(warehouse, droneRecord.second, orders[currentOrder]);
			
			if (newTime <= turns)
				sendDrone(warehouse, droneRecord.second, currentOrder, newTime);
			else
				break;
		}

	}
	
	std::cerr << "end calculate\n";
}

#endif

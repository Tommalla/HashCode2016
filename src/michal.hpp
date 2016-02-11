#ifndef __MICHAL_HPP
#define __MICHAL_HPP
#include "api.hpp"

#include <algorithm>

struct order {
	coords destination;
	productsPerTypeVector products;
};

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
}

// positive if found, -1 if not
int findWarehouseForOrder(int orderId) {
	std::unordered_map<int, int> orderProducts;
	order& o = orders[orderId];
	for (int i = 0; i < o.products; i++) {
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




void calculate() {
	std::cerr << "hello calculate\n";
	initOrders();
	std::sort(orders.begin(), orders.end(), cmp);
	
	for (int i = 0; i < numOfOrders; i++) {
		int warehouse = findWarehouseForOrder(i);
		int drone = 
	}
	
	std::cerr << "end calculate\n";
}

#endif
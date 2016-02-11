#ifndef __MICHAL_HPP
#define __MICHAL_HPP
#include "api.hpp"

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
		//order.destination = orderDestination[i];
		//order.products = numberOfProductsPerOrder[i];
		orders.push_back(current);
	}
}

void calculate() {

	initOrders();	
	//std::sort(orders.begin(), orders.end(), cmp);
	
	
	
	
}

#endif

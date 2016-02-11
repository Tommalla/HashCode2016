#include "api.hpp"
#include "michal.hpp"
#include <utility>
#include <sstream>

void printVector(const vector<int> &vect) {
	for (const auto &elem: vect) {
		cerr << elem << " ";
	}
	cerr << endl;
}

int main(int argc, char const *argv[])
{
	cin >> rows >> columns >> numOfDrones >> turns >> maxPayload;
	std::cerr << "rows: " << rows
		<< " columns: " << columns
		<< " numOfDrones: " << numOfDrones
		<< " turns: " << turns
		<< " maxPayload: " << maxPayload 
		<< std::endl;
		
	cin >> numOfProducts;
	std::cerr << "num of product types: " << numOfProducts << std::endl;
	
	productsWeight.resize(numOfProducts);
	for (int i = 0; i < numOfProducts; ++i) {
		cin >> productsWeight[i];
	}
	
	std::cerr << "Products weight: ";
	printVector(productsWeight);
	
	cin >> numOfWarehouse;
	std::cerr << "numOfWarehouse: " << numOfWarehouse << std::endl;
	
	WarehouseCoords.resize(numOfWarehouse);
	productsPerWarehousePerType.resize(numOfWarehouse);
	for (int i = 0; i < numOfWarehouse; ++i) {
		cin >> WarehouseCoords[i].first >> WarehouseCoords[i].second;
		productsPerWarehousePerType[i].resize(numOfProducts);
		for (int j = 0; j < numOfProducts; ++j) {
			cin >> productsPerWarehousePerType[i][j];
		}
	}
	
	cin >> numOfOrders;
	std::cerr << "num of orders: " << numOfOrders << std::endl;
	orderDestination.resize(numOfOrders);
	numberOfProductsPerOrder.resize(numOfOrders);
	
	for (int i = 0; i < numOfOrders; ++i) {
		cin >> orderDestination[i].first >> orderDestination[i].second;
		int productsForOrder;
		cin >> productsForOrder;
		while (productsForOrder--) {
			int productId;
			cin >> productId;
			numberOfProductsPerOrder[i].push_back(productId);
		}
	}

	for(auto it = WarehouseCoords.begin(); it != WarehouseCoords.end(); ++it)
	{
		std::cerr << "Warehouse coords: " << std::get<0>(*it) << ", " << std::get<1>(*it) << std::endl;
	}

	for(auto it = productsPerWarehousePerType.begin(); it != productsPerWarehousePerType.end(); ++it)
	{
		std::cerr << "Warehouse: ";
		for(auto it2 = it->begin(); it2 != it->end(); ++it2)
		{
			std::cerr << *it2 << " ";
		}
		std::cerr << std::endl;
	}

	for(auto it = orderDestination.begin(); it != orderDestination.end(); ++it)
	{
		std::cerr << "Order destination coords: " << std::get<0>(*it) << ", " << std::get<1>(*it) << std::endl;
	}

	for(auto it = numberOfProductsPerOrder.begin(); it != numberOfProductsPerOrder.end(); ++it)
	{
		std::cerr << "Order: ";
		for(auto it2 = it->begin(); it2 != it->end(); ++it2)
		{
			std::cerr << *it2 << " ";
		}
		std::cerr << std::endl;
	}

	for(auto it = dronsCoords.begin(); it != dronsCoords.end(); ++it)
	{
		std::cerr << "Current drons coords: " << it->first << ", " << it->second << std::endl;
	}
	
	initialDronesAvailable = numOfDrones;
	
	calculate();
	
	cout << droneCommands.size() << endl;
	
	for (DroneCommand* command : droneCommands) {
		command->printCommand();
		delete command;
	}
	
    return 0;
}

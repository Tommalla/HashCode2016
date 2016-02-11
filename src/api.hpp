#ifndef __API_HPP
#define __API_HPP
#include <cassert>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>

using namespace std;

// Defs

typedef std::pair<int,int> coords;
typedef std::vector<int> prodcutsWeightVector;
typedef std::vector<coords> warehouseCordsVector;
typedef std::vector<int> productsPerTypeVector;

struct DroneCommand {
	int droneId;
	char command;
	
	void printCommand() {
		cout << droneId << " " << command << " " ;
		printImplem();
		cout << endl;
	}
	
	virtual void printImplem() = 0;
	
	virtual ~DroneCommand() {};
};

struct DoThingsCommand : public DroneCommand {
	int special, productType, productQty;
	
	void printImplem() override {
		cout << special << " " << productType << " " << productQty;
	}
};

struct WaitCommand : public DroneCommand {
	int time;
	
	void printImplem() override {
		cout << time;
	}
};

DroneCommand* load(const int droneId, const int warehouseId, const int productType, const int productQty) {
	auto* res = new DoThingsCommand();
	res->droneId = droneId;
	res->command = 'L';
	res->special = warehouseId;
	res->productType = productType;
	res->productQty = productQty;
	return res;
}

DroneCommand* unload(const int droneId, const int warehouseId, const int productType, const int productQty) {
	auto* res = load(droneId, warehouseId, productType, productQty);
	res->command = 'U';
	return res;
}

DroneCommand* deliver(const int droneId, const int orderId, const int productType, const int productQty) {
	auto* res = load(droneId, orderId, productType, productQty);
	res->command = 'D';
	return res;
}
	
DroneCommand* wait(const int droneId, const int time) {
	auto* res = new WaitCommand();
	res->droneId = droneId;
	res->command = 'W';
	res->time = time;
	return res;
}

// Containers:
set<pair<int, int>> droneTimesQueue;
int initialDronesAvailable;

//Matrix:
int rows;
int columns;

//Drones:
int numOfDrones;
int maxPayload;

//Other:
int turns;

//Products
int numOfProducts;
prodcutsWeightVector productsWeight;

//Warehouses
int numOfWarehouse;
warehouseCordsVector WarehouseCoords;
std::vector<productsPerTypeVector> productsPerWarehousePerType;

//Orders
int numOfOrders;
std::vector<coords> orderDestination;
std::vector<productsPerTypeVector> numberOfProductsPerOrder;

//Current dron states
std::vector<coords> dronsCoords;

vector<DroneCommand *> droneCommands;

// Func:

// Outputs any errors in solution to stderr along with the result for the solution;
int validateSolution() {
	int result = 0;
	
	
	//cerr << "Solution value: " << result << endl;
	return result;
}

void registerDroneBusy(const int untilTimestamp, const int droneId) {
	droneTimesQueue.insert(make_pair(untilTimestamp, droneId));
}

pair<int, int> getSoonestFreeDrone() {
	if (initialDronesAvailable > 0) {
		initialDronesAvailable--;
		return make_pair(0, initialDronesAvailable);
	}
	assert(!droneTimesQueue.empty());
	auto res = *(droneTimesQueue.begin());
	droneTimesQueue.erase(droneTimesQueue.begin());
	return res;
}

struct order {
	int orderId;
	coords destination;
	productsPerTypeVector products;
};

int getTimeForDrone(int warehouse, int drone, const order& o, const unordered_map<int, int>& orderProducts) {
	auto warehousePos = WarehouseCoords[warehouse];
	
	double dx = warehousePos.first - o.destination.first;
	double dy = warehousePos.second - o.destination.second;
	
	int d = (int)ceil(sqrt(dx * dx + dy * dy));
	
	return d + 2 * orderProducts.size() ;
}

#endif

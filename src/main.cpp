#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

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


vector<DroneCommand *> droneCommands;


int main(int argc, char const *argv[])
{
 	std::ifstream file("input");
 	
 	int line_num = 0;
    
    for(std::string line; getline(file, line); )
	{
		std::cout << line << std::endl; 
		++line_num;
	}

	
	droneCommands.push_back(wait(1, 2));
	droneCommands.push_back(deliver(0, 2, 3, 10));
	
	
	for (DroneCommand* command : droneCommands) {
		command->printCommand();
		delete command;
	}
	return 0;
}

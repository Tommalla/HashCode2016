#include "api.hpp"
//#include "michal.hpp"
#include <utility>
#include <sstream>

int main(int argc, char const *argv[])
{
 	std::ifstream file("input");
 	
 	int lineNum = 0;
 	int loadedWarehouses = 0;
 	bool warehousesLocationLoaded = false;
 	bool orderNumLoaded = false;
 	int orderLoadingState = 0;
 	int loadedOrders = 0;
 	int productsNumForOrders = 0;

    for(std::string line; getline(file, line); )
	{
		std::cerr << "Reading line: " << lineNum << std::endl; 
		std::stringstream ss(line);
			
		if(lineNum == 0)
		{
			ss >> rows;
			ss >> columns;
			ss >> numOfDrones;
			ss >> turns;
			ss >> maxPayload;
			std::cerr << "rows: " << rows
					<< " columns: " << columns
					<< " numOfDrones: " << numOfDrones
					<< " turns: " << turns
					<< " maxPayload: " << maxPayload 
					<< std::endl;
		}
		else if(lineNum == 1)
		{
			ss >> numOfProducts;
			std::cerr << "num of product types: " << numOfProducts << std::endl;
		}
		else if(lineNum == 2)
		{
			int numberOfProductsWeightGot = 0;
			
			productsWeight.resize(numOfProducts);
			while(numberOfProductsWeightGot < numOfProducts)
			{
				ss >> productsWeight[numberOfProductsWeightGot];	
				++numberOfProductsWeightGot;
			}
  			
  			std::cerr << "Products weight: ";
  			for (auto i = productsWeight.begin(); i != productsWeight.end(); ++i)
			{
    			std::cerr << *i << ' ';
    		}
    		std::cerr << std::endl;
		}
		else if(lineNum == 3)
		{
			ss >> numOfWarehouse;
			std::cerr << "numOfWarehouse: " << numOfWarehouse << std::endl;

			productsPerWarehousePerType.resize(numOfWarehouse);
			WarehouseCoords.resize(numOfWarehouse);
		}
		else if(loadedWarehouses < numOfWarehouse)
		{
			if(not warehousesLocationLoaded)
			{
				int x;
				int y;
				ss >> x;
				ss >> y;
				WarehouseCoords[loadedWarehouses] = coords(x,y);	
			}
			else
			{
				productsPerWarehousePerType[loadedWarehouses].resize(numOfProducts);
				for(int productTypeId = 0; productTypeId < numOfProducts; ++productTypeId)
				{
					ss >> productsPerWarehousePerType[loadedWarehouses][productTypeId];
				}
				++loadedWarehouses;
			}

			//We want to get two different lines with warehouse info
			warehousesLocationLoaded = not warehousesLocationLoaded;
		}
		else if(not orderNumLoaded)
		{
			orderNumLoaded = true;
			ss >> numOfOrders;
			std::cerr << "num of orders: " << numOfOrders << std::endl;
			orderDestination.resize(numOfOrders);
			numberOfProductsPerOrder.resize(numOfOrders);

		}
		else if(orderLoadingState == 0)
		{
			int x;
			int y;
			ss >> x;
			ss >> y;
			orderDestination[loadedOrders] = coords(x,y);
			++orderLoadingState;
		}
		else if(orderLoadingState == 1)
		{
			ss >> productsNumForOrders;
			numberOfProductsPerOrder[loadedOrders].resize(numOfProducts, 0);
			++orderLoadingState;
		}
		else if(orderLoadingState == 2)
		{
			for(int i = 0; i < productsNumForOrders; ++i)
			{
				int itemId;
				ss >> itemId;
				++numberOfProductsPerOrder[loadedOrders][itemId];
			}
			orderLoadingState = 0;
			++loadedOrders;
		}

		++lineNum;
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

//	calculate();
	
// 	droneCommands.push_back(wait(1, 2));
// 	droneCommands.push_back(deliver(0, 2, 3, 10));
	
	for (DroneCommand* command : droneCommands) {
		command->printCommand();
		delete command;
	}

//	return solutionValue;
	return 0;
}

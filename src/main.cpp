#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>

typedef std::pair<int,int> coords;
typedef std::vector<int> prodcutsWeightVector;
typedef std::vector<coords> warehouseCordsVector;
typedef std::vector<int> productsPerTypeVector;

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




int main(int argc, char const *argv[])
{
 	std::ifstream file("input");
 	
 	int line_num = 0;
    
    for(std::string line; getline(file, line); )
	{
		std::cout << line << std::endl; 
		++line_num;
	}

    return 0;
}
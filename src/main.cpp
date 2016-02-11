#include "api.hpp"

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
	
	int solutionValue = validateSolution();
	if (solutionValue < 0) {
		return -1;
	}
    
	for (DroneCommand* command : droneCommands) {
		command->printCommand();
		delete command;
	}
	
	return solutionValue;
}

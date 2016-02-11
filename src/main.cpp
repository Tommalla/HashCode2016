#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(int argc, char const *argv[])
{
    std::vector<char> v;
 	std::ifstream file("input");
 	
 	int line_num = 0;
    
    for(std::string line; getline(file, line); )
	{
		std::cout << line << std::endl; 
		++line_num;
	}

    return 0;
}
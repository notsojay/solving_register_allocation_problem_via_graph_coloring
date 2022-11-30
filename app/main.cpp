#include <iostream>
#include "proj6.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"

int main() 
{
	auto GRAPH = "simple.csv";
	InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);
	std::unordered_set<Variable> expected_vertices = {"z", "x", "y"};
	for(auto &i : ig.vertices())
	{
		std::cout << i << " ";
	}
	return 0; 
}

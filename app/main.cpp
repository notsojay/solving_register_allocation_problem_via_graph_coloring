#include <iostream>
#include "proj6.hpp"
#include "CSVReader.hpp"
#include "IGWriter.hpp"
#include "InterferenceGraph.hpp"

int main() 
{
	const auto &GRAPH = "self.csv";
	const auto NUM_REGS = 3;
	
	const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
	
//	const auto &GRAPH = "pairs.csv";
//	const auto NUM_REGS = 2;
//	
//	const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
//	for(const auto &i : allocation)
//	{
//		std::cout << i.first << " " << i.second << "\n";
//	}
//	IGWriter::write(CSVReader::load(GRAPH), "pairs.dot", allocation);
	
	//EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
	
//	auto GRAPH = "simple.csv";
//	InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);
//	
//	ig.removeEdge("x", "y");
//	std::cout << ig.numEdges();
//	
//	auto add = [](int a, int b) -> int { return a + b; };
//	
//	add(1, 2);
//	
	
//	EXPECT_EQ(ig.numEdges(), 2);
//	ig.removeEdge("x", "z");
//	EXPECT_EQ(ig.numEdges(), 1);
//	ig.removeEdge("z", "y");
//	EXPECT_EQ(ig.numEdges(), 0);
//	
//	EXPECT_EQ(ig.numVertices(), 3);
//	ig.removeVertex("z");
//	EXPECT_EQ(ig.numVertices(), 2);
//	ig.removeVertex("y");
//	EXPECT_EQ(ig.numVertices(), 1);
//	ig.removeVertex("x");
//	EXPECT_EQ(ig.numVertices(), 0);
	return 0; 
}

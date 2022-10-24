/**
   CSVReader.cpp

   You do NOT need to modify this file as part of your project. This is simply
   a utility for creating an InterferenceGraph type from a graph file as
   mentioned in the README.

*/

#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <fstream>
#include <sstream>
#include <utility>

InterferenceGraph<Variable>::EdgeTy CSVReader::readEdge(std::string &s) {
  Variable v;
  Variable w;

  std::stringstream stream(s);
  std::getline(stream, v, ',');
  std::getline(stream, w);
  return InterferenceGraph<Variable>::EdgeTy(v, w);
}

// Again, do NOT modify the following function.
InterferenceGraph<Variable> CSVReader::load(const std::string &graph_path) {

  InterferenceGraph<Variable> ig;
  std::string line;
  std::ifstream file_stream(graph_path);

  while (std::getline(file_stream, line)) {
    const auto &edge = readEdge(line);
    ig.addVertex(edge.first);            // implemented by YOU
    ig.addVertex(edge.second);           // implemented by YOU
    ig.addEdge(edge.first, edge.second); // implemented by YOU
  }

  // Note: copy constructor not needed due to copy ellision.
  return ig;
}
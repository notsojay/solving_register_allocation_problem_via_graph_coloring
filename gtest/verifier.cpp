/**
   verifier.cpp

   You do NOT need to modify this file as part of your project. This is simply
   a utility for verifying that your register allocation is correct for a given
   graph.

*/

#include "verifier.hpp"
#include "CSVReader.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

using namespace proj6;

testing::AssertionResult verifyAllocation(const std::string &path_to_graph,
                                          int num_registers,
                                          const RegisterAssignment &mapping) {

  std::string line;
  std::ifstream file_stream(path_to_graph);
  std::unordered_map<Variable, unsigned> degrees;

  while (std::getline(file_stream, line)) {
    const auto &edge = CSVReader::readEdge(line);
    degrees[edge.first]++;
    degrees[edge.second]++;
    if (mapping.find(edge.first) == mapping.end()) {
      return testing::AssertionFailure()
             << "Variable " << edge.first
             << " did not get mapped to a register!";
    }
    if (mapping.find(edge.second) == mapping.end()) {
      return testing::AssertionFailure()
             << "Variable " << edge.second
             << " did not get mapped to a register!";
    }
    if (mapping.at(edge.first) < 1 || mapping.at(edge.first) > num_registers)
      return testing::AssertionFailure()
             << "Variable " << edge.first << " mapped to register "
             << mapping.at(edge.first) << " which is out of range [" << 1 << ","
             << num_registers << "]";

    if (mapping.at(edge.second) < 1 || mapping.at(edge.second) > num_registers)
      return testing::AssertionFailure()
             << "Variable " << edge.second << " mapped to register "
             << mapping.at(edge.second) << " which is out of range [" << 1
             << "," << num_registers << "]";

    if (mapping.at(edge.first) == mapping.at(edge.second))
      return testing::AssertionFailure()
             << "Variables " << edge.first << " and " << edge.second
             << " were mapped to the same register: " << mapping.at(edge.first);
  }
  const auto highest_degree =
      std::max_element(
          std::begin(degrees), std::end(degrees),
          [](const auto &p1, const auto &p2) { return p1.second < p2.second; })
          ->second;

  std::unordered_set<Register> unique_registers;
  for (const auto &e : mapping)
    unique_registers.insert(e.second);

  const auto MAX_ALLOWED_REGS = highest_degree + 1;
  const auto NUM_USED_REGS = unique_registers.size();
  if (NUM_USED_REGS > MAX_ALLOWED_REGS) {
    return testing::AssertionFailure()
           << "Too many registers were used! Expected at most "
           << MAX_ALLOWED_REGS << " but you used " << NUM_USED_REGS;
  }

  return testing::AssertionSuccess();
}
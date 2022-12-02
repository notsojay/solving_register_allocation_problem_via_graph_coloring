#include "CSVReader.hpp"
#include "IGWriter.hpp"
#include "InterferenceGraph.hpp"
#include "proj6.hpp"
#include "verifier.hpp"
#include "gtest/gtest.h"

// Warning: These are *NOT* exhaustive tests.
// You should consider creating your own unit tests
// to test the functionality of your code entirely.

namespace {

using namespace proj6;

TEST(InterferenceGraph, SimpleAddEdgesAndVertices) {
  const auto &GRAPH = "gtest/graphs/simple.csv";

  const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

  EXPECT_EQ(ig.numEdges(), 3);
  EXPECT_EQ(ig.numVertices(), 3);

  const std::unordered_set<Variable> &expected_vertices = {"z", "x", "y"};
  EXPECT_EQ(ig.vertices(), expected_vertices);

  std::unordered_set<Variable> expected_neighbors;
  expected_neighbors = {"y", "z"};
  EXPECT_EQ(ig.neighbors("x"), expected_neighbors);

  expected_neighbors = {"x", "y"};
  EXPECT_EQ(ig.neighbors("z"), expected_neighbors);

  expected_neighbors = {"z", "x"};
  EXPECT_EQ(ig.neighbors("y"), expected_neighbors);
}

TEST(InterferenceGraph, InterferesBasic) {
  const auto &GRAPH = "gtest/graphs/simple.csv";

  const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

  EXPECT_TRUE(ig.interferes("x", "y"));
  EXPECT_TRUE(ig.interferes("y", "x"));
  EXPECT_TRUE(ig.interferes("x", "z"));
  EXPECT_TRUE(ig.interferes("z", "x"));
  EXPECT_TRUE(ig.interferes("z", "y"));
  EXPECT_TRUE(ig.interferes("y", "z"));
}

TEST(InterferenceGraph, DegreeBasic) {
  const auto &GRAPH = "gtest/graphs/simple.csv";

  const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

  EXPECT_EQ(ig.degree("x"), 2);
  EXPECT_EQ(ig.degree("y"), 2);
  EXPECT_EQ(ig.degree("z"), 2);
}

TEST(InterferenceGraph, SimpleRemove) {
  const auto &GRAPH = "gtest/graphs/simple.csv";

  InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);

  ig.removeEdge("x", "y");
  EXPECT_EQ(ig.numEdges(), 2);
  ig.removeEdge("x", "z");
  EXPECT_EQ(ig.numEdges(), 1);
  ig.removeEdge("z", "y");
  EXPECT_EQ(ig.numEdges(), 0);

  EXPECT_EQ(ig.numVertices(), 3);
  ig.removeVertex("z");
  EXPECT_EQ(ig.numVertices(), 2);
  ig.removeVertex("y");
  EXPECT_EQ(ig.numVertices(), 1);
  ig.removeVertex("x");
  EXPECT_EQ(ig.numVertices(), 0);
}

TEST(InterferenceGraph, Neighbors) {
  const auto &GRAPH = "gtest/graphs/simple.csv";

  const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

  const std::unordered_set<Variable> &expected_neighbors = {"y", "z"};

  EXPECT_EQ(ig.neighbors("x"), expected_neighbors);
}

TEST(RegisterAllocation, Simple) {
  const auto &GRAPH = "gtest/graphs/simple.csv";
  const auto NUM_REGS = 3;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH), "gtest/graphs/simple.dot",
                  allocation);

  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, SmallBipartiteFail) {
  const auto &GRAPH = "gtest/graphs/small_bipartite.csv";
  const auto NUM_REGS = 1;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),
                  "gtest/graphs/small_bipartite_fail.dot", allocation);
  EXPECT_TRUE(allocation.empty());
}

TEST(RegisterAllocation, SmallBipartiteSuccess) {
  const auto &GRAPH = "gtest/graphs/small_bipartite.csv";
  const auto NUM_REGS = 2;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),
                  "gtest/graphs/small_bipartite_success.dot", allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, BigBipartiteFail) {
  const auto &GRAPH = "gtest/graphs/big_bipartite.csv";
  const auto NUM_REGS = 1;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH), "gtest/graphs/big_bipartite_fail.dot",
                  allocation);
  EXPECT_TRUE(allocation.empty());
}

TEST(RegisterAllocation, BigBipartiteSuccess) {
  const auto &GRAPH = "gtest/graphs/big_bipartite.csv";
  const auto NUM_REGS = 2;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),
                  "gtest/graphs/big_bipartite_success.dot", allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, Pairs) {
  const auto &GRAPH = "gtest/graphs/pairs.csv";
  const auto NUM_REGS = 2;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH), "gtest/graphs/pairs.dot", allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, CompleteSix) {
  const auto &GRAPH = "gtest/graphs/complete_6.csv";
  const auto NUM_REGS = 6;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH), "gtest/graphs/complete_6.dot",
                  allocation);

  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, CompleteEight) {
  const auto &GRAPH = "gtest/graphs/complete_8.csv";
  const auto NUM_REGS = 8;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH), "gtest/graphs/complete_8.dot",
                  allocation);

  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, CompleteEightFail) {
  const auto &GRAPH = "gtest/graphs/complete_8.csv";
  const auto NUM_REGS = 7;

  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH), "gtest/graphs/complete_8_fail.dot",
                  allocation);
  EXPECT_TRUE(allocation.empty());
}

  TEST(RegisterAllocation, selftest) {
    const auto &GRAPH = "gtest/graphs/self.csv";
    const auto NUM_REGS = 3;
    
    const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
    EXPECT_TRUE(!allocation.empty());
  }

} // end namespace

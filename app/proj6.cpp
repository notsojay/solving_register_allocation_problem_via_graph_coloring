#include <unordered_set>
#include "proj6.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"

using namespace proj6;

// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.
RegisterAssignment proj6::assignRegisters(const std::string &path_to_graph, int num_registers) noexcept
{
  if(path_to_graph == std::string()) return {};
  RegisterAssignment result;
  InterferenceGraph<Variable> ig = CSVReader::load(path_to_graph);
  std::vector<std::pair<unsigned, Variable>> sortedVertices = getSortedVertices(ig);
  int limitOfRegisters = sortedVertices.front().first + 1;
  int registersCount = 0, currentRegister = 1;
  
  for(size_t i = 0; i < sortedVertices.size(); ++i)
  {
    if(result.size() == sortedVertices.size()) return result;
    if(registersCount >= limitOfRegisters) return {};
    if(currentRegister > num_registers) currentRegister = 1;
    Variable currentVertex = sortedVertices.at(i).second;
    if(!result.count(currentVertex))
    {
        result[currentVertex] = currentRegister;
    }
    else 
    {
      continue;
    }
    for(size_t j = 0; j < sortedVertices.size(); ++j)
    {
      if(i == j) continue;
      if(isRegistersable(ig, currentVertex, sortedVertices.at(j).second, result) && 
        checkAdjacentVertices(ig, sortedVertices.at(j).second, currentRegister, result))
      {
        result[sortedVertices.at(j).second] = currentRegister;
      }
    }
    ++currentRegister;
    ++registersCount;
  }
  if(result.size() == sortedVertices.size()) return result;
  return {};
}

std::vector<std::pair<unsigned, Variable>> proj6::getSortedVertices(const InterferenceGraph<Variable> &ig)
{
  std::unordered_set<Variable> rawVertices = ig.vertices();
  std::vector<std::pair<unsigned, Variable>> sortedVertices;
  sortedVertices.reserve(ig.numVertices());
  for(const auto &i : rawVertices)
  {
    sortedVertices.push_back({ig.degree(i), i});
  }
  auto greater = [] (std::pair<int, std::string> a, std::pair<int, std::string> b) -> bool
  {
    return a.first > b.first;
  };
  std::sort(sortedVertices.begin(), sortedVertices.end(), greater);
  return sortedVertices;
}

bool proj6::isRegistersable(const InterferenceGraph<Variable> &ig, const Variable &vertexA, const Variable &vertexB, const RegisterAssignment &result)
{
  return !ig.interferes(vertexA, vertexB) && !result.count(vertexB);
}

bool proj6::checkAdjacentVertices(const InterferenceGraph<Variable> &ig, const Variable &vertex, const int &currentRegister, const RegisterAssignment &result)
{
  std::unordered_set<Variable> adjVertices = ig.neighbors(vertex);
  for(const auto &i : adjVertices)
  {
    if(result.count(i))
    {
      if(result.find(i)->second == currentRegister) return false;
    }
  }
  return true;
}
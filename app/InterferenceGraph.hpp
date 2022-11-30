#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class UnknownVertexException : public std::runtime_error {
public:
  UnknownVertexException(const std::string &v)
      : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error {
public:
  UnknownEdgeException(const std::string &v, const std::string &w)
      : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file.
template <typename T> 
class InterferenceGraph {
public:
  // Custom type used to represent edges. This is mainly
  // used in the utility function for reading and writing
  // the graph structure to/from files. You don't need to use it.
  using EdgeTy = std::pair<T, T>;

  InterferenceGraph();

  ~InterferenceGraph();

  void addEdge(const T &v, const T &w);

  void addVertex(const T &vertex) noexcept;

  void removeEdge(const T &v, const T &w);

  void removeVertex(const T &vertex);

  std::unordered_set<T> vertices() const noexcept;

  std::unordered_set<T> neighbors(const T &vertex) const;

  unsigned numVertices() const noexcept;

  unsigned numEdges() const noexcept;

  bool interferes(const T &v, const T &w) const;

  unsigned degree(const T &v) const;

private:
  size_t LocateVertexIndex(const T& vertex) const;

private:
  // Private member variables here.
  std::vector<T> setOfVertices;
  std::unordered_map<T, size_t> setOfIndex;
  std::vector<std::vector<int>> adjacencyMatrix;
  unsigned edgesCount;
};

template <typename T>
InterferenceGraph<T>::InterferenceGraph():edgesCount(0)
{
  
}

template <typename T>
InterferenceGraph<T>::~InterferenceGraph() 
{
  
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const 
{
  size_t index = LocateVertexIndex(vertex);
  std::unordered_set<T> neighbors;
  for(size_t i = 0; i < adjacencyMatrix.at(index).size(); ++i)
  {
    if(adjacencyMatrix.at(index).at(i) != 0)
      neighbors.insert(setOfVertices.at(i));
  }
  return neighbors;
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept
{
  std::unordered_set<T> vertices;
  for(const auto &i : setOfVertices)
  {
    vertices.insert(i);
  }
  return vertices;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept 
{  return setOfVertices.size();
}

template <typename T> unsigned InterferenceGraph<T>::numEdges() const noexcept
{
  return edgesCount;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w)
{
  if(v == w) return;
  size_t vIndex = LocateVertexIndex(v), wIndex = LocateVertexIndex(w);
  adjacencyMatrix.at(vIndex).at(wIndex) = 1;
  adjacencyMatrix.at(wIndex).at(vIndex) = 1;
  ++edgesCount;
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w) 
{
  size_t vIndex = LocateVertexIndex(v), wIndex = LocateVertexIndex(w);
  if(adjacencyMatrix.at(vIndex).at(wIndex) == 0 || adjacencyMatrix.at(wIndex).at(vIndex) == 0)
    throw UnknownEdgeException(v, w);
  adjacencyMatrix.at(vIndex).at(wIndex) = 0;
  adjacencyMatrix.at(wIndex).at(vIndex) = 0;
  --edgesCount;
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) noexcept
{
  if(setOfIndex.count(vertex)) return;
  setOfVertices.push_back(vertex);
  setOfIndex.insert({vertex, setOfVertices.size()-1});
  for(auto &i : adjacencyMatrix)
  {
    i.push_back(0);
  }
  adjacencyMatrix.push_back(std::vector<int>(setOfVertices.size(), 0));
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) 
{
  size_t index = LocateVertexIndex(vertex);
  setOfIndex[setOfVertices.back()] = index;
  setOfIndex.erase(vertex);
  std::swap(setOfVertices.at(index), setOfVertices.back());
  setOfVertices.pop_back();
  std::swap(adjacencyMatrix.at(index), adjacencyMatrix.back());
  adjacencyMatrix.pop_back();
  for(auto &i : adjacencyMatrix)
  {
    std::swap(i.at(index), i.back());
    i.pop_back();
  }
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const 
{
  size_t vIndex = LocateVertexIndex(v), wIndex = LocateVertexIndex(w);
  return adjacencyMatrix.at(vIndex).at(wIndex) != 0 && adjacencyMatrix.at(wIndex).at(vIndex) != 0;
}

template <typename T>
unsigned InterferenceGraph<T>::degree(const T &v) const 
{
  size_t index = LocateVertexIndex(v);
  unsigned degreeCount = 0;
  for(const auto &i : adjacencyMatrix.at(index))
  {
    if(i != 0) ++degreeCount;
  }
  return degreeCount; 
}

template <typename T>
size_t InterferenceGraph<T>::LocateVertexIndex(const T& vertex) const
{
  if(!setOfIndex.count(vertex)) throw UnknownVertexException(vertex);
  size_t index = setOfIndex.find(vertex)->second;
  return index;
}

#endif

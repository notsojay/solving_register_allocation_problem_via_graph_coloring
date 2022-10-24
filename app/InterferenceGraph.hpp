#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>

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
template <typename T> class InterferenceGraph {
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
  // Private member variables here.
};

template <typename T> InterferenceGraph<T>::InterferenceGraph() {}

template <typename T> InterferenceGraph<T>::~InterferenceGraph() {}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const {
  return {};
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
  return {};
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
  return 0;
}

template <typename T> unsigned InterferenceGraph<T>::numEdges() const noexcept {
  return 0;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w) {}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w) {}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) noexcept {}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) {}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const { return false; }

template <typename T>
unsigned InterferenceGraph<T>::degree(const T &v) const { return 0; }

#endif

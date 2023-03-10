#ifndef __PROJ_6__HPP
#define __PROJ_6__HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "InterferenceGraph.hpp"

namespace proj6 {

using Variable = std::string;
using Register = int;
using RegisterAssignment = std::unordered_map<Variable, Register>;

RegisterAssignment assignRegisters(const std::string &path_to_graph,
                                   int num_registers) noexcept;

std::vector<std::pair<unsigned, Variable>> getSortedVertices(const InterferenceGraph<Variable> &ig);

bool isRegistersable(const InterferenceGraph<Variable> &ig, const Variable &vertexA, const Variable &vertexB, const RegisterAssignment &result);

bool checkAdjacentVertices(const InterferenceGraph<Variable> &ig, const Variable &vertex, const int &currentRegister, const RegisterAssignment &result);

}; // namespace proj6

#endif
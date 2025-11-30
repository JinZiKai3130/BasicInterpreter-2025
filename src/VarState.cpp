#include "VarState.hpp"

#include <algorithm>

#include "utils/Error.hpp"

VarState::VarState() {
  scopes.emplace_back();
}

void VarState::Indent() {
  scopes.emplace_back();
}

void VarState::Dedent() {
  if (scopes.size() <= 1) {
    throw BasicError("SCOPE UNDERFLOW");
  }
  scopes.pop_back();
}

void VarState::setValue(const std::string& name, int value) { // change
  scopes.back()[name] = value;
}

int VarState::getValue(const std::string& name) const { // change 
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    auto var = it->find(name);
    if (var != it->end()) {
      return var->second;
    }
  }
  throw BasicError("VARIABLE NOT DEFINED");
}

void VarState::clear() {
  scopes.clear();
  scopes.emplace_back();
}
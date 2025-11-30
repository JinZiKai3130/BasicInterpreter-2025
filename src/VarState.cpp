#include "VarState.hpp"

#include <algorithm>

#include "utils/Error.hpp"

VarState::VarState() {
  level = 0;
  scopes.resize(1);
}

void VarState::Indent() {
  ++level;
  scopes.resize(level + 1);
}

void VarState::Dedent() {
  if (level == 0) {
    throw BasicError("SCOPE UNDERFLOW");
  }
  --level;
  scopes.resize(level + 1);
}

void VarState::setValue(const std::string& name, int value) { // change
  scopes.back()[name] = value;
}

int VarState::getValue(const std::string& name) const { // change 
  for (auto it = scopes.end(); it != scopes.begin(); --it) {
    auto var = it->find(name);
    if (var != it->end()) {
      return var->second;
    }
  }
  throw BasicError("VARIABLE NOT DEFINED");
}

void VarState::clear() {
  scopes.clear();
  level = 0;
  scopes.resize(1);
}
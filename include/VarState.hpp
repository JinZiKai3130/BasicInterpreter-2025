#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class VarState {
 public:
  VarState();
  void Indent();
  void Dedent();
  void setValue(const std::string& name, int value);
  int getValue(const std::string& name) const;
  void clear();

 private:
  int level;
  std::vector<std::unordered_map<std::string, int>> scopes;
};

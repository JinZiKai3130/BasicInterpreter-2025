#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default;

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;
};

// TODO: Other statement types derived from Statement, e.g., GOTOStatement,
// LetStatement, etc.
class LetStmt : public Statement {
private:
    std::string varName;
    Expression* expr;

public:
    LetStmt(const std::string& varName, Expression* expr, const std::string& originLine);

    ~LetStmt() override {
        delete expr;
    }

    void execute(VarState& varState) const;
};

class InputStmt : public Statement {
  private:
    std::string varName;
  public:
    InputStmt(const std::string& varName, const std::string& originLine)
        : Statement(originLine), varName(varName) {
        }

    void execute(VarState& varState) const;
};
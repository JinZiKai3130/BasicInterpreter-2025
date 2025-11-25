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
  std::string varName_;
  Expression* expr_;
public:
  LetStmt(std::string varName, Expression* expr, const std::string& originLine);
  ~LetStmt() override;
  void execute(VarState& varState, Program& program) const override;
};

class InputStmt : public Statement {
private:
  std::string varName_;
public:
  InputStmt(std::string varName, const std::string& originLine);
  void execute(VarState& varState, Program& program) const override;
};

class PrintStmt : public Statement {
private:
  Expression* expr;
public:
  PrintStmt(Expression* expr, const std::string& originLine);
  ~PrintStmt() override;
  void execute(VarState& varState, Program& program) const override;
};

class GotoStmt : public Statement {
private:
    int targetLine;
public:
    GotoStmt(int targetLine, const std::string& originLine);
    void execute(VarState& varState, Program& program) const override;
};

class IfStmt : public Statement {
private:
    Expression* leftExpr_;
    char comparisonOp_;
    Expression* rightExpr_;
    int targetLine_;

public:
    IfStmt(Expression* leftExpr, char op, Expression* rightExpr, 
           int targetLine, const std::string& originLine);
    
    ~IfStmt() override;

    void execute(VarState& varState, Program& program) const override;
};

class RemStmt : public Statement {
public:
    explicit RemStmt(const std::string& originLine);
    void execute(VarState& varState, Program& program) const override;
};

class EndStmt : public Statement {
public:
    explicit EndStmt(const std::string& originLine);
    void execute(VarState& varState, Program& program) const override;
};

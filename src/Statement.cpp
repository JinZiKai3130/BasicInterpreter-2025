#include "Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }

// TODO: Imply interfaces declared in the Statement.hpp.
LetStmt(const std::string& varName, Expression* expr, const std::string& originLine)
        : Statement(originLine), varName(varName), expr(expr) {

        }
void LetStmt::execute(VarState& varState) const {
    int exprValue = expr->evaluate(varState);

    varState.setValue(varName, exprValue);
}

InputStmt::InputStmt(std::string varName, std::string source)
    : Statement(std::move(source)), varName_(std::move(varName)) {

    }


void InputStmt::execute(VarState& state) const {
  std::cout << "?";
  int inputValue;
  std::cin >> inputValue;

  state.setValue(varName_, inputValue);
}
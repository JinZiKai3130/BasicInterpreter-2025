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
LetStmt::LetStmt(std::string varName, Expression* expr, const std::string& originLine)
    : Statement(originLine), varName_(std::move(varName)), expr_(expr) {
    }

LetStmt::~LetStmt() {
    delete expr_;
}

void LetStmt::execute(VarState& varState, Program& program) const {
    int exprValue = expr_->evaluate(varState);
    varState.setValue(varName_, exprValue);
}

InputStmt::InputStmt(std::string varName, const std::string& originLine)
    : Statement(originLine), varName_(std::move(varName)) {
    }

void InputStmt::execute(VarState& varState, Program& program) const {
    while (1) {
        std::cout << " ? ";
        int inputint;
        std::string inputValue;
        getline(std::cin, inputValue);
        try {
            size_t pos = 0;
            inputint = std::stoi(inputValue, &pos);
        
            if (pos == inputValue.length()) {
                varState.setValue(varName_, inputint);
                return;
            }
            else {
                std::cout << "INVALID NUMBER" << std::endl;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "INVALID NUMBER" << std::endl;
        }
    }
    
}

PrintStmt::PrintStmt(Expression* expr, const std::string& originLine)
    : Statement(originLine), expr(expr) {
    }

PrintStmt::~PrintStmt() {
    delete expr;
}

void PrintStmt::execute(VarState& varState, Program& program) const {
    int value = expr->evaluate(varState);
    std::cout << value << std::endl;
}

GotoStmt::GotoStmt(int targetLine, const std::string& originLine)
    : Statement(originLine), targetLine(targetLine) {
    }

void GotoStmt::execute(VarState& varState, Program& program) const {
    program.changePC(targetLine);
}

IfStmt::IfStmt(Expression* leftExpr, char op, Expression* rightExpr, 
               int targetLine, const std::string& originLine)
    : Statement(originLine),
      leftExpr_(leftExpr),
      comparisonOp_(op),
      rightExpr_(rightExpr),
      targetLine_(targetLine) {}

IfStmt::~IfStmt() {
    delete leftExpr_;
    delete rightExpr_;
}

void IfStmt::execute(VarState& varState, Program& program) const {
    int leftValue = leftExpr_->evaluate(varState);
    int rightValue = rightExpr_->evaluate(varState);

    bool conditionMet = false;
    if (comparisonOp_ == '=') {
        conditionMet = (leftValue == rightValue);
    }
    else if (comparisonOp_ == '<') {
        conditionMet = (leftValue < rightValue);
    }
    else if (comparisonOp_ == '>') {
        conditionMet = (leftValue > rightValue);
    }

    if (conditionMet) {
        program.changePC(targetLine_);
    }
}

RemStmt::RemStmt(const std::string& originLine) : Statement(originLine) {
}

void RemStmt::execute(VarState& varState, Program& program) const {
}

EndStmt::EndStmt(const std::string& originLine) : Statement(originLine) {
}

void EndStmt::execute(VarState& varState, Program& program) const {
    program.programEnd();
}

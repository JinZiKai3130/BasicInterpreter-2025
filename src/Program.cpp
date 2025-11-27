// TODO: Imply interfaces declared in the Program.hpp.
#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"
#include "Recorder.hpp"
#include "Statement.hpp"
#include <iostream>
Program::Program() 
    : programCounter_(0), programEnd_(false) {
}

Program::~Program() {
    clear();
}


void Program::addStmt(int line, Statement* stmt) {
    if (line <= 0) {
        throw BasicError("LINE NUMBER ERROR");
    }
    recorder_.add(line, stmt);
}

void Program::removeStmt(int line) {
    if (!recorder_.hasLine(line)) {
        throw BasicError("LINE NUMBER ERROR");
    }
    recorder_.remove(line);
}

void Program::run() {
    resetAfterRun();
    // if (recorder_.lines_.empty()) {
    //     throw("SYNTAX ERROR");
    //     return;
    // }
    programCounter_ = recorder_.getMinLine();
    while (!programEnd_) {
        auto curStmt = recorder_.get(programCounter_);
        try {
            execute(curStmt);
        } catch (const BasicError& e) {
            std::cout << e.message() << std::endl;
        }
        int nexLine = recorder_.nextLine(programCounter_);
        if (nexLine == -1) {
            programEnd_ = true;
        }
        else {
            programCounter_ = nexLine;
        }
    }
}

void Program::list() const {
    recorder_.printLines();
}

void Program::clear() {
    recorder_.clear();
    vars_.clear();

}

void Program::execute(const Statement* stmt) {
    // !stmt possible?
    try {
        stmt->execute(vars_, *this);
    } catch (const BasicError& e) {
        std::cout << e.message() << std::endl;
    }
}

int Program::getPC() const noexcept {
    return programCounter_;
}

void Program::changePC(int line) {
    if (!recorder_.hasLine(line)) {
        throw BasicError("LINE NUMBER ERROR");
    }
    programCounter_ = line;
}

void Program::programEnd() {
    programEnd_ = true;
}

void Program::resetAfterRun() noexcept {
    programCounter_ = 0;
    programEnd_ = false;
    vars_.clear();
}
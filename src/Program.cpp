// TODO: Imply interfaces declared in the Program.hpp.
Program::Program() 
    : programCounter_(0), programEnd_(false) {
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
    
}
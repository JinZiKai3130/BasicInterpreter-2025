#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {
      // TODO: The main function.
      if (line == "QUIT") { break; }
      if (line == "LIST") { program.list(); continue; }
      if (line == "RUN") { program.run(); continue; }
      if (line == "CLEAR") { program.clear(); continue; }
      if (line == "HELP") { std::cout << "my help" << std::endl; continue; }

      auto tokens = lexer.tokenize(line);
      auto parsed_line = parser.parseLine(tokens, line);
      auto stmt = parsed_line.fetchStatement();
      if (parsed_line.getLine() != std::nullopt && stmt != nullptr) {
        int this_line = parsed_line.getLine().value();
        // std::cout << "add" << std::endl;
        program.addStmt(this_line, stmt);
      }
      else if (stmt == nullptr) {
        int this_line = parsed_line.getLine().value();
        // std::cout << "stmt == nullptr" << std::endl;
        program.removeStmt(this_line);
      } 
      else {
        program.execute(stmt);
        // std::cout << "execute" << std::endl;
        delete stmt;
      }
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}
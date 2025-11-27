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
      if (input == "QUIT") break;
      if (input == "LIST") { program.list(); continue; }
      if (input == "RUN") { program.run(); continue; }
      if (input == "CLEAR") { program.clear(); continue; }
      if (input == "HELP") { std::cout << "my help" << std::endl; continue; }

      auto tokens = lexer.tokenize(input);
      auto parsed_line = parser.parseLine(tokens, input);
      if (parsed_line.line_number_ != std::nullopt) {
        program.addStmt(lineNum, stmt);
      }
      else {
        program.execute(stmt);
        stmt.~Statement();
      }
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}
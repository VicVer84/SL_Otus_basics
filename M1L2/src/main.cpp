// OTUS C++ Basic course homework skeleton.
// Lexer using example

#include <iostream>

#include "astnode.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {
    // TODO
    // Implement the next classes:
    // Add
    // Sub
    // Mul
    // Div
    // Variable

    // Without implementation that classes this application works only with numbers

    Lexer lexer(std::cin);
    Parser parser(lexer);

    ASTNode* ast;
    try {
        ast = parser.parse();
    } catch (const std::invalid_argument e) {
        std::cout << e.what();
        return 1;
    }
    
    if (ast) {
         ast->print(std::cout);
    }

    return 0;
}

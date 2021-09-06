// OTUS C++ Basic course homework skeleton.
// Lexer using example


#include <iostream>
#include <memory>

#include "astnode.hpp"
#include "parser.hpp"
#include "astNodeNumber.hpp"
#include "astNodeAdd.hpp"
#include "astNodeSub.hpp"
#include "astNodeMul.hpp"
#include "astNodeDiv.hpp"
#include "astNodeVar.hpp"
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

    ASTNode *ast = parser.parse();
    

    if (ast) {
         ast->print(std::cout);
         delete ast;
    }   

    return 0;
}

#include "parser.hpp"
#include "astNodeNumber.hpp"
#include "astNodeAdd.hpp"
#include "astNodeSub.hpp"
#include "astNodeMul.hpp"
#include "astNodeDiv.hpp"
#include "astNodeVar.hpp"

using Token = Lexer::Token;

ASTNode *Parser::parse() { return expr(); }

void Parser::next_token() {
    tok_ = lexer_.next_token();
}

ASTNode *Parser::expr() {
    // parse addition and subsctraction
    ASTNode *root = term();
    for (;;) {
        switch (tok_) {
            case Token::Operator: {
                std::string op = lexer_.get_operator();
                switch (op.front()) {
                    case '+':
                        // Implement Add class and uncomment this line
                        root = new Add(root, term());                 
                        break;
                    case '-':
                        // Implement Sub class and uncomment this line
                        root = new Sub(root, term());                
                        break;
                    default:
                        return root;
                }
                break;
            }
            case Token::Error:
                return new ASTNode(lexer_.GetError());
            default:
                return root;
        }
    }
}

ASTNode *Parser::term() {
    // parse multiplication and division
    ASTNode *root = prim();
    for (;;) {
        switch (tok_) {
            case Token::Operator: {
                std::string op = lexer_.get_operator();
                switch (op.front()) {
                    case '*':
                        // Implement Mul class and uncomment this line
                        root = new Mul(root, prim());                
                        break;
                    case '/':
                        // Implement Div class and uncomment this line
                        root = new Div(root, prim());
                        break;
                    default:
                        return root;
                }
                break;
            }
            default:
                return root;
        }
    }
}

ASTNode *Parser::prim() {
    // parse numbers and names
    next_token();
    ASTNode* node = brace();
    switch (tok_) {
        case Token::Number:
            node = new Number(lexer_.get_number());
            break;
        case Token::Name:
            // Implement Variable class and uncomment this line
            node = new Variable(lexer_.get_name());        
            break;
        default:
            break;
    }
    next_token();
    return node;
}

ASTNode* Parser::brace() {
    // parse braces
    ASTNode* node = nullptr;
    switch (tok_) {
        case Token::Lbrace:
            node = expr();
            break;
        default:
            break; 
    }
    return node;
}
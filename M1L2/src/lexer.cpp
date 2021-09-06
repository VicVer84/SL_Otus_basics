// OTUS C++ Basic course homework skeleton.
// Lexer implementation

#include "lexer.hpp"

#include <cctype>


Lexer::Token Lexer::next_token() {
    for (;;) {
        switch (state_) {
        case State::End:            
            return TokenValidation(Token::End);
        case State::ReadNumber:
            return ReadNumber(); 
        case State::ReadName:
            return ReadName();
        case State::Empty:
            if (end()) {
                state_ = State::End;
                return TokenValidation(Token::End);
            }
            if (std::isspace(ch_)) {
                next_char();
                break;
            }
            if (isoperator(ch_)) {                
                operator_ = ch_;
                next_char();
                return TokenValidation(Token::Operator);
            }
            if (ch_ == '(') {                
                next_char();
                paranthesis_++;
                return TokenValidation(Token::Lbrace);
            }
            if (ch_ == ')') {                
                next_char();
                paranthesis_--;
                return TokenValidation(Token::Rbrace);
            }
            if (std::isdigit(ch_)) {
                number_ = ch_ - '0';
                state_ = State::ReadNumber;
                next_char();
                break;
            }
            if (std::isalpha(ch_)) {
                name_ = ch_;
                state_ = State::ReadName;
                next_char();
                break;
            }
        }
    }
}

std::string Lexer::GetErrorPos() {
    std::string s = std::to_string(in_.tellg());    
    return std::to_string(std::stoi(s) - 1);
}

Lexer::Token Lexer::ReadNumber() {
    if (end()) {
        state_ = State::End;        
        return TokenValidation(Token::Number);
    }
    while (std::isdigit(ch_)) {
        number_ = 10 * number_ + (ch_ - '0');
        state_ = State::ReadNumber;
        next_char();
    }
    state_ = State::Empty;
    return TokenValidation(Token::Number);
}

Lexer::Token Lexer::ReadName() {
    if (end()) {
        state_ = State::End;        
        return TokenValidation(Token::Name);;
    }    
    while (std::isalpha(ch_) || std::isdigit(ch_)) {
        name_ += ch_;
        next_char();
    }
    state_ = State::Empty;
    return TokenValidation(Token::Name);
}

Lexer::Token Lexer::TokenValidation(Lexer::Token token) {
    switch (token) {
    case Token::Number:
        if (lasttoken_ != Token::Begin && lasttoken_ != Token::Operator && lasttoken_ != Token::Lbrace) {
            status = 1;
            error = "Input error in position (" + GetErrorPos() + "): Number should be the first member of expression otherwise follow operator or leftbrace";
        }        
        break;
    case Token::Name:
        if (lasttoken_ != Token::Begin && lasttoken_ != Token::Operator && lasttoken_ != Token::Lbrace) {
            status = 1;
            error = "Input error in position (" + GetErrorPos() + "): Named member should be the first member of expression otherwise follow operator or leftbrace.";
        }
        break;
    case Token::Operator:
        if (lasttoken_ != Token::Number && lasttoken_ != Token::Name && lasttoken_ != Token::Rbrace) {
            status = 1;
            error = "Input error in position (" + GetErrorPos() + "): Operator should always follow Number or Name";
        }
        break;
    case Token::Lbrace:
        if (lasttoken_ != Token::Begin && lasttoken_ != Token::Lbrace && lasttoken_ != Token::Operator) {
            status = 1;
            error = "Input error in position (" + GetErrorPos() + "): Left brace should be on first position othewise follow lbrace or operator";
        }
        break;
    case Token::Rbrace:
        if (lasttoken_ != Token::Number && lasttoken_ != Token::Name && lasttoken_ != Token::Rbrace) {
            status = 1;
            error = "Input error in position (" + GetErrorPos() + "): Right brace should follow Number, Name or Right brace";
        }
        break;
    case Token::End:
        if (lasttoken_ != Token::Number && lasttoken_ != Token::Name && lasttoken_ != Token::Rbrace) {
            status = 1;
            error = "Input error in position (" + GetErrorPos() + "): Expression should always end with Name, Number or Brace";
        }
        if (paranthesis_ != 0) {
            status = 1;
            error = "Something wrong with paranthesis balance";
        }
    }
    if (status == 1) {
        return Token::Error;
    } else {
        lasttoken_ = token;
        return token;
    }
}
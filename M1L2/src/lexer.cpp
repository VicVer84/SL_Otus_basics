// OTUS C++ Basic course homework skeleton.
// Lexer implementation

#include "lexer.hpp"

#include <cctype>


Lexer::Token Lexer::next_token() {
    for (;;) {
        switch (state_) {
        case State::End:
            if (lasttoken_ != Token::Number && lasttoken_ != Token::Name && lasttoken_ != Token::Rbrace) {
                throw std::invalid_argument("Input error in position (" + GetErrorPos() + "): Expression should always end with Name, Number or Brace");
            }
            if (paranthesis_ != 0) {
                throw std::invalid_argument("Something wrong with paranthesis balance");
            }
            return Token::End;
        case State::ReadNumber:
            try { return ReadNumber(); 
            } catch(...) {
                throw;
            }
        case State::ReadName:
            try {
                return ReadName();
            } catch (...) {
                throw;
            }
        case State::Empty:
            if (end()) {
                state_ = State::End;
                return Token::End;
            }
            if (std::isspace(ch_)) {
                next_char();
                break;
            }
            if (isoperator(ch_)) {
                if (lasttoken_ != Token::Number && lasttoken_ != Token::Name && lasttoken_ != Token::Rbrace) {
                    throw std::invalid_argument("Input error in position (" + GetErrorPos() + "): Operator should always follow Number or Name");
                }
                operator_ = ch_;
                next_char();
                lasttoken_ = Token::Operator;
                return Token::Operator;
            }
            if (ch_ == '(') {
                if (lasttoken_ != Token::Begin && lasttoken_ != Token::Lbrace && lasttoken_ != Token::Operator) {
                    throw std::invalid_argument("Input error in position (" + GetErrorPos() + "): Left brace should be on first position othewise follow lbrace or operator");
                }
                next_char();
                lasttoken_ = Token::Lbrace;
                paranthesis_++;
                return Token::Lbrace;
            }
            if (ch_ == ')') {
                if (lasttoken_ != Token::Number && lasttoken_ != Token::Name && lasttoken_ != Token::Rbrace) {
                    throw std::invalid_argument("Input error in position (" + GetErrorPos() + "): Left brace should be on first position othewise follow lbrace or operator");
                }
                next_char();
                lasttoken_ = Token::Rbrace;
                paranthesis_--;
                return Token::Rbrace;
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
        if (lasttoken_ != Token::Begin && lasttoken_ != Token::Operator && lasttoken_ != Token::Lbrace) {
            throw std::invalid_argument("Input error in position (" + GetErrorPos() + "): Number should be the first member of expression otherwise follow operator or leftbrace");
        }
        lasttoken_ = Token::Number;
        return Token::Number;
    }
    if (lasttoken_ != Token::Begin && lasttoken_ != Token::Operator && lasttoken_ != Token::Lbrace) {
        throw std::invalid_argument("Input error in position (" + GetErrorPos() + "): Number should be the first member of expression otherwise follow operator or leftbrace");
    }
    if (std::isdigit(ch_)) {
        number_ = 10 * number_ + (ch_ - '0');
        state_ = State::ReadNumber;
        next_char();
    }
    state_ = State::Empty;
    lasttoken_ = Token::Number;
    return Token::Number;
}

Lexer::Token Lexer::ReadName() {
    if (end()) {
        state_ = State::End;
        if (lasttoken_ != Token::Begin && lasttoken_ != Token::Operator && lasttoken_ != Token::Lbrace) {
            throw std::invalid_argument("Input error in position (" + GetErrorPos() + "): Named member should be the first member of expression otherwise follow operator or leftbrace.");
        }
        lasttoken_ = Token::Name;
        return Token::Name;
    }
    if (lasttoken_ != Token::Begin && lasttoken_ != Token::Operator && lasttoken_ != Token::Lbrace) {
        throw std::invalid_argument("Input error in position (" + GetErrorPos() + "): Named member should be the first member of expression otherwise follow operator or leftbrace.");
    }
    if (std::isalpha(ch_) || std::isdigit(ch_)) {
        name_ += ch_;
        next_char();
    }
    state_ = State::Empty;
    lasttoken_ = Token::Name;
    return Token::Name;
}
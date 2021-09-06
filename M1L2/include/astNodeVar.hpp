#pragma once

#include <string>

#include "astnode.hpp"

class Variable : public ASTNode {
  public:
    Variable(const std::string &repr) : ASTNode(repr) {}
};

#ifndef TAYLOR_CPP_EXPRESSION_SUBTRACT
#define TAYLOR_CPP_EXPRESSION_SUBTRACT

#include "expression.h"

class ExpressionSubtract: public Expression {

// Attributes.

private:

  const Expression
    *left,                              // Left operand of subtract.
    *right;                             // Right operand of subtract.

// Methods.

public:

  ExpressionSubtract(const Expression &_left, const Expression &_right) {
    left = &_left;
    right = &_right;
    }
  
  Number &count(long digits) const {

#ifdef DEBUG
    LOG("SUBTRACT");
#endif

    Number &number = left->count(digits);
    number -= right->count(digits);

    return number;
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionSubtract(
          left->clone(), right->clone()));
    return copy;
    }
  
  std::string latex() const {
    std::string repr = std::string(" \\left( ");
    repr += left->latex() + " - " + right->latex() + " \\right) ";
    return repr;
    }

  };

#endif

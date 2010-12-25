#ifndef TAYLOR_CPP_EXPRESSION_MULTIPLICATION
#define TAYLOR_CPP_EXPRESSION_MULTIPLICATION

#include "expression.h"

class ExpressionMultiplication: public Expression {

// Attributes.

private:

  const Expression 
    *left,                              // Left operand of sum.
    *right;                             // Right operand of sum.

// Methods.

  int getLeftPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }
  
  int getRightPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }

public:

  ExpressionMultiplication(
      const Expression &_left, const Expression &_right) {
    left = &_left;
    right = &_right;
    }
  
  Number &count(int precision) const {

#ifdef DEBUG
    LOG("MULTIPLICATION");
#endif

    int precision_left = this->getLeftPrecision(precision);
    int precision_right = this->getRightPrecision(precision);

    Number &number = left->count(precision_left);
    number *= right->count(precision_right);

    return number;
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionMultiplication(
          left->clone(), right->clone()));
    return copy;
    }

  };

#endif

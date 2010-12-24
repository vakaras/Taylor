#ifndef TAYLOR_CPP_EXPRESSION_SUM
#define TAYLOR_CPP_EXPRESSION_SUM

#include "expression.h"

class ExpressionSum: public Expression {

// Attributes.

private:

  const Expression 
    *left,                              // Left operand of sum.
    *right;                             // Right operand of sum.

// Methods.

public:

  ExpressionSum(const Expression &_left, const Expression &_right) {
    left = &_left;
    right = &_right;
    }

  Number &count(int precision) const {

#ifdef DEBUG
    LOG("SUM");
#endif

    Number &number = left->count(precision);
    number += right->count(precision);

    return number;
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionSum(left->clone(), right->clone()));
    return copy;
    }
  
  };

#endif

#ifndef TAILOR_CPP_EXPRESSION_NEGATIVE
#define TAILOR_CPP_EXPRESSION_NEGATIVE

#include "expression.h"

class ExpressionNegative: public Expression {

// Attributes.

private:

  const Expression *expression;

// Methods.

public:

  ExpressionNegative(const Expression &_expression) {
    expression = &_expression;
    }
  
  Number &count(int precision) const {

#ifdef DEBUG
    LOG("NEGATIVE");
#endif

    Number &number = expression->count(precision);
    number = -number;

    return number;
    }
  
  Expression &clone() const {
    Expression &copy = *(new ExpressionNegative(expression->clone()));
    return copy;
    }
  
  };

#endif

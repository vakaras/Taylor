#ifndef TAYLOR_CPP_EXPRESSION_E
#define TAYLOR_CPP_EXPRESSION_E

#include "expression.h"
#include "number_exp.h"

class ExpressionE: public Expression {

// Methods.

public:

  ExpressionE() {
    }
  
  Number &count(long digits) const {

    long precision = getEPrecision(digits);

    Number &number = *(new Number(getE(precision)));

    return number;
    }
  
  Expression &clone() const {
    Expression &copy = *(new ExpressionE());
    return copy;
    }
  
  };

#endif

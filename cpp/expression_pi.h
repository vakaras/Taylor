#ifndef TAYLOR_CPP_EXPRESSION_PI
#define TAYLOR_CPP_EXPRESSION_PI

#include "expression.h"
#include "number_pi.h"

class ExpressionPi: public Expression {

// Methods.

public:

  ExpressionPi() {
    }
  
  Number &count(long digits) const {

    long precision = dec_to_bin(digits);

    Number &number = *(new Number(getPi(precision)));

    return number;
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionPi());
    return copy;
    }

  std::string latex() const {
    return std::string(" \\pi ");
    }

  };

#endif

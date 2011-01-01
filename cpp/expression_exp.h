#ifndef TAYLOR_CPP_EXPRESSION_EXP
#define TAYLOR_CPP_EXPRESSION_EXP

#include "expression.h"
#include "number_exp.h"

class ExpressionExp: public Expression {

// Attributes.

private:

  const Expression *argument;           // Expression of cos argument.

// Methods.

  /** 
   * Calculates, how accurate in decimal digits the argument have to be
   * that it would be possible to calculate exp in given precision.
   * @param precision precision of sin result in decimal digits.
   */
  long getArgumentPrecision(long precision) const {
    // FIXME: Write normal.
    return precision;
    }

public:

  ExpressionExp(const Expression &_argument) {
    argument = &_argument;
    }
  
  Number &count(long digits) const {

    long precision_argument = this->getArgumentPrecision(digits);
    long precision = getEPrecision(digits);

    Number &number = argument->count(precision_argument);

    return exp(number);
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionExp(argument->clone()));
    return copy;
    }

  };

#endif

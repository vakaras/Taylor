#ifndef TAYLOR_CPP_EXPRESSION_LN
#define TAYLOR_CPP_EXPRESSION_LN

#include "expression.h"
#include "number_exp.h"

class ExpressionLn: public Expression {

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

  ExpressionLn(const Expression &_argument) {
    argument = &_argument;
    }
  
  Number &count(long digits) const {

    long precision_argument = this->getArgumentPrecision(digits);
                                        // TODO: Check if works.

    Number &number = argument->count(precision_argument);

    return ln(number);
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionLn(argument->clone()));
    return copy;
    }

  std::string latex() const {
    std::string repr = std::string(" \\ln ");
    repr += argument->latex();
    return repr;
    }

  };

#endif

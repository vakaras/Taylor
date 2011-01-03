#ifndef TAYLOR_CPP_EXPRESSION_SIN
#define TAYLOR_CPP_EXPRESSION_SIN

#include "expression.h"
#include "number_pi.h"
#include "number_trigonometry.h"

class ExpressionSin: public Expression {

// Attributes.

private:

  const Expression *argument;           // Expression of sin argument.
  
// Methods.

  /** 
   * Calculates, how accurate in decimal digits the argument have to be
   * that it would be possible to calculate sin in given precision.
   * @param precision precision of sin result in decimal digits.
   */
  long getArgumentPrecision(long precision) const {
    // FIXME: Write normal.
    return precision;
    }
  
public:

  ExpressionSin(const Expression &_argument) {
    argument = &_argument;
    }

  Number &count(long digits) const {

#ifdef DEBUG
    LOG("SIN");
#endif

    long precision_argument = this->getArgumentPrecision(digits);
    long precision = dec_to_bin(digits);

    Number &number = argument->count(precision_argument);

    return sin(
        number,
        getPi(precision),
        getPi2(precision),
        getPi4(precision)
        );
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionSin(argument->clone()));
    return copy;
    }

  std::string latex() const {
    std::string repr = std::string(" \\sin ");
    repr += argument->latex();
    return repr;
    }

  };

#endif

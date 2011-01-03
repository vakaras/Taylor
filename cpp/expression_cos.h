#ifndef TAYLOR_CPP_EXPRESSION_COS
#define TAYLOR_CPP_EXPRESSION_COS

#include "expression.h"
#include "number_pi.h"
#include "number_trigonometry.h"

class ExpressionCos: public Expression {

// Attributes.

private:

  const Expression *argument;           // Expression of cos argument.

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

  ExpressionCos(const Expression &_argument) {
    argument = &_argument;
    }
  
  Number &count(long digits) const {

#ifdef DEBUG
    LOG("COS");
#endif

    long precision_argument = this->getArgumentPrecision(digits);
    long precision = dec_to_bin(digits);

    Number &number = argument->count(precision_argument);

    return cos(
        number,
        getPi(precision),
        getPi2(precision),
        getPi4(precision)
        );
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionCos(argument->clone()));
    return copy;
    }

  std::string latex() const {
    std::string repr = std::string(" \\cos ");
    repr += argument->latex();
    return repr;
    }
  
  };

#endif

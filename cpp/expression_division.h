#ifndef TAYLOR_CPP_EXPRESSION_DIVISION
#define TAYLOR_CPP_EXPRESSION_DIVISION

#include "expression.h"

class ExpressionDivision: public Expression {

// Attributes.

private:

  const Expression
    *numerator,
    *denominator;
// Methods.

  long getNumeratorPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }
  
  long getDenominatorPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }
  
public:

  ExpressionDivision(
      const Expression &_numerator, const Expression &_denominator) {
    numerator = &_numerator;
    denominator = &_denominator;
    }
  
  Number &count(long digits) const {

#ifdef DEBUG
    LOG("DIVISION");
#endif

    long precision_numerator = this->getNumeratorPrecision(digits);
    long precision_denominator = this->getDenominatorPrecision(digits);

    Number &number = numerator->count(precision_numerator);
    number /= denominator->count(precision_denominator);

    return number;
    }
  
  Expression &clone() const {
    Expression &copy = *(new ExpressionDivision(
          numerator->clone(), denominator->clone()));
    return copy;
    }
  
  };

#endif

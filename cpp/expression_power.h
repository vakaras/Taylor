#ifndef TAYLOR_CPP_EXPRESSION_POWER
#define TAYLOR_CPP_EXPRESSION_POWER

#include "expression.h"

/// Expression a^{x}
class ExpressionPower: public Expression {

// Attributes.

private:

  const Expression 
    *argument,                          // Expression of power argument.
    *power;                             // Expression of power.

// Methods.

  int getArgumentPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }
  
  int getPowerPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }

public:

  ExpressionPower(const Expression &_argument, const Expression &_power) {
    argument = &_argument;
    power = &_power;
    }
  
  Number &count(long digits) const {

#ifdef DEBUG
    LOG("POWER");
#endif

    // TODO: Make refactoring.
    long precision = dec_to_bin(digits);     // TODO: Check if correct.

    long precision_argument = this->getArgumentPrecision(digits);
    long precision_power = this->getPowerPrecision(digits);

    Number one(1, precision);

    Number &number = *(new Number(1, precision));
                                        // sum
    Number &argument = this->argument->count(precision_argument);
    argument -= one;
                                        // x
    Number &degree = this->power->count(precision_power);
                                        // a
    Number toAdd = Number(1, precision);
                                        // \frac{a\cdots (a-n+1)}{n!}
    Number remainder(1, precision);
    remainder >>= precision;            // 2^{-a}

    int i = 1;
    while (toAdd.cmpAbs(remainder) > 0) {
      // TODO: Add check for cases with possibly wrong precision.

      toAdd *= argument;                // \frac%
                                        // {a\cdots (a-n+2)\cdot x^n}%
                                        // {(n-1)!}
      toAdd *= degree;                  // \frac%
                                        // {a\cdots (a-n+1)\cdot x^n}%
                                        // {(n-1)!}
      degree -= one;                    // a-n
      toAdd /= Number(i++, precision);  // \frac%
                                        // {a\cdots (a-n+1)\cdot x^n}%
                                        // {n!}
      number += toAdd;
      }

    return number;
    }
  
  Expression &clone() const {
    Expression &copy = *(new ExpressionPower(
          argument->clone(), power->clone()));
    return copy;
    }
  
  };

#endif


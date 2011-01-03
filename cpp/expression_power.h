#ifndef TAYLOR_CPP_EXPRESSION_POWER
#define TAYLOR_CPP_EXPRESSION_POWER

#include "expression.h"
#include "number_exp.h"

/// Expression a^{x}
class ExpressionPower: public Expression {

// Attributes.

private:

  const Expression 
    *base,                              // Expression of base.
    *power;                             // Expression of power.

// Methods.

  int getBasePrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }
  
  int getPowerPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }

public:

  ExpressionPower(const Expression &_base, const Expression &_power) {
    base = &_base;
    power = &_power;
    }
  
  Number &count(long digits) const {

#ifdef DEBUG
    LOG("POWER");
#endif

    //long precision = dec_to_bin(digits);     

    long precision_base = this->getBasePrecision(digits);
                                        // TODO: Check if correct.
    long precision_power = this->getPowerPrecision(digits);
                                        // TODO: Check if correct.

    Number &base = this->base->count(precision_base);
    Number &power = this->power->count(precision_power);

    return exp(power * ln(base));
    }
  
  Expression &clone() const {
    Expression &copy = *(new ExpressionPower(
          base->clone(), power->clone()));
    return copy;
    }
  
  std::string latex() const {
    std::string repr = std::string(" ");
    repr += base->latex() + " ^{" + power->latex() + " } ";
    return repr;
    }
  
  };

#endif

#ifndef TAYLOR_CPP_EXPRESSION_MULTIPLICATION
#define TAYLOR_CPP_EXPRESSION_MULTIPLICATION

#include "expression.h"

class ExpressionMultiplication: public Expression {

// Attributes.

private:

  const Expression 
    *left,                              // Left operand of sum.
    *right;                             // Right operand of sum.

// Methods.

  long getLeftPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }
  
  long getRightPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }

public:

  ExpressionMultiplication(
      const Expression &_left, const Expression &_right) {
    left = &_left;
    right = &_right;
    }
  
  Number &count(long digits) const {

#ifdef DEBUG
    LOG("MULTIPLICATION");
#endif

    // TODO: Check code.
    //
    long digits_left = this->getLeftPrecision(digits);
    long digits_right = this->getRightPrecision(digits);

    Number &number = left->count(digits_left);
    // TODO Check if argument precision can be used.
    number *= right->count(digits_right);

    return number;
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionMultiplication(
          left->clone(), right->clone()));
    return copy;
    }

  std::string latex() const {
    std::string repr = std::string(" \\left( ");
    repr += left->latex() + " * " + right->latex() + " \\right) ";
    return repr;
    }

  };

#endif

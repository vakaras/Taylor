#ifndef TAYLOR_CPP_EXPRESSION_INTEGER
#define TAYLOR_CPP_EXPRESSION_INTEGER

#include "expression.h"

class ExpressionInteger: public Expression {

// Attributes.

private:

  long value;

// Methods.

public:

  ExpressionInteger(): value(0) {
    }

  ExpressionInteger(int _value): value(_value) {
    }

  Number &count(long digits) const {

#ifdef DEBUG
    LOG("NUMBER")
    LOG(value)
#endif

    long precision = dec_to_bin(digits);

    Number &number = *(new Number(this->value, precision));

    return number;
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionInteger(this->value));
    return copy;
    }

  std::string latex() const {
    char a[((int) (2.5 * ((double) sizeof(value)))) + 2];
    sprintf(a, "%ld", value);
    return std::string(a);
    }

  };

#endif

#ifndef TAYLOR_CPP_EXPRESSION_SIN
#define TAYLOR_CPP_EXPRESSION_SIN

#include "expression.h"
#include "number_pi.h"

class ExpressionSin: public Expression {

// Attributes.

private:

  const Expression *argument;           // Expression of sin argument.
  
// Methods.

  int getArgumentPrecision(int precision) const {
    // FIXME: Write normal.
    return precision;
    }
  
public:

  ExpressionSin(const Expression &_argument) {
    argument = &_argument;
    }

  Number &count(int precision) const {

#ifdef DEBUG
    LOG("SIN");
#endif

    int precision_argument = this->getArgumentPrecision(precision);

    Number &number = argument->count(precision_argument);
                                        // x, sum
    // Minimizing argument to [-pi; pi]
    Number const &pi = getPi(precision);

    Number multiplier = number / pi;
    multiplier >>= 1;
    multiplier.floor();
    multiplier *= pi;
    multiplier <<= 1;
    number -= multiplier;

    // Calculating using Taylor.
    Number numberSquare = number * number;
                                        // x^{2}
    Number toAdd = number;              // \frac{x^n}{n!}

    Number remainder(1, precision);      
    remainder >>= precision;            // 2^{-a}

    int i = 2;
    while (toAdd.cmpAbs(remainder) > 0) {
      // TODO: Add check for cases with possibly wrong precision.
      
      toAdd *= numberSquare;            // \frac{x^n}{(n-2)!}
      toAdd /= Number((i)*(i+1), precision);     
                                        // \frac{x^n}{n!} 
      i += 2;

      if (!(i % 4)) {
        number -= toAdd;
        //std::cout << "to add: -" << toAdd.asString() << std::endl;
        }
      else {
        number += toAdd;
        //std::cout << "to add: +" << toAdd.asString() << std::endl;
        }
      //std::cout << "number: " << number.asString() << std::endl;
      
      }

    return number;
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionSin(argument->clone()));
    return copy;
    }

  };

#endif

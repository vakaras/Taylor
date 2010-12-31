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
  
  Number &count(int digits) const {

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

//  Number &numberSquare = argument->count(precision_argument);
//  numberSquare.sqr();                 // x^{2}

//  Number &number = *(new Number(1, precision));        
//                                      // sum

//  Number toAdd(1, precision);         // \frac{x^n}{n!}

//  Number remainder(1, precision);
//  remainder >>= precision;            // 2^{-a}

//  int i = 2;
//  while (toAdd.cmpAbs(remainder) > 0) {
//    // TODO: Add check for cases with possibly wrong precision.
//    
//    //std::cout << "  to add 1: " << toAdd.asString() << std::endl;
//    toAdd *= numberSquare;            // \frac{x^n}{(n-2)!}
//    //std::cout << "  to add 2: " << toAdd.asString() << std::endl;
//    toAdd /= Number(i*(i-1), precision);
//                                      // \frac{x^n}{n!}
//    //std::cout << "  to add 3: " << toAdd.asString() << std::endl;
//    i += 2;
//    if (!(i % 4)) {
//      //std::cout << "to add: -" << toAdd.asString() << std::endl;
//      number -= toAdd;
//      }
//    else {
//      //std::cout << "to add: +" << toAdd.asString() << std::endl;
//      number += toAdd;
//      //std::cout << "to add: +" << toAdd.asString() << std::endl;
//      }
//    //std::cout << "number: " << number.asString() << std::endl;
//    }
//  
//  return number;
    }

  Expression &clone() const {
    Expression &copy = *(new ExpressionCos(argument->clone()));
    return copy;
    }
  
  };

#endif

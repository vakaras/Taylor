#ifndef TAYLOR_CPP_NUMBER_PI
#define TAYLOR_CPP_NUMBER_PI

#include "number.h"

/// Atan function optimized for pi calculation.
/**
 * ataninv(x) = 1/x - 1/(3x) + 1/(5x) - 1/(7x) + \cdots
 */
Number ataninvint(long x, long precision) {

  Number number(0, precision);          // sum

  Number term(1, precision);            // \frac{1}{x^{n}}
  term /= x;
  //std::cout << "term: " << term.asString() << std::endl;

  long xSquare = x*x;

  Number *toAdd = NULL;                 // \frac{1}{x^n \cdot n}

  Number remainder(1, precision);       // 2^{a} TODO: Check if this method
                                        // is correct.
  remainder >>= precision;

  for (int i = 1; ; i+=2) {
    toAdd = &(term / i);
    if ((i % 4) == 1) {
      number += *toAdd;
      }
    else {
      number -= *toAdd;
      }
    //std::cout << number.asString() << std::endl;
    if (toAdd->cmpAbs(remainder) <= 0) {
      break;
      }
    term /= xSquare;
    }

  return number;
  }

/// Returns pi/4 as Number in given precision.
const Number &getPi4(long precision) {

  static Number *pi4 = NULL;

  if ((!pi4) || (pi4 && pi4->getPrecision() < precision)) {
    if (pi4)
      delete pi4;
    pi4 = new Number(ataninvint(5, precision));
    *pi4 <<= 2;
    *pi4 -= ataninvint(239, precision);
    }
  
  return *pi4;
  }

/// Returns pi as number in given precision.
const Number &getPi(long precision) {

  static Number *pi = NULL;

  if ((!pi) || (pi && pi->getPrecision() < precision)) {
    if (pi)
      delete pi;
    pi = new Number(getPi4(precision));
    *pi <<= 2;
    }

  return *pi;
  }

#endif

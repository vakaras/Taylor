#ifndef TAYLOR_CPP_NUMBER_EXP
#define TAYLOR_CPP_NUMBER_EXP

#include "number.h"

/// Calculates x^{n}
Number &pow(const Number &x, const Number &n) {

  /*
   *
   *To expand on what user923005 wrote, computing pow(x,y) as using Taylor
series to evaluate exp(y*ln(x)) certainly works to some extent. 
   */
  }

/// Calculates e^{x}
Number &exp(const Number &x) {

  Number &result = *(new Number(1, x.getPrecision()));    
                                        // 1 + \frac{x^1}{1!} + \cdots
  Number remainder(1, x.getPrecision());
                                        // 2^{-precision}
  remainder >>= x.getPrecision();
  Number toAdd(x);                      // \frac{x^n}{n!}

  for (int i = 2; toAdd.cmpAbs(remainder) > 0; i++) {
    result += toAdd;
    toAdd *= x;
    toAdd /= i;
    }
  
  return result;
  }

long getEPrecision(long digits) {
  return dec_to_bin(digits);
  }

const Number &getE(long precision) {

  static Number *e = NULL;

  if ((!e) || (e && e->getPrecision() < precision)) {
    if (e)
      delete e;
    e = &exp(*(new Number(1, precision)));
    }
  
  return *e;
  }

/// Calculates ln(x)
Number &ln(const Number &x) {

  }

#endif

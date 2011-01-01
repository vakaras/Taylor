#ifndef TAYLOR_CPP_NUMBER_EXP
#define TAYLOR_CPP_NUMBER_EXP

#include "exceptions.h"
#include "number.h"

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

/// Returns e of requested precision.
/**
 * This function is not thread safe.
 */
const Number &getE(long precision) {

  static Number *e = NULL;

  if ((!e) || (e && e->getPrecision() < precision)) {
    if (e)
      delete e;
    e = &exp(*(new Number(1, precision)));
    }
  
  return *e;
  }

/// Calculates ln(1 + x), when x \in [-\frac{1}{2}; \frac{1}{2}]
Number &ln_2(const Number &x) {
  
  Number &result = *(new Number(x));
  Number remainder(1, x.getPrecision());
                                        // 2^{-precision}
  remainder >>= x.getPrecision();
  Number toAdd(x);
  
  for (int i = 2; toAdd.cmpAbs(remainder) > 0; i++) {
    toAdd *= x;
    toAdd.negative();                   // Change sign.
    result += toAdd / i;
    }

  return result;
  }

/// Calculates ln(z)
/**
 * Modifies argument.
 */
Number &ln(Number &z) {

  if (z <= 0.0) {
    throw ValueError("ln argument should be positive.");
    }

  if (z <= 0.5) {
    z *= getE(z.getPrecision());        // TODO: Check precision.
    Number &result = ln(z);
    result -= 1;
    return result;
    }

  if (z >= 1.5) {
    z /= getE(z.getPrecision());        // TODO: Check precision.
    Number &result = ln(z);
    result += 1;
    return result;
    }
  
  z -= 1;
  return ln_2(z);
  }

#endif

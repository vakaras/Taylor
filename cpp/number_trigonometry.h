#ifndef TAYLOR_CPP_NUMBER_TRIGONOMETRY
#define TAYLOR_CPP_NUMBER_TRIGONOMETRY

#include "number.h"
#include "number_pi.h"

/// Calculates sin, when the argument is from interval [-pi/4; pi/4]
/** 
 * Uses argument precision.
 */
Number &sin_pi2(const Number &x) {

  Number &result = *(new Number(x));    // x - \frac{x^{3}}{3!} + \cdots
  Number xSquare = x * x;               // x^{2}
  Number remainder(1, x.getPrecision());
                                        // 2^{-precision}
  remainder >>= x.getPrecision();
  Number toAdd(x);                      // \frac{x^{2k+1}}{(2k+1)!}

  for (int i = 3; toAdd.cmpAbs(remainder) > 0; i += 2) {
    toAdd *= xSquare;
    toAdd /= (i-1)*i;
    if (i % 4 == 3) {
      result -= toAdd;
      }
    else {
      result += toAdd;
      }
    }

  return result;
  }

/// Calculates cos, when the argument is from interval [-pi/4; pi/4]
/** 
 * Uses argument precision.
 */
Number &cos_pi2(const Number &x) {

  Number &result = *(new Number(1, x.getPrecision()));
                                        // 1 - \frac{x^2}{2!} + \cdots
  Number xSquare = x * x;               // x^{2}
  Number remainder(1, x.getPrecision());
                                        // 2^{-precision}
  remainder >>= x.getPrecision();
  Number toAdd(1, x.getPrecision());

  for (int i = 2; toAdd.cmpAbs(remainder) > 0; i+=2) {
    toAdd *= xSquare;
    toAdd /= (i-1)*i;
    if (i % 4 == 2) {
      result -= toAdd;
      }
    else {
      result += toAdd;
      }
    }
  
  return result;
  }

/// Minimizes given positive argument to interval [0; 2pi]
/** 
 * Uses argument precision.
 */
void minimize(Number &x, const Number &pi) {
  Number multiplier = x / pi;
  multiplier >>= 1;
  multiplier.floor();
  multiplier *= pi;
  multiplier <<= 1;
  x -= multiplier;
  }

/// Calculates sin.
/** 
 * Uses argument precision. Modifies argument.
 */
Number &sin(
    Number &x, const Number &pi, const Number &pi2, const Number &pi4) {

  if (x.isNegative()) {
    x.negative();
    Number &result = sin(x, pi, pi2, pi4);
    result.negative();
    return result;
    }

  minimize(x, pi);                      // x \in [0; 2 \pi]
  x -= pi;                              
  x.negative();                          // x \in [-\pi; \pi]
  if (x.cmpAbs(pi4) <= 0) {
    // if x \in [-pi/4; pi/4]
    return sin_pi2(x);
    }
  if (x.isNegative()) {
    // if x \in [-pi; -pi/4]
    if (x.cmpAbs(pi - pi4) >= 0) {
      // if x \in [-pi; -3pi/4]
      x += pi;
      x.negative();
      return sin_pi2(x);
      }
    else {
      // if x \in [-3pi/4; -pi/4]
      x += pi2;
      Number &result = cos_pi2(x);
      result.negative();
      return result;
      }
    }
  else {
    // if x \in [pi/4; pi]
    if (x.cmpAbs(pi - pi4) >= 0) {
      // if x \in [3pi/4; pi]
      x -= pi;
      x.negative();
      return sin_pi2(x);
      }
    else {
      // if x \in [pi/4; 3pi/4]
      x -= pi2;
      return cos_pi2(x);
      }
    }
  
  assert(0);                            // Unreachable code.
  return *(new Number(0, 0));
  }

/// Calculates cos.
/** 
 * Uses argument precision. Modifies argument.
 */
Number &cos(
    Number &x, const Number &pi, const Number &pi2, const Number &pi4) {

  if (x.isNegative()) {
    x.negative();
    }
  
  minimize(x, pi);                      // x \in [0; 2 \pi]
  x -= pi;                              // -cos(x), x \in [-\pi; \pi]
  if (x.cmpAbs(pi4) <= 0) {
    // if x \in [-pi/4; pi/4]
    Number &result = cos_pi2(x);
    result.negative();
    return result;
    }
  if (x.isNegative()) {
    // if x \in [-pi; -pi/4]
    if (x.cmpAbs(pi - pi4) >= 0) {
      // if x \in [-pi; -3pi/4]
      x += pi;
      return cos_pi2(x);
      }
    else {
      // if x \in [-3pi/4; -pi/4]
      x += pi2;
      x.negative();
      return sin_pi2(x);
      }
    }
  else {
    // if x \in [pi/4; pi]
    if (x.cmpAbs(pi - pi4) >= 0) {
      // if x \in [3pi/4; pi]
      x -= pi;
      return cos_pi2(x);
      }
    else {
      // if x \in [pi/4; 3pi/4]
      x -= pi2;
      x.negative();
      return sin_pi2(x);
      }
    }
  }

#endif

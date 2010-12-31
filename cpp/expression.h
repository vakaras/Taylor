#ifndef TAYLOR_CPP_EXPRESSION
#define TAYLOR_CPP_EXPRESSION

#include <string>

#include "utils.h"
#include "number.h"

// Base expression class.
/**
 * WARNING: Because this class is abstract, creating its instances copies 
 * is responsibility of the caller.
 */
class Expression {

// Methods.

public:

  virtual Number &count(long precision) const = 0;

  /// Returns latex math mode representation of the expression.
  //virtual std::string &latex() const = 0;
  //                                    TODO
  
  /// Copy constructor.
  virtual Expression &clone() const = 0;

  /// Returns string representation of number in normal form.
//std::string asNormalString(int precision, int base=10) {
//  // TODO
//  }
  
  /// Returns string representation of number in plain form.
  std::string asString(long digits) {
    return this->count(digits).asFormatedString(digits);
    }

  };

#endif

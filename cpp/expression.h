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

  virtual Number &count(int precision) const = 0;

  /// Returns latex math mode representation of the expression.
  //virtual std::string &latex() const = 0;
  //                                    TODO

  /// Copy constructor.
  virtual Expression &clone() const = 0;
  
  std::string asString(int precision, int base=10) {
    // TODO: Add function, which translates base 10 precision to base 2.
    return this->count(precision).asString(base);
    }

  };

#endif

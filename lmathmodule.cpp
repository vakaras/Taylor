#include <iostream>

#include <cstring>
#include <gmp.h>
#include <mpfr.h>

#define DEBUG 1
#ifdef DEBUG
#define LOG(a) cout << "DEBUG: " << a << endl;
#endif

using namespace std;

void swap( int &x, int &y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void say_hello(const char* name) {
    int a = 1, b = 2;
    cout << "a = " << a << " b = " << b << endl;
    cout << "Hello " <<  name << "!\n";
}

struct World
{
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

/// Wrapper class for MPFR library.
/**
 * Should be used as temporary object for counting value.
 */
class Number {

// Attributes.

protected:

  mpfr_t value;

// Methods.
public:

  Number(int integer, int precision) {
    mpfr_init2(this->value, precision);
    mpfr_set_si(this->value, integer, GMP_RNDD);
    }

  ~Number() {
    mpfr_clear(this->value);
    }

  /// Returns string representation of a number.
  /**
   * @param base in what base number should be represented.
   * @return number as C++ string in given base.
   */
  std::string asString(int base=10) {

    mpfr_exp_t exp;

    char *representation = mpfr_get_str(
        NULL, &exp, base, 0, this->value, GMP_RNDD);

    int len = strlen(representation);
    std::string &str = *(new std::string);
    str.resize(len+1);

    for (int i = 0; i < exp; i++) {
      str[i] = representation[i];
      }
    str[exp] = ',';                     // FIXME: Hardcoded value.
    for (int i = exp; i < len; i++) {
      str[i+1] = representation[i];
      }

    mpfr_free_str(representation);

    return str;
    }

  /// Adds another number to this. 
  /**
   * This number precision is used.
   */
  void operator += (const Number &other) {
    mpfr_add(this->value, this->value, other.value, GMP_RNDD);
    }

  };

// For header.
class Expression;
class ExpressionSum;

/// Base expression class.
class Expression {

// Methods.

public:

  Number &count(int precision) {
    }

  Expression &operator + (const Expression &other); 

  std::string asString(int precision, int base=10) {
    // TODO: Add function, which translates base 10 precision to base 2.
    return this->count(precision).asString(base);
    }

  };

/// Class representing single integer.
class ExpressionInteger {

// Attributes.

private:

  long value;
  
// Methods.

public:

  /// Counts expression value with given binary precision.
  Number &count(int precision) {
#ifdef DEBUG
    LOG("NUMBER")
    LOG(value)
#endif

    Number &number = *(new Number(value, precision));

    return number;
    }

  ExpressionInteger(): value(0) {
    }

  ExpressionInteger(int _value): value(_value) {
    }

  std::string asString(int precision, int base=10) {
    // TODO: Add function, which translates base 10 precision to base 2.
    return this->count(precision).asString(base);
    }

  };

/// Class representing sum of two expressions.
class ExpressionSum: public Expression {

// Attributes.

private:

  Expression left, right;

// Methods.

public:

  ExpressionSum(const Expression _left, const Expression _right) {
    this->left = _left;
    this->right = _right;
    }
  
  /// Counts expression value with given binary precision.
  Number &count(int precision) {

#ifdef DEBUG
    LOG("SUM")
#endif
    Number &number = left.count(precision);
    number += right.count(precision);

    return number;
    }

/*
  Expression &operator + (const Expression &other) {
    Expression &sum = *(new ExpressionSum(*this, other));
    return sum;
    }
*/

  };

Expression &Expression::operator + (const Expression &other) {
  ExpressionSum &sum = *(new ExpressionSum(*this, other));
  return sum;
  }

/*
ExpressionSum &operator + (const Expression &a, const Expression &b) {
  ExpressionSum &sum = *(new ExpressionSum(a, b));
  return sum;
  }
*/

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>
using namespace boost::python;
 
BOOST_PYTHON_MODULE(lmath)
{
    def("say_hello", say_hello);
    class_<World>("World")
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;
    class_<Number>("Number", init<int, int>())
      .def("asString", &Number::asString)
      ;
    class_<Expression>("Expression", init<>())
      .def("asString", &Expression::asString)
      .def(self + self)
      ;
}

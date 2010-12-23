#include <iostream>

#include <cstring>
#include <gmp.h>
#include <mpfr.h>

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

  };


/// Base expression class representing single integer.
class Expression {

// Attributes.

private:

  long value;
  
// Methods.

protected:

  /// Counts expression value with given binary precision.
  Number &count(int precision) {
    // TODO: Add function, which translates base 10 precision to base 2.

    Number &number = *(new Number(value, precision));

    return number;
    }

public:

  Expression(int _value): value(_value) {
    }

  };
 
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
}

#ifndef TAYLOR_CPP_NUMBER
#define TAYLOR_CPP_NUMBER

#include <cstring>
#include <string>
#include <gmp.h>
#include <mpfr.h>

#include "utils.h"

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

  /// Default constructor.
  /**
   * @param integer is initial Number value.
   * @param precision the length of number in memory in bits.
   */
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

    //std::cout << exp << std::endl;

    int comma_pos = exp;                // Comma position in representation.
    int move = 1;                       // When copying, how much to move
                                        // cursor.
    if (representation[0] == '-') {
      comma_pos++;
      }

    //std::cout << exp << std::endl;
    //std::cout << representation << std::endl;

    if (exp > 0) {
      str.resize(len+1);
      for (int i = 0; i < comma_pos; i++) {
        str[i] = representation[i];
        }
      str[comma_pos] = ',';                   // FIXME: Hardcoded value.
      }
    else {
      // If there is no digits before comma.
      //std::cout << exp << std::endl;
      str.resize(len+2);
      str[0] = representation[0];
      str[comma_pos] = '0';
      str[comma_pos+1] = ',';           // FIXME: Hardcoded value.
      move++;
      }
    
    for (int i = comma_pos; i < len; i++) {
      str[i+move] = representation[i];
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

  /// Substracts another number from this. 
  /**
   * This number precision is used.
   */
  void operator -= (const Number &other) {
    mpfr_sub(this->value, this->value, other.value, GMP_RNDD);
    }

  };

#endif

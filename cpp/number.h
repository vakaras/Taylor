#ifndef TAYLOR_CPP_NUMBER
#define TAYLOR_CPP_NUMBER

#include <cstring>
#include <string>
#include <cmath>
#include <gmp.h>
#include <mpfr.h>

#include "utils.h"
#include "exceptions.h"

// Helper functions.

/// Converts decimal precision to binary.
long dec_to_bin(long decimal) {
  static double lg = log(10)/log(2);
  return (((double) decimal) * lg) + 16;
  }

/// Converts binary precision to decimal.
long bin_to_dec(long decimal) {
  static double lg = log(10)/log(2);
  return ceil((((double) decimal) / lg));
  }

/// Wrapper class for MPFR library.
/**
 * Should be used as temporary object for counting value.
 */
class Number {

// Attributes.

protected:

  long precision;
  mpfr_t value;

// Methods.
public:

  /// Default constructor.
  /**
   * @param integer is initial Number value.
   * @param precision the length of number in memory in bits.
   */
  Number(long integer, long _precision) {
    this->precision = _precision;
    mpfr_init2(this->value, this->precision);
    mpfr_set_si(this->value, integer, GMP_RNDD);
    this->validate();
    }

  /// Copy number.
  Number(const Number &number) {
#ifdef DEBUG
    LOG("COPYING NUMBER");
#endif
    this->precision = number.precision;
    mpfr_init2(this->value, this->precision);
    mpfr_set(this->value, number.value, GMP_RNDD);
    }

  /// Copy number with new precision.
  Number(const Number &number, long _precision) {
    this->precision = _precision;
    mpfr_init2(this->value, this->precision);
    mpfr_set(this->value, number.value, GMP_RNDD);
    }

  ~Number() {
    mpfr_clear(this->value);
    }

  /// Validates if number is in correct form.
  /* If it is not, then throws Exception.
   */
  void validate() {
    mpfr_exp_t exp = mpfr_get_exp(this->value);
    if (exp > this->precision) {
      throw OverflowException();
      }
    }

  long getPrecision() const {
    return this->precision;
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
    int newLen = len + 1;               // The length of str.
    bool negative = representation[0] == '-'; 
                                        // If the number is negative.

    if (exp <= 0) {
      newLen += -exp + 1;
      }

    str.resize(newLen);

    if (negative) {
      str[0] = '-';
      }

    int i, j = 0 + negative;
    for (i = 0 + negative; i < exp + negative; i++) {         
                                        // If number is greater than 1.
      str[i] = representation[j++];
      }
    if (exp <= 0) {
      str[i++] = '0';
      str[i++] = UTILS_COMMA;
      for (; exp < 0; i++ && exp++) {
                                          // If number is smaller than 1.
        str[i] = '0';
        }
      }
    else {
      str[i++] = UTILS_COMMA;
      }
    for (; j < len; j++) {
      str[i++] = representation[j];
      }

    mpfr_free_str(representation);
    return str;

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
      str[comma_pos] = UTILS_COMMA;
      }
    else {
      // If there is no digits before comma.
      //std::cout << exp << std::endl;
      str.resize(len+2);
      str[0] = representation[0];
      str[comma_pos] = '0';
      str[comma_pos+1] = UTILS_COMMA;
      move++;
      }
    
    for (int i = comma_pos; i < len; i++) {
      str[i+move] = representation[i];
      }

    mpfr_free_str(representation);

    return str;
    }

  /// Returns string representation in form like "%*.*Rf"
  std::string asFormatedString(
      const char *templ, long width, long precision) {
    // FIXME: Not DRY code.

    char *representation;
    if (mpfr_asprintf(
          &representation, templ, width, precision, this->value) < 0) {
      throw ConversionError();
      }

    return std::string(representation);
    }

  /// Returns string representation in form "%*Rf" with given width.
  std::string asFormatedString(long width) {
    // FIXME: Not DRY code.

    mpfr_exp_t exp = mpfr_get_exp(this->value);
    long decExp = bin_to_dec(exp);
    long precision;

    if (mpfr_zero_p(this->value)) {
      decExp = 0;
      }

    if (width <= decExp) {
      throw FormattingError("Given width is too small.");
      }
    else {
      precision = width - 1 - decExp;
      }

    char *representation;

    if (mpfr_asprintf(
            &representation, "%*.*Rf", width, precision, this->value
            ) < 0) {
      throw ConversionError();
      }

    return std::string(representation);
    }
 
  /// Returns string representation in form like "%Rf"
  std::string asFormatedString(const char *templ) {
    // FIXME: Not DRY code.

    char *representation;
    if (mpfr_asprintf(&representation, templ, this->value) < 0) {
      throw ConversionError();
      }

    return std::string(representation);
    }

  /// Adds another number to this. 
  /**
   * This number precision is used.
   */
  void operator += (const Number &other) {
    mpfr_add(this->value, this->value, other.value, GMP_RNDD);
    this->validate();
    }
  
  /// Adds another number to this. 
  /**
   * This number precision is used.
   */
  void operator += (const long &other) {
    mpfr_add_si(this->value, this->value, other, GMP_RNDD);
    this->validate();
    }

  /// Subtracts another number from this. 
  /**
   * This number precision is used.
   */
  void operator -= (const Number &other) {
    mpfr_sub(this->value, this->value, other.value, GMP_RNDD);
    this->validate();
    }

  /// Subtracts another number from this. 
  /**
   * This number precision is used.
   */
  void operator -= (const long &other) {
    mpfr_sub_si(this->value, this->value, other, GMP_RNDD);
    this->validate();
    }


  /// Subtracts another number from this.
  /**
   * This number precision is used.
   */
  Number &operator - (const Number &other) const {

    Number &number = *(new Number(*this));
    mpfr_sub(number.value, number.value, other.value, GMP_RNDD);

    number.validate();
    return number;
    }

  /// Returns a negative copy of number.
  /**
   * This number precision is used.
   */
  Number &operator - () const {

    Number &number = *(new Number(*this));
    mpfr_neg(number.value, number.value, GMP_RNDD);

    number.validate();
    return number;
    }

  /// Multiplies this number from another. 
  /**
   * This number precision is used.
   */
  void operator *= (const Number &other) {
    mpfr_mul(this->value, this->value, other.value, GMP_RNDD);
    this->validate();
    }

  /// Multiplies this number from signed integer. 
  /**
   * This number precision is used.
   */
  void operator *= (const long &other) {
    mpfr_mul_si(this->value, this->value, other, GMP_RNDD);
    this->validate();
    }

  /// Multiplies this number from another. 
  /**
   * This number precision is used.
   */
  Number &operator * (const Number &other) const {

    Number &number = *(new Number(*this));
    mpfr_mul(number.value, number.value, other.value, GMP_RNDD);

    number.validate();
    return number;
    }

  /// Divides this number from another. 
  /**
   * This number precision is used.
   */
  Number &operator / (const Number &other) const {

    Number &number = *(new Number(*this));
    mpfr_div(number.value, number.value, other.value, GMP_RNDD);

    number.validate();
    return number;
    }

  /// Divides this number from integer. 
  /**
   * This number precision is used.
   */
  Number &operator / (const long &other) const {

    Number &number = *(new Number(*this));
    mpfr_div_si(number.value, number.value, other, GMP_RNDD);

    number.validate();
    return number;
    }

  /// Raises this number by power of 2.
  void sqr() {
    mpfr_sqr(this->value, this->value, GMP_RNDD);
    this->validate();
    }

  /// Divides this number from another. 
  /**
   * This number precision is used.
   */
  void operator /= (const Number &other) {
    mpfr_div(this->value, this->value, other.value, GMP_RNDD);
    this->validate();
    }

  /// Divides this number from integer. 
  /**
   * This number precision is used.
   */
  void operator /= (const long &other) {
    mpfr_div_si(this->value, this->value, other, GMP_RNDD);
    this->validate();
    }

  /// Multiplies this by 2^{bits}.
  /**
   * This number precision is used.
   */
  void operator <<= (const long bits) {
    mpfr_mul_2si(this->value, this->value, bits, GMP_RNDD);
    this->validate();
    }
  
  /// Divides this by 2^{bits}.
  /**
   * This number precision is used.
   */
  void operator >>= (const long bits) {
    mpfr_div_2si(this->value, this->value, bits, GMP_RNDD);
    this->validate();
    }

  /// Compares this number with other.
  bool operator >= (const Number &other) const {
    return mpfr_cmp(this->value, other.value) >= 0;
    }
  
  /// Compares this number with other.
  bool operator >= (const double &other) const {
    return mpfr_cmp_d(this->value, other) >= 0;
    }
  
  /// Compares this number with other.
  bool operator <= (const Number &other) const {
    return mpfr_cmp(this->value, other.value) <= 0;
    }

  /// Compares this number with other.
  bool operator <= (const double &other) const {
    return mpfr_cmp_d(this->value, other) <= 0;
    }

  /// Compares this number absolute value with other number absolute value.
  /**
   * @returns positive if this number is bigger, zero if they are equal and
   * negative if this number is smaller.
   */
  int cmpAbs(const Number &other) const {
    return mpfr_cmpabs(this->value, other.value);
    }

  /// Checks if number is negative.
  /** 
   * @returns true if numer < 0
   */
  bool isNegative() const {
    return mpfr_sgn(this->value) < 0;
    }
  
  /// - -> +, + -> -
  void negative() {
    mpfr_neg(this->value, this->value, GMP_RNDD);
    }

  /// Floor.
  void floor() {
    mpfr_floor(this->value, this->value);
    this->validate();
    }

  };

#endif

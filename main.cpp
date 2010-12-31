#include <iostream>
#include <cassert>
#include <string>

#include "cpp/utils.h"
#include "cpp/number.h"
#include "cpp/number_pi.h"
#include "cpp/expression.h"
#include "cpp/expression_integer.h"
#include "cpp/expression_sum.h"
#include "cpp/expression_subtract.h"
#include "cpp/expression_negative.h"
#include "cpp/expression_multiplication.h"
#include "cpp/expression_division.h"
#include "cpp/expression_sin.h"
#include "cpp/expression_cos.h"
#include "cpp/expression_power.h"

using namespace std;

void test_number() {
  cout << "Testing class Number. ";
  //cout << endl;

  Number a = Number(1, 32);
  //cout << a.asString() << endl;
  assert(a.asString() == string("1,0000000000"));

  a += Number(2, 32);
  //cout << a.asString() << endl;
  assert(a.asString() == string("3,0000000000"));

  a += Number(-5, 32);
  //cout << a.asString() << endl;
  assert(a.asString() == string("-2,0000000000"));

  a += Number(2, 32);
  //cout << a.asString() << endl;
  assert(a.asString() == string("-0,00000000000"));

  a += Number(143, 32);
  //cout << a.asString() << endl;
  assert(a.asString() == string("143,00000000"));

  a -= Number(243, 32);
  //cout << a.asString() << endl;
  string b = a.asString();
  //cout << b.length() << endl;
  assert(a.asString() == string("-100,00000000"));

  a /= Number(20, 32);
  //cout << a.asString() << endl;
  assert(a.asString() == string("-5,0000000000"));

  a *= Number(-3, 32);
  //cout << a.asString() << endl;
  assert(a.asString() == string("15,000000000"));

  a -= Number(14, 32);
  a >>= 4;
  //cout << a.asString() << endl;
  assert(a.asString() == string("0,062500000000"));

  a <<= 4;
  //cout << a.asString() << endl;
  assert(a.asString() == string("1,0000000000"));

  a >>= 32;
  //cout << a.asString() << endl;
  assert(a.asString() == string("0,00000000023283064365"));

  a <<= 32;
  //cout << a.asString() << endl;
  assert(a.asString() == string("1,0000000000"));

  Number f = Number(1, dec_to_bin(10));
  f /= 3;
  //cout << "%Rf:     \"" << f.asFormatedString("%Rf") << '\"' << endl;
  assert(f.asFormatedString("%Rf") == string("0.333333"));
  //cout << "%*.Rf:   \"" << f.asFormatedString(10) << '\"' << endl;
  assert(f.asFormatedString(10) == string("0.333333333"));
  //cout << "%*.*Rf:  \"" << f.asFormatedString(
  //    "%*.*Rf", 12, 8) << '\"' << endl;
  assert(f.asFormatedString("%*.*Rf", 12, 8) == string("  0.33333333"));

  f *= 3;
  //cout << "%*.Rf:   \"" << f.asFormatedString(10) << '\"' << endl;
  assert(f.asFormatedString(10) == string("1.000000000"));

  cout << "Ok." << endl;
  }

void test_number_pi() {
  cout << "Testing class NumberPi. ";
  //cout << endl;

  Number pi4(getPi4(55));
  //cout << "\"" << pi4.asFormatedString(55) << '\"' << endl;
  assert(pi4.asFormatedString(55) == \
      string("0.785398163397448309615660845819875721049292349843776455"));

  Number pi(getPi(55));
  //cout << "\"" << pi.asFormatedString(55) << '\"' << endl;
  assert(pi.asFormatedString(55) == \
      string("3.14159265358979323846264338327950288419716939937510582"));

  cout << "Ok." << endl;
  }

void test_expression_integer() {
  cout << "Testing class ExpressionInteger. ";
  //cout << endl;

  ExpressionInteger a;
  //cout << a.asString(32) << endl;
  assert(a.asString(32) == string("0.0000000000000000000000000000000"));

  ExpressionInteger b(20);
  //cout << b.asString(32) << endl;
  assert(b.asString(32) == string("20.00000000000000000000000000000"));

  ExpressionInteger c(-20);
  //cout << c.asString(32) << endl;
  assert(c.asString(32) == string("-20.00000000000000000000000000000"));

  ExpressionInteger d(2);
  //cout << d.asString(32) << endl;
  assert(d.asString(32) == string("2.000000000000000000000000000000"));

  cout << "Ok." << endl;
  }

void test_expression_sum() {
  cout << "Testing class ExpressionSum. ";
  //cout << endl;

  ExpressionInteger a(20), b(30), d(-60);

  ExpressionSum c(a, b);
  //cout << c.asString(32) << endl;
  assert(c.asString(32) == string("50.00000000000000000000000000000"));

  ExpressionSum e(c, d);
  //cout << e.asString(32) << endl;
  assert(e.asString(32) == string("-10.00000000000000000000000000000"));

  cout << "Ok." << endl;
  }

void test_expression_subtract() {
  cout << "Testing class ExpressionSum. ";
  //cout << endl;

  ExpressionInteger a(20), b(30), d(-60);

  ExpressionSubtract c(a, b);
  //cout << c.asString(32) << endl;
  assert(c.asString(32) == string("-10.00000000000000000000000000000"));

  ExpressionSubtract e(c, d);
  //cout << e.asString(32) << endl;
  assert(e.asString(32) == string("50.00000000000000000000000000000"));

  cout << "Ok." << endl;
  }

void test_expression_negative() {
  cout << "Testing class ExpressionNegative. ";
  //cout << endl;

  ExpressionInteger a(20), b(-30);

  ExpressionNegative c(a);
  //cout << c.asString(32) << endl;
  assert(c.asString(32) == string("-20.00000000000000000000000000000"));

  ExpressionNegative d(b);
  //cout << d.asString(32) << endl;
  assert(d.asString(32) == string("30.00000000000000000000000000000"));

  cout << "Ok." << endl;
  }

void test_expression_multiplication() {
  cout << "Testing class ExpressionMultiplication. ";
  //cout << endl;

  ExpressionInteger a(2), b(3), d(-6);

  ExpressionMultiplication c(a, b);
  //cout << c.asString(32) << endl;
  assert(c.asString(32) == string("6.000000000000000000000000000000"));

  ExpressionMultiplication e(c, d);
  //cout << e.asString(32) << endl;
  assert(e.asString(32) == string("-36.00000000000000000000000000000"));

  cout << "Ok." << endl;
  }

void test_expression_division() {
  cout << "Testing class ExpressionDivision. ";
  //cout << endl;

  ExpressionInteger a(2), b(3), d(-6);

  ExpressionDivision c(a, b);
  //cout << c.asString(32) << endl;
  assert(c.asString(32) == string("0.6666666666666666666666666666667"));

  ExpressionDivision e(c, d);
  //cout << e.asString(32) << endl;
  assert(e.asString(32) == string("-0.1111111111111111111111111111111"));

  ExpressionMultiplication f(c, b);
  //cout << f.asString(32) << endl;
  assert(f.asString(32) == string("2.000000000000000000000000000000"));

  cout << "Ok." << endl;
  }

void test_expression_sin() {
  cout << "Testing class ExpressionSin. ";
  //cout << endl;

  ExpressionInteger a(1), b(-1), e(2000000);

  ExpressionSin c(a);
  //cout << c.asString(50) << endl;
  assert(c.asString(50) == \
      string("0.8414709848078965066525023216302989996225630607984"));

  ExpressionSin d(b);
  //cout << d.asString(50) << endl;
  assert(d.asString(50) == \
      string("-0.8414709848078965066525023216302989996225630607984"));

  ExpressionSin f(e);
  //cout << f.asString(50) << endl;
  assert(f.asString(50) == \
      string("-0.6557143155634700047626098527827476029967326202468"));
  //          -0.65571431556347000476260985278274760299673262024692362938
  // FIXME: Paskutinis skaitmuo nesutampa!

  cout << "Check." << endl;
  }

void test_expression_cos() {
  cout << "Testing class ExpressionCos. ";
  //cout << endl;

  ExpressionInteger a(1), b(-1), e(2000000);

  ExpressionCos c(a);
  //cout << c.asString(50) << endl;
  assert(c.asString(50) == \
      string("0.5403023058681397174009366074429766037323104206179"));

  ExpressionCos d(b);
  //cout << d.asString(50) << endl;
  assert(d.asString(50) == \
      string("0.5403023058681397174009366074429766037323104206179"));

  ExpressionCos f(e);
  //cout << f.asString(50) << endl;
  assert(f.asString(50) == \
      string("0.7550090968757463112230154096399955740150930942374"));
  //          0.75500909687574631122301540963999557401509309423726368324
  // FIXME: Paskutinis skaitmuo nesutampa!

  cout << "Check." << endl;
  }

/*
void test_expression_power() {
  cout << "Testing class ExpressionPower. ";
  //cout << endl;

  ExpressionInteger a(2), b(3);

  ExpressionPower c(a, b);
  //cout << c.asString(32, 10) << endl;
  assert(c.asString(32, 10) == string("8,0000000000"));

  ExpressionInteger d(1), e(2);
  ExpressionDivision f(d, e);
  //cout << f.asString(32, 10) << endl;
  ExpressionPower g(e, f);
  //cout << g.asString(32, 10) << endl;
  assert(g.asString(32, 10) == string("1,4139489340"));

  // FIXME: Should return only correct digits!

  cout << "Check." << endl;
  }

void test_polymorphism() {

  cout << "Testing class Expression polymorphism. ";
  //cout << endl;
  
  Expression 
    &a = *(new ExpressionInteger(20)),
    &b = *(new ExpressionInteger(30)),
    &d = *(new ExpressionInteger(-60)),
    &c = *(new ExpressionSum(a, b)),
    &e = *(new ExpressionSum(c, d)),
    &f = *(new ExpressionDivision(d, a)),
    &g = *(new ExpressionSin(d)),
    &h = *(new ExpressionPower(g, f));


  //cout << a.asString(32, 10) << endl;
  assert(a.asString(32, 10) == string("20,000000000"));

  //cout << b.asString(32, 10) << endl;
  assert(b.asString(32, 10) == string("30,000000000"));

  //cout << d.asString(32, 10) << endl;
  assert(d.asString(32, 10) == string("-60,000000000"));

  //cout << c.asString(32, 10) << endl;
  assert(c.asString(32, 10) == string("50,000000000"));

  //cout << e.asString(32, 10) << endl;
  assert(e.asString(32, 10) == string("-10,000000000"));

  //cout << f.asString(32, 10) << endl;
  assert(f.asString(32, 10) == string("-3,0000000000"));

  //cout << g.asString(32, 10) << endl;
  assert(g.asString(32, 10) == string("0,30481067311"));

  //cout << h.asString(32, 10) << endl;
  assert(h.asString(32, 10) == string("35,310956671"));

  cout << "Check." << endl;
  }
*/

int main() {

  test_number();
  test_number_pi();
  test_expression_integer();
  test_expression_sum();
  test_expression_subtract();
  test_expression_negative();
  test_expression_multiplication();
  test_expression_division();
  test_expression_sin();
  test_expression_cos();
//test_expression_power();
//test_polymorphism();

  return 0;
  }

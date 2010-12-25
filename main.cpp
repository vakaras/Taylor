#include <iostream>
#include <cassert>
#include <string>

#include "cpp/utils.h"
#include "cpp/number.h"
#include "cpp/expression.h"
#include "cpp/expression_integer.h"
#include "cpp/expression_sum.h"
#include "cpp/expression_subtract.h"
#include "cpp/expression_negative.h"

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
  assert(a.asString() == string("-100,00000000"));

  cout << "Ok." << endl;
  }

void test_expression_integer() {
  cout << "Testing class ExpressionInteger. ";
  //cout << endl;

  ExpressionInteger a;
  //cout << a.asString(32, 10) << endl;
  assert(a.asString(32, 10) == string("0,00000000000"));

  ExpressionInteger b(20);
  //cout << b.asString(32, 10) << endl;
  assert(b.asString(32, 10) == string("20,000000000"));

  ExpressionInteger c(-20);
  //cout << c.asString(32, 10) << endl;
  assert(c.asString(32, 10) == string("-20,000000000"));

  cout << "Ok." << endl;
  }

void test_expression_sum() {
  cout << "Testing class ExpressionSum. ";
  //cout << endl;

  ExpressionInteger a(20), b(30), d(-60);

  ExpressionSum c(a, b);
  //cout << c.asString(32, 10) << endl;
  assert(c.asString(32, 10) == string("50,000000000"));

  ExpressionSum e(c, d);
  //cout << e.asString(32, 10) << endl;
  assert(e.asString(32, 10) == string("-10,000000000"));

  cout << "Ok." << endl;
  }

void test_expression_subtract() {
  cout << "Testing class ExpressionSum. ";
  //cout << endl;

  ExpressionInteger a(20), b(30), d(-60);

  ExpressionSubtract c(a, b);
  //cout << c.asString(32, 10) << endl;
  assert(c.asString(32, 10) == string("-10,000000000"));

  ExpressionSubtract e(c, d);
  //cout << e.asString(32, 10) << endl;
  assert(e.asString(32, 10) == string("50,000000000"));

  cout << "Ok." << endl;
  }

void test_expression_negative() {
  cout << "Testing class ExpressionNegative. ";
  //cout << endl;

  ExpressionInteger a(20), b(-30);

  ExpressionNegative c(a);
  //cout << c.asString(32, 10) << endl;
  assert(c.asString(32, 10) == string("-20,000000000"));

  ExpressionNegative d(b);
  //cout << d.asString(32, 10) << endl;
  assert(d.asString(32, 10) == string("30,000000000"));

  cout << "Ok." << endl;
  }

void test_polymorphism() {

  cout << "Testing class Expression polymorphism. ";
  //cout << endl;
  
  Expression 
    &a = *(new ExpressionInteger(20)),
    &b = *(new ExpressionInteger(30)),
    &d = *(new ExpressionInteger(-60)),
    &c = *(new ExpressionSum(a, b)),
    &e = *(new ExpressionSum(c, d));

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

  cout << "Ok." << endl;
  }

int main() {

  test_number();
  test_expression_integer();
  test_expression_sum();
  test_expression_subtract();
  test_expression_negative();
  test_polymorphism();

  return 0;
  }

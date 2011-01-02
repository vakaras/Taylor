#include <string>
//#include <iostream>

#include "cpp/utils.h"
#include "cpp/expression.h"
#include "cpp/expression_integer.h"
#include "cpp/expression_pi.h"
#include "cpp/expression_e.h"
#include "cpp/expression_sum.h"
#include "cpp/expression_subtract.h"
#include "cpp/expression_negative.h"
#include "cpp/expression_multiplication.h"
#include "cpp/expression_division.h"
#include "cpp/expression_sin.h"
#include "cpp/expression_cos.h"
#include "cpp/expression_exp.h"
#include "cpp/expression_ln.h"
#include "cpp/expression_power.h"

class PythonExpression {

// Attributes.

private:

  Expression *expression;

// Methods.

public:

  PythonExpression() {
    expression = new ExpressionInteger(0);
    }

  PythonExpression(long _value) {
    expression = new ExpressionInteger(_value);
    }

  PythonExpression(Expression *_expression) {
    expression = _expression;
    }

  PythonExpression(const PythonExpression &original) {
    this->expression = &original.expression->clone();
    }

  ~PythonExpression() {
    delete expression;                  // FIXME: Expressions have to be
                                        // deleted recursively.
    }

  std::string asString(long digits) {
    return this->expression->asString(digits);
    }

  PythonExpression &operator + (const PythonExpression &other) const {

    Expression *expr = new ExpressionSum(
        expression->clone(), other.expression->clone());

    return *(new PythonExpression(expr));
    }

  PythonExpression &operator + (const long &other) const {

    Expression *expr = new ExpressionSum(
        expression->clone(), *(new ExpressionInteger(other)));

    return *(new PythonExpression(expr));
    }

  PythonExpression &operator - (const PythonExpression &other) const {

    Expression *expr = new ExpressionSubtract(
        expression->clone(), other.expression->clone());

    return *(new PythonExpression(expr));
    }

  PythonExpression &operator - (const long &other) const {

    Expression *expr = new ExpressionSubtract(
        expression->clone(), *(new ExpressionInteger(other)));

    return *(new PythonExpression(expr));
    }

  PythonExpression &operator - () const {

    Expression *expr = new ExpressionNegative(
        expression->clone());

    return *(new PythonExpression(expr));
    }
  
  PythonExpression &operator * (const PythonExpression &other) const {

    Expression *expr = new ExpressionMultiplication(
        expression->clone(), other.expression->clone());

    return *(new PythonExpression(expr));
    }

  PythonExpression &operator * (const long &other) const {

    Expression *expr = new ExpressionMultiplication(
        expression->clone(), *(new ExpressionInteger(other)));

    return *(new PythonExpression(expr));
    }

  PythonExpression &operator / (const PythonExpression &other) const {

    Expression *expr = new ExpressionDivision(
        expression->clone(), other.expression->clone());

    return *(new PythonExpression(expr));
    }

  PythonExpression &operator / (const long &other) const {

    Expression *expr = new ExpressionDivision(
        expression->clone(), *(new ExpressionInteger(other)));

    return *(new PythonExpression(expr));
    }

  PythonExpression &sin() const {
    Expression *expr = new ExpressionSin(expression->clone());
    return *(new PythonExpression(expr));
    }

  PythonExpression &cos() const {
    Expression *expr = new ExpressionCos(expression->clone());
    return *(new PythonExpression(expr));
    }

  PythonExpression &exp() const {
    Expression *expr = new ExpressionExp(expression->clone());
    return *(new PythonExpression(expr));
    }
  
  PythonExpression &ln() const {
    Expression *expr = new ExpressionLn(expression->clone());
    return *(new PythonExpression(expr));
    }

  PythonExpression &operator ^ (const PythonExpression &other) const {

    Expression *expr = new ExpressionPower(
        expression->clone(), other.expression->clone());

    return *(new PythonExpression(expr));
    }

  };

PythonExpression get_pi() {
  return PythonExpression(new ExpressionPi());
  }

PythonExpression get_e() {
  return PythonExpression(new ExpressionE());
  }

PythonExpression get_sin(const PythonExpression &expression) {
  return PythonExpression(expression.sin());
  }

PythonExpression get_cos(const PythonExpression &expression) {
  return PythonExpression(expression.cos());
  }

PythonExpression get_exp(const PythonExpression &expression) {
  return PythonExpression(expression.exp());
  }

PythonExpression get_ln(const PythonExpression &expression) {
  return PythonExpression(expression.ln());
  }

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(lmathcpp)
{
  class_<PythonExpression>("Expression", init<>())
    .def(init<int>())
    .def("asString", &PythonExpression::asString)
    .def(self + self)
    .def(self + long())
    .def(self - self)
    .def(self - long())
    .def(-self)
    .def(self * self)
    .def(self * long())
    .def(self / self)
    .def(self / long())
    .def(self ^ self)
    .def(self ^ long())
    ;
  def("get_pi", get_pi, "Returns expression pi.");
  def("get_e",  get_e,  "Returns expression e.");
  def("sin", get_sin, "Returns expression of sin.");
  def("cos", get_cos, "Returns expression of cos.");
  def("exp", get_exp, "Returns expression of exp.");
  def("ln",  get_ln,  "Returns expression of ln.");
}

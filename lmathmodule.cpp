#include <string>

#include "cpp/utils.h"
#include "cpp/expression.h"
#include "cpp/expression_integer.h"
#include "cpp/expression_sum.h"

class PythonExpression {

// Attributes.

private:

  Expression *expression;

// Methods.

public:

  PythonExpression() {
    expression = new ExpressionInteger(0);
    }

  PythonExpression(int _value) {
    expression = new ExpressionInteger(_value);
    }

  PythonExpression(Expression *_expression) {
    expression = _expression;
    }

  std::string asString(int precision, int base=10) {
    return this->expression->asString(precision, base);
    }

  PythonExpression &operator + (const PythonExpression &other) const {

    Expression *sum = new ExpressionSum(
        expression->clone(), other.expression->clone());

    return *(new PythonExpression(sum));
    }
  
  };

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>
using namespace boost::python;
 
BOOST_PYTHON_MODULE(lmath)
{
  class_<PythonExpression>("Expression", init<>())
    .def(init<int>())
    .def("asString", &PythonExpression::asString)
    .def(self + self)
    ;
}

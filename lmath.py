from lmathcpp import Expression
from lmathcpp import get_e as _get_e
from lmathcpp import get_pi as _get_pi
from lmathcpp import sin as _sin
from lmathcpp import cos as _cos
from lmathcpp import exp as _exp
from lmathcpp import ln as _ln

e = _get_e()
pi = _get_pi()

def sin(x):
    """ Creates sin expression.

    If int is passed, then it is wraped into Expression.
    """
    if isinstance(x, int):
        x = Expression(x)
    return _sin(x)

def cos(x):
    """ Creates cos expression.

    If int is passed, then it is wraped into Expression.
    """
    if isinstance(x, int):
        x = Expression(x)
    return _cos(x)

def exp(x):
    """ Creates e^{x} expression.

    If int is passed, then it is wraped into Expression.
    """
    if isinstance(x, int):
        x = Expression(x)
    return _exp(x)

def ln(x):
    """ Creates ln (natural logarithm) expression.

    If int is passed, then it is wraped into Expression.
    """
    if isinstance(x, int):
        x = Expression(x)
    return _ln(x)

import lmath

#   from lmath import Number

#   a = Number(2, 32)

#   print a.asString(10)

from lmath import Expression
from lmath import get_e, get_pi
from lmath import sin, cos, exp, ln

a = Expression(5)
b = Expression(3)

e = get_e()
pi = get_pi()

print u'Veiksmai su'
print u' a = ', a.asString(32)
print u' b = ', b.asString(32)
print u' e  = ', e.asString(32)
print u' pi = ', pi.asString(32)
print u'a + b = ', (a + b).asString(32)
print u'a - b = ', (a - b).asString(32)
print u' - a  = ', (-a).asString(32)
print u'a * b = ', (a * b).asString(32)
print u'a / b = ', (a / b).asString(32)
print u'(a / b) * b = ', ((a / b) * b).asString(32)
print u'a + 1 = ', (a + 1).asString(32)
print u'a - 1 = ', (a - 1).asString(32)
print u'a * 1 = ', (a * 1).asString(32)
print u'a / 1 = ', (a / 1).asString(32)
print u'sin(pi) = ', sin(pi).asString(32)
print u'cos(pi) = ', cos(pi).asString(32)
print u'exp(b)  = ', exp(b).asString(32)
print u'ln(e)   = ', ln(e).asString(32)
#TODO: print u'exp(1) = ', exp(1).asString(32)
print u' a ^ b = ', (a^b).asString(32)
print u' a ^ 2 = ', (a^b).asString(32)

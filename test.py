# -*- encoding: utf-8 -*-
import lmath

from lmath import Expression
from lmath import e, pi
from lmath import sin, cos, exp, ln

a = Expression(5)
b = Expression(3)

print u'Veiksmai su'
print u' a          = ', a.asString(32)
print u' b          = ', b.asString(32)
print u' e          = ', e.asString(32)
print u' pi         = ', pi.asString(32)
print u'a + b       = ', (a + b).asString(32)
print u'a - b       = ', (a - b).asString(32)
print u' - a        = ', (-a).asString(32)
print u'a * b       = ', (a * b).asString(32)
print u'a / b       = ', (a / b).asString(32)
print u'(a / b) * b = ', ((a / b) * b).asString(32)
print u'a + 1       = ', (a + 1).asString(32)
print u'a - 1       = ', (a - 1).asString(32)
print u'a * 1       = ', (a * 1).asString(32)
print u'a / 1       = ', (a / 1).asString(32)
print u'sin(pi)     = ', sin(pi).asString(32)
print u'cos(pi)     = ', cos(pi).asString(32)
print u'exp(b)      = ', exp(b).asString(32)
print u'ln(e)       = ', ln(e).asString(32)
print u'sin(1)      = ', sin(1).asString(32)
print u'cos(1)      = ', cos(1).asString(32)
print u'exp(1)      = ', exp(1).asString(32)
print u'ln(1)       = ', ln(1).asString(32)
print u' a ^ b      = ', (a ^ b).asString(32)
print u' a ^ 2      = ', (a ^ b).asString(32)

print (pi/2).latex()

a = (a + 1)/10
print a.asString(32)
print (a^20).asString(32)
print (a^20).asString(5)

from lmath import latex_show_as_aligned
print latex_show_as_aligned([['1', '=', '1']])

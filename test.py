import lmath

#   from lmath import Number

#   a = Number(2, 32)

#   print a.asString(10)

from lmath import Expression

e = Expression(5)

print e.asString(64, 10)

op1 = Expression(1)
op2 = Expression(2)

op3 = op1+op2

print op3.asString(64, 10)

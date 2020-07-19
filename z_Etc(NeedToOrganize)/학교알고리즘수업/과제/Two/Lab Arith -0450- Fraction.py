#-*- coding: cp949 -*-
#-------------------------------------------------------------------------------
# Purpose:     2018 Power Python
# Author:      Cho
#-------------------------------------------------------------------------------

import  fractions
la= [  fractions.Fraction(451,893),  fractions.Fraction(123,839),  fractions.Fraction(7111,17111), \
 fractions.Fraction(4865, 8291),  fractions.Fraction(10, 20),  fractions.Fraction(300,600), \
 fractions.Fraction(325, 547),  fractions.Fraction(4517,  8937),  fractions.Fraction(4511, 7621), \
fractions.Fraction(101, 235) ]


print la
la.sort()
for i, x in enumerate(la) :
    print i+1, "= ", x
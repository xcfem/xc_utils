# -*- coding: utf-8 -*-
'''
   Comprobación de la función ka_coulomb, a partir de la tabla 6.4 del libro
   "Principios de ingeniería de cimentaciones." Braja M. Das, página 353 y
   de la tabla 10.3 de Geotécnia y Cimientos II. Jiménez Salas, página 683
'''
from geotecnia import empujeCoulomb
import math

ka1= empujeCoulomb.ka_coulomb(math.radians(0),math.radians(0),math.radians(28),math.radians(0))
ka2= empujeCoulomb.ka_coulomb(math.radians(0),math.radians(0),math.radians(30),math.radians(5))
ka3= empujeCoulomb.ka_coulomb(math.radians(0),math.radians(0),math.radians(32),math.radians(10))
ka4= empujeCoulomb.ka_coulomb(math.radians(-20),math.radians(-20),math.radians(40),math.radians(10))

ratio1= abs(ka1-0.3610)/0.3610
ratio2= abs(ka2-0.3189)/0.3189
ratio3= abs(ka3-0.2853)/0.2853
ratio4= abs(ka4-0.085)/0.085

'''
print "ka1= ",ka1
print "ka2= ",ka2
print "ka3= ",ka3
print "ka4= ",ka4
print "ratio1= ",ratio1
print "ratio2= ",ratio2
print "ratio3= ",ratio3
print "ratio4= ",ratio4
'''

import os
fname= os.path.basename(__file__)
if (ratio1<1e-3) & (ratio2<1e-3) & (ratio3<1e-3) & (ratio4<3e-2):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."

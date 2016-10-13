# -*- coding: utf-8 -*-

from geotecnia import earthPressureRankine
import math

Kp= earthPressureRankine.RankineSoil(math.pi/6.0).Kp()

#print 'Kp= ', Kp

ratio1= abs(Kp-3)/3.0

import os
fname= os.path.basename(__file__)
if (ratio1<1e-12):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."

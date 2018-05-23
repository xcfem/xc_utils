# -*- coding: utf-8 -*-

import xc_base
import geom
import math

ptoOrigen=geom.Pos2d(0,0)
ptoDestino=geom.Pos2d(10,0)
s1=geom.Segmento2d(ptoOrigen,ptoDestino)
s2=s1.offsetDouble(2)
s3=s1.offsetDouble(-2)

p1=s2.getCenterOfMass()
p2=s3.getCenterOfMass()

ratio1=math.fabs(p1.distPos2d(p2)-4)

import os
fname= os.path.basename(__file__)
if ratio1<1e-15:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."



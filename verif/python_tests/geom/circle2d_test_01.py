# -*- coding: utf-8 -*-

import xc_base
import geom
import math

circ1=geom.Circle2d(geom.Pos2d(0.0,0.0),1.0)

areaCirc=circ1.getArea()
perimetroCirc= circ1.getPerimetro()
circleCenterOfMassX= circ1.getCenterOfMass().x
circleCenterOfMassY= circ1.getCenterOfMass().y
IxCirc=circ1.getIx()
IyCirc=circ1.getIy()
PxyCirc=circ1.getPxy()

ratio1=areaCirc-math.pi
ratio2=(perimetroCirc-2*math.pi)/2*math.pi
ratio3=circleCenterOfMassX
ratio4=circleCenterOfMassY
ratio5=(IxCirc-(math.pi/4.))/(math.pi/4.)
ratio6=(IyCirc-(math.pi/4.))/(math.pi/4.)
ratio7=PxyCirc

import os
fname= os.path.basename(__file__)
if math.fabs(ratio1)<1e-10 and math.fabs(ratio2)<1e-10 and math.fabs(ratio3)<1e-10 and math.fabs(ratio4)<1e-10  and math.fabs(ratio5)<1e-10 and math.fabs(ratio6)<1e-10 and math.fabs(ratio7)<1e-10:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."












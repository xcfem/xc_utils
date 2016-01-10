# -*- coding: utf-8 -*-

import xc_base
import geom
import math

circ1=geom.Circulo2d(geom.Pos2d(0.0,0.0),1.0)

areaCirc=circ1.getArea()
perimetroCirc=circ1.getPerimetro()
xCdgCirc=circ1.getCdg().x
yCdgCirc=circ1.getCdg().y
IxCirc=circ1.getIx()
IyCirc=circ1.getIy()
PxyCirc=circ1.getPxy()

ratio1=areaCirc-math.pi
ratio2=(perimetroCirc-2*math.pi)/2*math.pi
ratio3=xCdgCirc
ratio4=yCdgCirc
ratio5=(IxCirc-(math.pi/4.))/(math.pi/4.)
ratio6=(IyCirc-(math.pi/4.))/(math.pi/4.)
ratio7=PxyCirc

if math.fabs(ratio1)<1e-10 and math.fabs(ratio2)<1e-10 and math.fabs(ratio3)<1e-10 and math.fabs(ratio4)<1e-10  and math.fabs(ratio5)<1e-10 and math.fabs(ratio6)<1e-10 and math.fabs(ratio7)<1e-10:
  print "test circulo 01: ok."
else:
  print "test circulo 01: ERROR."












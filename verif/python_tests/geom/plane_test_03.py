# -*- coding: utf-8 -*-

#Intersección de recta y plano.
#Ejemplo 1.2 de la tesis «La teoría de bloque aplicada a la dinámica
#de rocas» de Juan Carlos Ayes Zamudio

import xc_base
import geom
import math

A=2.
B=3.
C=1.
D=4.

ITeor=geom.Pos3d(3,-1,1)
P=geom.Plane3d(geom.GeneralEquationOfPlane(2,3,1,-4))
pto=geom.Pos3d(1,1,-2)
vDir=geom.Dir3d(2,-2,3)

r=geom.Recta3d(pto,vDir)
dr=ITeor.distRecta3d(r)
I=P.getIntersRecta3d(r)
d=I.distPlano3d(P)

ratio1=ITeor.distPos3d(I)
ratio2=math.fabs(dr)
ratio3=math.fabs(d)

import os
fname= os.path.basename(__file__)
if math.fabs(ratio1)<1e-4 and math.fabs(ratio2)<1e-4 and math.fabs(ratio3)<1e-4:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


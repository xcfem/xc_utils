# -*- coding: utf-8 -*-

import xc_base
import geom
import math

def getAbs(vt1):
  return vt1.getModulo()

def getAngulo(vt1,vt2):
  return vt1.angulo(vt2)


u=geom.Vector2d(1,0)
v=geom.Vector2d(1,1)
modulo=getAbs(u)
alpha=getAngulo(v,u)

ratio1= modulo-1
ratio2=math.degrees(alpha)-45



if math.fabs(ratio1)<1e-10 and math.fabs(ratio2)<1e-10:
  print "test vector 2d 02: pasa."
else:
  print "test vector 2d 02: falla."












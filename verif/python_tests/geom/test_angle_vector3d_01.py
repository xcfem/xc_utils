# -*- coding: utf-8 -*-

# Angle between two vectors.

import xc_base
import geom
import math

vec1=geom.Vector3d(1,7.19412e-10,-2.08017e-05)
vec2=geom.Vector3d(1,0,-2.08017e-05)
angle=vec1.angulo(vec2)
angleTeor=0.0
ratio1=math.fabs(angleTeor-angle)#/angleTeor

print "angle= ", math.degrees(angle)

if math.fabs(ratio1)<1e-4:
  print "test vector3d 02: pasa."
else:
  print "test vector3d 02: falla."












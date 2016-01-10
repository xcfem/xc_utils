# -*- coding: utf-8 -*-

# Ángulo entre dos vectores. Ejemplo 1.6 de la tesis «La teoría de bloque aplicada a la dinámica de rocas» de Juan Carlos Ayes Zamudio

import xc_base
import geom
import math

vec1=geom.Vector3d(9,8,7)
vec2=geom.Vector3d(1,2,1)
delta=vec1.angulo(vec2)
deltaTeor=math.acos(32/2.4495/13.9284)
ratio1=math.fabs(deltaTeor-delta)/deltaTeor

if math.fabs(ratio1)<1e-4:
  print "test vector3d 02: ok."
else:
  print "test vector3d 02: ERROR."












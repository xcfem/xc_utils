# -*- coding: utf-8 -*-

#Ángulo entre dos planos.
#Ejemplo 1.7 de la tesis «La teoría de bloque aplicada a la dinámica
#de rocas» de Juan Carlos Ayes Zamudio

import xc_base
import geom
import math
import teoria_bloques

alpha1=math.radians(30)
beta1=math.radians(320)
p=geom.Pos3d(0,0,0)

plBuz1=teoria_bloques.calcPlanoBuzamiento(alpha1,beta1,p)
P1=geom.SemiEspacio3d(plBuz1)
v=geom.Vector3d(1,2,1)

delta=P1.anguloConVector3d(v)
deltaTeor=math.radians(32.349)

ratio1=math.fabs(deltaTeor-delta)/deltaTeor

if math.fabs(ratio1)<1e-4:
    print "test SemiEspacio3d 02: ok."
else:
    print "test SemiEspacio3d 02: ERROR."


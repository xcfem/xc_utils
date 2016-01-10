# -*- coding: utf-8 -*-

#Proyección de un vector sobre un plano.
#Ejemplo 1.13 de la tesis «La teoría de bloque aplicada a la dinámica
#de rocas» de Juan Carlos Ayes Zamudio

import xc_base
import geom
import math
import teoria_bloques

alpha=math.radians(50)
beta=math.radians(290)
p=geom.Pos3d(0,0,0)

r=geom.Vector3d(1,2,1)

plBuz=teoria_bloques.calcPlanoBuzamiento(alpha,beta,p)
P=geom.SemiEspacio3d(plBuz)
plLim=P.getPlanoLimite()
s=plLim.getProyeccionVector3d(r)
s=s.normalizado()

sTeor=geom.Vector3d(0.5488,0.7818,0.2959)
ratio1= (sTeor-s)
ratio1=ratio1.getModulo()

if abs(ratio1)<1e-4:
    print "test SemiEspacio3d 03: ok."
else:
    print "test SemiEspacio3d 01: ERROR."


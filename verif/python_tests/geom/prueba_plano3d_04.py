# -*- coding: utf-8 -*-


#Vector dirección de la intersección de dos planos.
#Ejemplo 1.3 de la tesis «La teoría de bloque aplicada a la dinámica
#de rocas» de Juan Carlos Ayes Zamudio

import xc_base
import geom
import math
import teoria_bloques

alpha1=math.radians(20)
beta1=math.radians(280)
alpha2=math.radians(60)
beta2=math.radians(150)

O=geom.Pos3d(0,0,0)

P1=teoria_bloques.calcPlanoBuzamiento(alpha1,beta1,O)
P2=teoria_bloques.calcPlanoBuzamiento(alpha2,beta2,O)

n1=P1.getNormal()
n2=P2.getNormal()

I12=n1.cross(n2)

I12Teor=geom.Vector3d(0.7345,0.5753,0.2269)

ratio1=(I12-I12Teor).getModulo()

if math.fabs(ratio1)<1e-4:
    print "test plano3d 04: ok."
else:
    print "test plano3d 04: ERROR."
#Terminar!!!

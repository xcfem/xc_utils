# -*- coding: utf-8 -*-

import xc_base
import geom
import math

u=geom.Vector2d(1,0)
ptoOrigen=geom.Pos2d(0,0)
ptoDestino=geom.Pos2d(1,1)
s=geom.Segmento2d(ptoOrigen,ptoDestino)
alpha=s.anguloVector(u)
ratio1= math.degrees(alpha)-45

ptoDestino=geom.Pos2d(0,1)
s=geom.Segmento2d(ptoOrigen,ptoDestino)
alpha=s.anguloVector(u)
ratio2= math.degrees(alpha)-90

ptoDestino=geom.Pos2d(-1,1)
s=geom.Segmento2d(ptoOrigen,ptoDestino)
alpha=s.anguloVector(u)
ratio3= math.degrees(alpha)-135

ptoDestino=geom.Pos2d(-1,0)
s=geom.Segmento2d(ptoOrigen,ptoDestino)
alpha=s.anguloVector(u)
ratio4= math.degrees(alpha)-180

ptoDestino=geom.Pos2d(-1,-1)
s=geom.Segmento2d(ptoOrigen,ptoDestino)
alpha=s.anguloVector(u)
ratio5= math.degrees(alpha)-225

ptoDestino=geom.Pos2d(0,-1)
s=geom.Segmento2d(ptoOrigen,ptoDestino)
alpha=s.anguloVector(u)
ratio6= math.degrees(alpha)-270

ptoDestino=geom.Pos2d(1,-1)
s=geom.Segmento2d(ptoOrigen,ptoDestino)
alpha=s.anguloVector(u)
ratio7= math.degrees(alpha)-315

ptoDestino=geom.Pos2d(1,0)
s=geom.Segmento2d(ptoOrigen,ptoDestino)
alpha=s.anguloVector(u)
ratio8= math.degrees(alpha)

if math.fabs(ratio1)<1e-10 and math.fabs(ratio2)<1e-10 and math.fabs(ratio3)<1e-10 and math.fabs(ratio4)<1e-10 and math.fabs(ratio5)<1e-10 and math.fabs(ratio6)<1e-10 and math.fabs(ratio7)<1e-10 and math.fabs(ratio8)<1e-10:
    print "test segmento 2d 01: ok."
else:
    print "test segmento 2d 01: ERROR."

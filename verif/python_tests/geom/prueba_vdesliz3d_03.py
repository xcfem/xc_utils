# -*- coding: utf-8 -*-

import xc_base
import geom
import math

ptoOrigen=geom.Pos3d(0.5,0,0)
ptoDest=geom.Pos3d(0.5,0,100)
r1=geom.Recta3d(ptoOrigen,ptoDest)
vdir=r1.getVDir()
tp=r1.tipo()

pto_aplic=geom.Pos3d(5,0,0)
vectorDir=geom.Vector3d(0,2,0)
vec1=geom.VDesliz3d(pto_aplic,vectorDir)
pto=vec1.getOrg()
brazo=pto.distRecta3d(r1)
fuerza=vec1.y
m=vec1.getMomentoRecta3d(r1)

mTeor=fuerza*brazo
ratio1=(m-mTeor)/mTeor

if m==mTeor:
    print "test vdesliz3d 03: pasa."
else:
    print "test vdesliz3d 03: falla."


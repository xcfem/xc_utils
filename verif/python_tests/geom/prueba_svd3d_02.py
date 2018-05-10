# -*- coding: utf-8 -*-
import xc_base
import geom
pto=geom.Pos3d(-1.,1.,0.)

ptoOrigen=geom.Pos3d(-1.,1.,0.)
ptoDest=geom.Pos3d(1.,1.,0.)
r1=geom.Recta3d(ptoOrigen,ptoDest)

svd1=geom.SVD3d()
ptoAplic=geom.Pos3d(1,1,0)
vectorDir=geom.Vector3d(0,0,1)
vec=geom.VDesliz3d(ptoAplic,vectorDir)
svd1+=vec
ptoAplic=geom.Pos3d(-1,1,0)
vec=geom.VDesliz3d(ptoAplic,vectorDir)
svd1+=vec
ptoAplic=geom.Pos3d(-1,-1,0)
vec=geom.VDesliz3d(ptoAplic,vectorDir)
svd1+=vec
ptoAplic=geom.Pos3d(1,-1,0)
vec=geom.VDesliz3d(ptoAplic,vectorDir)
svd1+=vec

Res=svd1.getResultant()
Mom=svd1.getMoment()
MomP=svd1.getMomentPos3d(pto)
MomR=svd1.getMomentRecta3d(r1) #devuelve el valor con signo (en función del sentido de la recta), probablemente sea mejor ignorar el signo

##print "Res.x =", Res.x
##print "Res.y =", Res.y
##print "Res.z =", Res.z
##print "Mom.x =", Mom.x
##print "Mom.y =", Mom.y
##print "Mom.z =", Mom.z
##print "MomR =", MomR
##print "MomP.x =", MomP.x
##print "MomP.y =", MomP.y

import os
fname= os.path.basename(__file__)
if Res.x == 0 and Res.y == 0 and Res.z == 4 and Mom.x == 0 and Mom.y == 0 and Mom.z == 0 and MomR == -4 and MomP.x == -4 and MomP.y == -4:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."



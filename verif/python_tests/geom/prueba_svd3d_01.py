# -*- coding: utf-8 -*-
import xc_base
import geom
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

Res=svd1.getResultante()
Mom=svd1.getMomento()

if Res.x == 0 and Res.y == 0 and Res.z == 4 and Mom.x == 0 and Mom.y == 0 and Mom.z == 0: 
    print "test svd3d 01: pasa."
else:
    print "test svd3d 01: falla."

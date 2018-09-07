# -*- coding: utf-8 -*-
import xc_base
import geom
svd1=geom.SlidingVectorsSystem3d()
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

#It seems there is a bug in svd.getResultant() it returns a SlidingVectorsSystem3d instead of a Vector3d.
#print 'type<Res>= ', type(Res)
#print 'Res= ', Res

import os
fname= os.path.basename(__file__)
if Res.x == 0 and Res.y == 0 and Res.z == 4 and Mom.x == 0 and Mom.y == 0 and Mom.z == 0: 
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


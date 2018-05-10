# -*- coding: utf-8 -*-
import xc_base
import geom
import math

svd1=geom.SVD2d()
ptoAplic=geom.Pos2d(1,1)
vectorDir=geom.Vector2d(1,0)
vec=geom.VDesliz2d(ptoAplic,vectorDir)
svd1+=vec

svd2=geom.SVD2d()
ptoAplic=geom.Pos2d(1,1)
vectorDir=geom.Vector2d(0.5,0)
vec=geom.VDesliz2d(ptoAplic,vectorDir)
svd2+=vec

R= 5.0*svd1-10.0*svd2
result= R.getResultant()
mom= R.getMoment()
ratio= result.getModulo()+ math.sqrt(mom**2)

# print 'R= ', R
# print 'result= ', result
# print 'mom= ', mom
# print 'ratio= ', ratio

import os
fname= os.path.basename(__file__)
if(ratio<1e-13):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


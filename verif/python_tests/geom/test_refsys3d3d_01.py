# -*- coding: utf-8 -*-
import math
import xc_base
import geom
p1=geom.Pos3d(1,1,1)
p2=geom.Pos3d(2,2,2)
ref= geom.Ref3d3d(p1,p2)


v= geom.Vector3d(1,1,1)
vTrf= ref.getCooLocales(v)
vTrfTeor= geom.Vector3d(math.sqrt(3.0),0,0)
ratio= (vTrf-vTrfTeor).getModulo()
p0= ref.getPosGlobal(geom.Pos3d(0.0,0.0,0.0))
ratio2= (p1-p0).getModulo()

# print "vTrf= ", vTrf
# print "ratio= ", ratio
# print "p0= ", p0
# print "ratio2= ", ratio2

import os
fname= os.path.basename(__file__)
if (abs(ratio)<1e-12 and abs(ratio2)<1e-12):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."











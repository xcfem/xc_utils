# -*- coding: utf-8 -*-

import xc_base
import geom
vec1=geom.Vector3d(1,2,3)
xV=vec1.x
yV=vec1.y
zV=vec1.z

tp=vec1.tipo()

if xV==1 and yV==2 and zV==3:
  print "test vector3d 01: ok."
else:
  print "test vector3d 01: ERROR."












# -*- coding: utf-8 -*-

import xc_base
import geom
import math

pto=geom.Pos3d(0,0,0)
vectorDir=geom.Vector3d(1,2,3)
vec1=geom.VDesliz3d(pto,vectorDir)

if vec1.x==1 and vec1.y==2 and vec1.z==3:
    print "test vdesliz3d 01: ok."
else:
    print "test vdesliz3d 01: ERROR."


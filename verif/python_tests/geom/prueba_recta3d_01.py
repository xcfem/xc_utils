# -*- coding: utf-8 -*-

import xc_base
import geom
import math

r1=geom.Recta3d(geom.Pos3d(0.,0.,0.),geom.Pos3d(10.,10.,10.))

vdir= r1.getVDir()
tp=r1.tipo()

if vdir.x==10. and vdir.y==10. and vdir.z==10.:
    print "test recta3d 01: ok."
else:
    print "test recta3d 01: ERROR."















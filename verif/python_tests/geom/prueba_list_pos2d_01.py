# -*- coding: utf-8 -*-

import xc_base
import geom
import math

ptsPrb=geom.ListPos2d()
ptsPrb.appendPoint(geom.Pos2d(0,0))
ptsPrb.appendPoint(geom.Pos2d(2,0))
ptsPrb.appendPoint(geom.Pos2d(2,2))
ptsPrb.appendPoint(geom.Pos2d(0,2))
xCdg=ptsPrb.getCdg().x
yCdg=ptsPrb.getCdg().y
area=ptsPrb.getArea()

import os
fname= os.path.basename(__file__)
if math.fabs(xCdg-1.0)<1e-15 and math.fabs(yCdg-1.0)<1e-15 and math.fabs(area)<1e-15:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


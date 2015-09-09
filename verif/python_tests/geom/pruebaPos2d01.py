# -*- coding: utf-8 -*-

import xc_base
import geom
pos1= geom.Pos2d(1,2);

xPt= pos1.x
yPt= pos1.y

#print("pos1.x= ",pos1.x," pos1.y= ",pos1.y)

if(xPt==1. and yPt==2.):
  print("test pos2d 01: pasa")
else:
  print("test pos2d 01: falla")

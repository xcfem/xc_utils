# -*- coding: utf-8 -*-
import xc_base
import geom
pol1=geom.Poligono2d()
pol1.agregaVertice(geom.Pos2d(0,0))
pol1.agregaVertice(geom.Pos2d(1,0))
pol1.agregaVertice(geom.Pos2d(1,1))
pol1.agregaVertice(geom.Pos2d(0,1))

perimPol1=pol1.getPerimetro()

pol2=pol1.offset(-0.25)
perimPol2=pol2.getPerimetro()

ratio1= (perimPol1-4)/4.
ratio2= (perimPol2-2)/2.

import os
fname= os.path.basename(__file__)
if abs(ratio1)<1e-10 and abs(ratio2)<1e-10:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


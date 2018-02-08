# -*- coding: utf-8 -*-
import xc_base
import geom
pol1=geom.Poligono2d()
pol1.agregaVertice(geom.Pos2d(0,0))
pol1.agregaVertice(geom.Pos2d(1,0))
pol1.agregaVertice(geom.Pos2d(1,1))
pol1.agregaVertice(geom.Pos2d(0,1))
areaPol=pol1.getArea()
perimetroPol=pol1.getPerimetro()
CdgPol=pol1.getCdg()
xCdgPol=CdgPol.x
yCdgPol=CdgPol.y
IxPol=pol1.getIx()
IyPol=pol1.getIy()
PxyPol=pol1.getPxy()

ratio1= (areaPol-1)
ratio2= (perimetroPol-4)/4.
ratio3= (xCdgPol-0.5)/0.5
ratio4= (yCdgPol-0.5)/0.5
ratio5= (IxPol-(1/12.0))/(1/12.0)
ratio6= (IyPol-(1/12.0))/(1/12.0)
ratio7= PxyPol

import os
fname= os.path.basename(__file__)
if abs(ratio1)<1e-10 and abs(ratio2)<1e-10 and abs(ratio3)<1e-10 and abs(ratio4)<1e-10 and abs(ratio5)<1e-10 and abs(ratio6)<1e-10 and abs(ratio7)<1e-10:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."

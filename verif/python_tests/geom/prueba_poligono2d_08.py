# -*- coding: utf-8 -*-
import xc_base
import geom
pol1=geom.Poligono2d()
pol1.agregaVertice(geom.Pos2d(0.,0.))
pol1.agregaVertice(geom.Pos2d(4.,0.))
pol1.agregaVertice(geom.Pos2d(4.,1.))
pol1.agregaVertice(geom.Pos2d(0.,1.))

areasTrib=pol1.getAreasTributarias()

ratio1= areasTrib[0]-1
ratio2= areasTrib[1]-1
ratio3= areasTrib[2]-1
ratio4= areasTrib[3]-1

if abs(ratio1)<1e-10 and abs(ratio2)<1e-10:
    print "test poligono2d 08: ok."
else:
    print "test poligono2d 08: ERROR."

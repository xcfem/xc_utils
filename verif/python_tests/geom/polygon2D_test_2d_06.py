# -*- coding: utf-8 -*-
import xc_base
import geom
import math

perimetroTeorico=4+math.sqrt(2)

pol1=geom.Poligono2d()
pol1.agregaVertice(geom.Pos2d(-1.,-1.))
pol1.agregaVertice(geom.Pos2d(1.,-1.))
pol1.agregaVertice(geom.Pos2d(1.,1.))
pol1.agregaVertice(geom.Pos2d(-1.,1.))

pol2=geom.Poligono2d(pol1)
pol2.mueve(geom.Vector2d(1,1))

pol3=geom.Poligono2d()
pol3.agregaVertice(geom.Pos2d(0.,-1.))
pol3.agregaVertice(geom.Pos2d(1.,-1.))
pol3.agregaVertice(geom.Pos2d(1.,2.))
pol3.agregaVertice(geom.Pos2d(0.,2.))

list1=[pol1,pol2]
list1=geom.particiona(list1)
list1=geom.clip(list1,pol3)

p1=list1[0]
ratio1=(p1.getPerimetro()-perimetroTeorico)/perimetroTeorico

p2=list1[1]
ratio2=(p2.getPerimetro()-perimetroTeorico)/perimetroTeorico

import os
fname= os.path.basename(__file__)
if abs(ratio1)<1e-10 and abs(ratio2)<1e-10:
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."

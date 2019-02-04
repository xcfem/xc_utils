# -*- coding: utf-8 -*-
from __future__ import print_function

import xc_base
import geom
pos1= geom.Pos2d(1,2);


exampleNumber= 4
saludo= "Saluda"
pos1.setProp("nuevaPropiedad",saludo)
pos1.lado= 2
pos1.setProp("radius",3)

aa= pos1.getProp("nuevaPropiedad")
#good= aa==saludo

pp= pos1.evalPy("1+1")
ratio1= pp-2
qq= pos1.evalPy("1+exampleNumber")
ratio2= qq-5
rr= pos1.evalPy("1+lado")
ss= pos1.evalPy("1+self.getProp('radius')")

#print pp
#print qq
#print rr
#print "ss= ",ss

import os
fname= os.path.basename(__file__)
if abs(ratio1)<1e-15 and abs(ratio2)<1e-15:
  print("test ",fname,": ok.")
else:
  print("test ",fname,": ERROR.")

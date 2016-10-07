# -*- coding: utf-8 -*-

import xc_base
import geom
import math

pol=geom.Polilinea2d()

pol.agregaVertice(geom.Pos2d(0,0)) #1
pol.agregaVertice(geom.Pos2d(0.5,0.09)) #2 (to erase)
pol.agregaVertice(geom.Pos2d(1,0)) #3
pol.agregaVertice(geom.Pos2d(1.001,0.5)) #4 (to erase)
pol.agregaVertice(geom.Pos2d(1,1)) #5
pol.agregaVertice(geom.Pos2d(2,1)) #6
pol.agregaVertice(geom.Pos2d(2,2)) #7
pol.agregaVertice(geom.Pos2d(1,2)) #8
pol.agregaVertice(geom.Pos2d(1,1)) #9
pol.agregaVertice(geom.Pos2d(0,1)) #10
#pol.agregaVertice(geom.Pos2d(0,0)) #11 MUST NOT BE CLOSED.

nv0= pol.getNumVertices()
pol.simplify(0.1)

nv1= pol.getNumVertices()

ratio0=(nv0-10)/10.0
ratio1=(nv1-8)/8.0

import os
fname= os.path.basename(__file__)
if math.fabs(ratio0)<1e-10 and math.fabs(ratio1)<1e-10 :
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."



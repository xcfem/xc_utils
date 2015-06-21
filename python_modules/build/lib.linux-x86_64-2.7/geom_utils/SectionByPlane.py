# -*- coding: utf-8 -*-

import xc_base
import geom

class SectionByPlane(object):
  name= "-"
  plane= geom.Plano3d(geom.Pos3d(1,0,0), geom.Pos3d(0,1,0), geom.Pos3d(0,0,1))

  def __init__(self,nm,p):
    self.name= nm
    self.plane= p

  def getIntersection(self,pline):
    return pline.getIntersection(plane)

  def getIntersectionPoints(self,listOfPlines):
    retval= geom.Polilinea3d()
    for pline in listOfPlines:
      lp= pline.getIntersection(plane)
      retval.agregaVertice(lp[0])
    return retval

# -*- coding: utf-8 -*-

import xc_base
import geom
import math

class XYFoldingPlanes(object):
  xyPline= None

  def __init__(self,xyPolyline):
    self.xyPline= xyPolyline
  def getIntersectionWith3DLine(self,p0, p1):
    retval= []
    err= 0.0
    proyP0= geom.Pos2d(p0.x,p0.y)
    proyP1= geom.Pos2d(p1.x,p1.y)
    line2d= geom.Recta2d(proyP0,proyP1)
    proy= self.xyPline.getIntersectionWithLine(line2d)
    for p in proy:
      lmb= p.distPos2d(proyP0)/proyP1.distPos2d(proyP0)
      pInt= geom.LineSegment3d(p0,p1).getPoint(lmb)
      err= (pInt.x-p.x)**2+(pInt.y-p.y)**2
      if(err>1e-6):
        print "Error finding intersection; err= ", err
        print "p= ", p
        print "pInt= ", pInt
        print "lmb= ", lmb
      else:
        retval.append(pInt)
    return retval
  def getIntersectionWith3DSegment(self,segment3d):
    retval= []
    p0= segment3d.getOrigen()
    p1= segment3d.getDestino()
    proyP0= geom.Pos2d(p0.x,p0.y)
    proyP1= geom.Pos2d(p1.x,p1.y)
    segment2d= geom.Segmento2d(proyP0,proyP1)
    proy= self.xyPline.getIntersectionWithSegment(segment2d)
    for p in proy:
      lmb= p.distPos2d(proyP0)/proyP1.distPos2d(proyP0)
      pInt= segment3d.getPoint(lmb)
      retval.append(pInt)
    return retval  



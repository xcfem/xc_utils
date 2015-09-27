# -*- coding: utf-8 -*-

from __future__ import division

import math
import cairo

class Boundary(object):
  def __init__(self,xmin,ymin,xmax,ymax):
    self.xmin= xmin
    self.xmax= xmax
    self.ymin= ymin
    self.ymax= ymax
  def getXCenter(self):
    return (self.xmax+self.xmin)/2.0
  def getYCenter(self):
    return (self.ymax+self.ymin)/2.0
  def getXWidth(self):
    return self.xmax-self.xmin
  def getYWidth(self):
    return self.ymax-self.ymin

class TransformParams(object):
  def __init__(self,w,h,bnd):
    self.w= w #User space width.
    self.h= h #User space height.
    self.bnd= bnd
  def getScale(self):
    eX= self.w/self.bnd.getXWidth()
    print "eX= ", eX
    eY= self.h/self.bnd.getYWidth()
    print "eY= ", eY
    return min(eX,eY)
  def applyTransform(self,ctx):
    scale= self.getScale()
    print "scale= ", scale
    x0= scale*self.bnd.getXCenter()#-self.w/2.0
    y0= scale*self.bnd.getYCenter()#-self.h/2.0
    print "x0= ", x0, " y0= ", y0
    ctx.translate(x0, y0)
    ctx.scale(scale, scale)
    

def plotPolygon(plg,ctx):
  # Dibuja el contorno del polígono cuyo nombre se pasa como parámetro.ç
  nv= plg.getNumVertices()
  ptPlot= plg.getVertice(0)
  ctx.move_to(ptPlot.x,ptPlot.y)
  for i in range(1,nv):
    ptPlot= plg.getVertice(i)
    ctx.line_to(ptPlot.x,ptPlot.y)
  ptPlot= plg.getVertice(0)
  ctx.line_to(ptPlot.x,ptPlot.y)

def plotEjesYZ(long,ctx):
  '''Dibuja los ejes Y y Z en el origen de coordenadas
   con la longitud que se pasa como parámetro.'''
  ctx.set_line_width(long/40)
  ctx.move_to(0,0)
  ctx.set_source_rgb(0, 1, 0) # Green color
  ctx.line_to(long,0)
  ctx.text_path("Y")
  ctx.move_to(0,0)
  ctx.set_source_rgb(0, 0, 1) # Blue color
  ctx.move_to(0,long)
  ctx.text_path("Z")

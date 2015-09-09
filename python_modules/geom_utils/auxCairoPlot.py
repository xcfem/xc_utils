# -*- coding: utf-8 -*-

import math
import cairo

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
  ctx.set_source_rgb(0, 0, 1) # Green color
  ctx.move_to(0,long)
  ctx.text_path("Z")

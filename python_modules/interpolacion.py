# -*- coding: utf-8 -*-

def interpolaRecta(x0,y0,x1,y1,x):
  ''' Return the value obtained interpolating with a line
      that passes through the points (x0,y0) y (x1,y1)'''
  return (y1-y0)/(x1-x0)*(x-x0)+y0 

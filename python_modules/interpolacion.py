# -*- coding: utf-8 -*-

# Devuelve el valor que resulta de interopolar mediante una recta que pasa por los puntos (x0,y0) y (x1,y1) }
def interpolaRecta(x0,y0,x1,y1,x):
  return (y1-y0)/(x1-x0)*(x-x0)+y0 

# -*- coding: utf-8 -*-

import math

# Coeficientes de rozamiento del cimiento con el terreno
mapAngRozCimTerrIGP2011= { 'RocaSana':math.atan(0.7), 'Grava':math.atan(0.6), 'Arena':math.atan(0.6), 'RecaDescomp':math.atan(0.4), 'SueloArcilloso':math.atan(0.3), 'SueloLimoso':math.atan(0.4)}


'''Devuelve el ángulo de rozamiento del cimiento de hormigón
con el terreno según la versión 2011 del IGP de Adif.
Ver IGP-5.2 Bases de cálculo para estructuras de ferrocarril
página 5'''
def angRozCimTerrIGP2011(tipoTerr):
  angRzCimTrrTmp= 0.4
  angRzCimTrrTmp= mapAngRozCimTerrIGP2011[tipoTerr]
  return angRzCimTrrTmp


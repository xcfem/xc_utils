# -*- coding: utf-8 -*-
from __future__ import division
import FrictionalSoil as fs
import math

'''earthPressureRankine.py: earth pressures from Rankine's Theory.'''

__author__= "Luis C. Pérez Tato (LCPT)"
__copyright__= "Copyright 2016, LCPT"
__license__= "GPL"
__version__= "3.0"
__email__= "l.pereztato@gmail.com"

# From Wikipedia:



class RankineSoil(fs.FrictionalSoil):
  '''From Wikipedia: Rankine's theory, developed in 1857, is a stress field solution that predicts active and passive earth pressure. It assumes that the soil is cohesionless, the wall is frictionless, the soil-wall interface is vertical, the failure surface on which the soil moves is planar, and the resultant force is angled parallel to the backfill surface. The equations for active and passive lateral earth pressure coefficients are given below. Note that φ is the angle of shearing resistance of the soil and the backfill is inclined at angle β to the horizontal.

  :ivar phi:    internal friction angle of the soil
  :ivar beta:   angle of backfill with horizontal
  '''
  def __init__(self,phi,beta= 0.0,rho= 2100.0):
    super(RankineSoil,self).__init__(phi,rho)
    self.beta= beta
  def Ka(self):
    '''Returns Rankine's active earth pressure coefficient.'''
    cBeta= math.cos(self.beta)
    cPhi= math.cos(self.phi)
    r= math.sqrt(cBeta**2-cPhi**2)
    return cBeta*(cBeta-r)/(cBeta+r)
  def Kp(self):
    '''Returns Rankine's passive earth pressure coefficient.'''
    cBeta= math.cos(self.beta)
    cPhi= math.cos(self.phi)
    r= math.sqrt(cBeta**2-cPhi**2)
    return cBeta*(cBeta+r)/(cBeta-r)

# -*- coding: utf-8 -*-
from __future__ import division
import math

'''FrictionalSoil.py: frictional (or cohesionless) soil model.'''

__author__= "Luis C. Pérez Tato (LCPT)"
__copyright__= "Copyright 2016, LCPT"
__license__= "GPL"
__version__= "3.0"
__email__= "l.pereztato@gmail.com"

class FrictionalSoil(object):
  '''Free-running type of soil, such as sand or gravel, whose strength depends on friction between particles.

  :ivar phi:    internal friction angle of the soil
  :ivar rho:   soil density (mass per unit volume)
  '''
  def __init__(self,phi,rho= 2100.0):
    self.phi= phi
    self.rho= rho
  def K0Jaky(self):
    '''Returns Jaky's earth pressure at rest.'''
    return 1.0-math.sin(self.phi)

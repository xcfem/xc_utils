# -*- coding: utf-8 -*-
from __future__ import division
import math
import FrictionalSoil as fs

'''FrictionalCohesionalSoil.py: soil with friction and cohesion soil model.

References: 

[1] Chapter 4-3 of Foundation Analysis and Design, Ed. 5 by Joseph E. Bowles.
[2] Brinch Hansen. A general formula for bearing capacity. The Danish Geotechnical Institute. Bulletin 11. Copenhagen 1961.
[3] Guía de cimentaciones en obras de carretera. Ministerio de Fomento (spain). 2002.
'''

__author__= "Luis C. Pérez Tato (LCPT)"
__copyright__= "Copyright 2016, LCPT"
__license__= "GPL"
__version__= "3.0"
__email__= "l.pereztato@gmail.com"

class FrictionalCohesionalSoil(fs.FrictionalSoil):
  '''Soil with friction and cohesion

  :ivar c:    soil cohesion
  '''
  def __init__(self,phi,c,rho= 2100.0):
    '''Constructor.

    :param phi:    internal friction angle of the soil.
    :param c: soil cohesion.
    :param rho:   soil density (mass per unit volume).
    '''
    super(FrictionalCohesionalSoil,self).__init__(phi,rho)
    self.c= c
    
  def iq(self,deltaB,deltaL):
    '''Factor that introduces the effect of load inclination.

    :param deltaB: angle between the load and the foundation width
                   atan(HloadB/VLoad).
    :param deltaL: angle between the load and the foundation length
                   atan(HloadL/VLoad). 
    '''
    return (1-0.7*math.tan(deltaB))**3/(1-0.7*math.tan(deltaL))**3

  def dq(self,D,Beff):
    '''Overburden factor for foundation depth.

       :param D: foundation depth.
       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    k= min(D,2.0*Beff)/Beff
    return 1+2*math.tan(self.phi)*(1-math.sin(self.phi))**2*math.atan(k)
  
  def Nq(self):
    '''Returns the overburden multiplier for the Brinch-Hasen formula.'''
    return self.Kp()*math.exp(math.pi*math.tan(self.phi))

  def dc(self,D,Beff):
    '''Overburden factor for cohesion.

       :param D: foundation depth.
       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    k= min(D,2.0*Beff)/Beff
    return 1+2*self.Nq()/self.Nc()*(1-math.sin(self.phi))**2*math.atan(k)
  
  def Nc(self):
    '''Returns the cohesion multiplier for the Brinch-Hasen formula.'''
    return (self.Nq()-1.0)*(1.0/math.tan(self.phi))
                                                         
  def dgamma(self):
    '''Wedge weigth factor.'''
    return 1.0

  def Ngamma(self,coef= 1.5):
    '''Returns the wedge weight multiplier for the Brinch-Hasen formula.

       :param coef: 1.5 in reference [1] and 1.8 in reference 2'''
    return coef*(self.Nq()-1.0)*math.tan(self.phi)

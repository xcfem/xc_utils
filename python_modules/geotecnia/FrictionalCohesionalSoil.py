# -*- coding: utf-8 -*-
from __future__ import division
import math
import FrictionalSoil as fs
from miscUtils import LogMessages as lmsg

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
  def __init__(self,phi,c,cu,rho= 2100.0):
    '''Constructor.

    :param phi:    internal friction angle of the soil.
    :param c: soil cohesion.
    :param cu: undrained shear strength.
    :param rho:   soil density (mass per unit volume).
    '''
    super(FrictionalCohesionalSoil,self).__init__(phi,rho)
    self.c= c
    self.cu= cu 
    
  def sq(self,Beff,Leff):
    '''Factor that introduces the effect of foundation shape on
       the overburden component.

       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
       :param Leff: Length of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    return 1.0+Beff/Leff*self.Nq()/self.Nc()

  def iq(self,deltaB,deltaL):
    '''Factor that introduces the effect of load inclination on
       the overburden component.

    :param deltaB: angle between the load and the foundation width
                   atan(HloadB/VLoad).
    :param deltaL: angle between the load and the foundation length
                   atan(HloadL/VLoad). 
    '''
    return (1.0-0.7*math.tan(deltaB))**3*(1.0-math.tan(deltaL))

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

  def sc(self,Beff,Leff):
    '''Factor that introduces the effect of foundation shape on
       the cohesion component.

    :param Beff: Width of the effective foundation area
                (see figure 12 in page 44 of reference[2]).
    :param Leff: Length of the effective foundation area
                (see figure 12 in page 44 of reference[2]).
    '''
    return self.sq(Beff,Leff)

  def ic(self,deltaB,deltaL,Hload,Beff,Leff):
    '''Factor that introduces the effect of load inclination on
       the cohesion component.

    :param deltaB: angle between the load and the foundation width
                   atan(HloadB/VLoad).
    :param deltaL: angle between the load and the foundation length
                   atan(HloadL/VLoad).
    :param Hload: Horizontal load. 
    :param Beff: Width of the effective foundation area
                 (see figure 12 in page 44 of reference[2]).
    :param Leff: Length of the effective foundation area
                (see figure 12 in page 44 of reference[2]).
    '''
    if(self.phi!=0.0):
      iq= self.iq(deltaB,deltaL)
      return (iq*self.Nq()-1.0)/(self.Nq()-1.0)
    else: #See expresion (15) in reference [2]
      resist= Beff*Leff*self.cu
      if(Hload<=resist):
        twoAlpha= math.acos(Hload/resist)
        return 0.5+(twoAlpha+math.sin(twoAlpha))/(math.pi+2.0)
      else:
        lmsg.warning('Load (H= '+str(Hload)+') greater than soil strength R='+str(resist)+' returns 0.0')
        return 0.0

  def dc(self,D,Beff):
    '''Depth factor for cohesion.

       :param D: foundation depth.
       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    k= min(D,2.0*Beff)/Beff
    return 1+2*self.Nq()/self.Nc()*(1-math.sin(self.phi))**2*math.atan(k)
  
  def Nc(self):
    '''Returns the cohesion multiplier for the Brinch-Hasen formula.'''
    if(self.phi!=0.0):
      return (self.Nq()-1.0)*(1.0/math.tan(self.phi))
    else:
      return math.pi+2.0
                                                         
  def sgamma(self,Beff,Leff):
    '''Factor that introduces the effect of foundation shape on
       the self weight component.

       :param Beff: Width of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
       :param Leff: Length of the effective foundation area
                    (see figure 12 in page 44 of reference[2]).
    '''
    return 1.0-0.3*Beff/Leff

  def igamma(self,deltaB,deltaL):
    '''Factor that introduces the effect of load inclination on
       the self weight component.

    :param deltaB: angle between the load and the foundation width
                   atan(HloadB/VLoad).
    :param deltaL: angle between the load and the foundation length
                   atan(HloadL/VLoad). 
    '''
    return (1-math.tan(deltaB))**3*(1-math.tan(deltaL))

  def dgamma(self):
    '''Factor that introduces the effect of foundation depth on
       the self weight component.'''
    return 1.0

  def Ngamma(self,coef= 1.5):
    '''Returns the wedge weight multiplier for the Brinch-Hasen formula.

       :param coef: 1.5 in reference [1] and 1.8 in reference 2'''
    return coef*(self.Nq()-1.0)*math.tan(self.phi)

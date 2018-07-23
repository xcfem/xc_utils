# -*- coding: utf-8 -*-
from __future__ import division
import math
from scipy.constants import g
from geotechnics import mononobe_okabe

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
  def __init__(self,phi,rho= 2100.0,gammaMPhi= 1.0):
    '''Constructor.

        Args:
            :phi: (float) internal friction angle of the soil
            :rho: (float) soil density (mass per unit volume)
            :gammaMPhi: (float) partial reduction factor for internal 
                        friction angle of the soil.
    '''
    self.phi= phi
    self.gammaMPhi= gammaMPhi
    self.rho= rho
  def K0Jaky(self):
    '''Returns Jaky's earth pressure at rest.'''
    return 1.0-math.sin(self.getDesignPhi())
  def Ka(self):
    '''Passive earth pressure coefficient.'''
    sinPhi= math.sin(self.getDesignPhi())
    return (1-sinPhi)/(1+sinPhi)
  def Kp(self):
    '''Passive earth pressure coefficient.'''
    sinPhi= math.sin(self.getDesignPhi())
    return (1+sinPhi)/(1-sinPhi)
  def gamma(self):
    '''Unit weight of soil'''
    return self.rho*g
  def getDesignPhi(self):
    '''Return the design value of the soil internal friction angle.'''
    return self.phi/self.gammaMPhi
  def getMononobeOkabeDryOverpressure(self,H,kv,kh,psi= math.radians(90),delta_ad= 0.0,beta= 0.0,Kas= None,g= 9.81):
    ''' Overpressure due to seismic action according to Mononobe-Okabe

        Args:
        :H: height of the structure.
        :kv: seismic coefficient of vertical acceleration.
        :kh: seismic coefficient of horizontal acceleration.
        :psi: back face inclination of the structure (< PI/2)
        :beta: slope inclination of backfill.
        :delta_ad: angle of friction soil - structure.
        :Kas: static earth pressure coefficient 
    '''
    gamma_soil= self.rho*g
    phi_d= math.atan(math.tan(self.phi)/1.25)
    if(Kas==None):
      Kas= self.Ka()
    return mononobe_okabe.overpressure_dry(H, gamma_soil, kv, kh, psi, phi_d, delta_ad,beta,Kas)

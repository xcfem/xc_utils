# -*- coding: utf-8 -*-

from __future__ import division

import math

# Mononobe-Okabe theory.

def active_earth_pressure_coefficient_Kad(psi, phi, theta, delta_ad,beta):
  ''' Return the active earth pressure coefficient according
      to Mononobe-Okabe.

      Args:
      :psi: back face inclination of the structure (< PI/2)ç
      :phi: angle of internal friction of soil.
      :theta: angle of weight with vertical:
         kv= seismic coefficient of vertical acceleration.
         kh= seismic coefficient of horizontal acceleration.
         tan(theta)= kh/(1+kv) AND tan(theta)= kh/(1-kv)
      :delta_ad: angle of friction soil - structure.
      :beta: slope inclination of terrain.'''
  num= (math.sin(psi+phi-theta))**2
  denom1= math.cos(theta)*(math.sin(psi))**2*math.sin(psi-theta-delta_ad)
  numA= math.sin(phi+delta_ad)*math.sin(phi-beta-theta)
  denomA= math.sin(psi-theta-delta_ad)*math.sin(psi+beta)
  denom2= (1+math.sqrt(numA/denomA))**2
  denom= denom1*denom2
  return num/denom

def overpressure_dry(H, gamma_soil, kv, kh, psi, phi, delta_ad, beta, Kas):
  ''' Overpressure due to seismic action according to Mononobe-Okabe

      Args:
      :H: height of the structure.
      :gamma_soil: unit weight of soil (backfill)
      :kv: seismic coefficient of vertical acceleration.
      :kh: seismic coefficient of horizontal acceleration.
      :psi: back face inclination of the structure (< PI/2)
      :phi: angle of internal friction of soil.
      :delta_ad: angle of friction soil - structure.
      :beta: slope inclination of backfill.
      :Kas: static earth pressure coefficient 
  '''
  theta= math.atan(kh/(1+kv)) #angle of weight with vertical:
                              #tan(theta)= kh/(1+kv) AND tan(theta)= kh/(1-kv)
  K_ad= active_earth_pressure_coefficient_Kad(psi, phi, theta, delta_ad,beta)
  minuendo= (1+kv)*K_ad
  factor= minuendo-Kas
  return 0.5*gamma_soil*H**2*factor

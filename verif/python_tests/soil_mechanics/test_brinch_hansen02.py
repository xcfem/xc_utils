# -*- coding: utf-8 -*-

'''
Verification of the Brinch Hansen formula.

See Brinch Hansen. A general formula for bearing capacity. The Danish Geotechnical Institute. Bulletin 11. Copenhagen 1961. Example on page 45
'''

__author__= "Luis C. Pérez Tato (LCPT)"
__copyright__= "Copyright 2016, LCPT"
__license__= "GPL"
__version__= "3.0"
__email__= "l.pereztato@gmail.com"

from geotecnia import FrictionalCohesionalSoil as fcs
import math

shortTermSoil= fcs.FrictionalCohesionalSoil(0.0,c=3,cu=10.3,rho= 2.2)

D= 2.0 #Foundation depth
Beff= 5.5 #Effective foundation width
Leff= 9.0 #Effective foundation length
V= 3000 #Vertical load
H= 225 #Horizontal load.
deltaB= math.atan(H/V)
deltaL= 0.0

NgammaSTS= shortTermSoil.Ngamma(1.8)
NqSTS= shortTermSoil.Nq()
NcSTS= shortTermSoil.Nc()
dcSTS= shortTermSoil.dc(D,Beff)
scSTS= shortTermSoil.sc(Beff,Leff)
icSTS= shortTermSoil.ic(deltaB,deltaL,H,Beff,Leff)

err= abs(NgammaSTS)**2
err+= abs(NqSTS-1.0)**2
err+= (abs(NcSTS-5.1)/5.1)**2
err+= (abs(dcSTS-1.13)/1.13)**2
err+= (abs(scSTS-1.12)/1.12)**2
err+= (abs(icSTS-0.89)/0.89)**2

'''
print 'NgammaSTS= ', NgammaSTS
print 'NqSTS= ', NqSTS
print 'NcSTS= ', NcSTS
print 'dcSTS= ', dcSTS
print 'scSTS= ', scSTS
print 'icSTS= ', icSTS
print 'err= ', err
'''

import os
fname= os.path.basename(__file__)
if (err<0.05):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."

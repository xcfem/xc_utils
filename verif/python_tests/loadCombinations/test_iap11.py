# -*- coding: utf-8 -*-

import xc_base
import loadCombinations
from loadCombinationUtils import iap11
from loadCombinationUtils import utils

lcg= iap11.controlCombGenerator
#print '*******', pond.permanentActions.gammaF.getGammaFELU.desfavorable

G1= lcg.insert("IAP11","permanentes",loadCombinations.Action("G1", "Peso propio"),"permanente","default")
G2= lcg.insert("IAP11","permanentes",loadCombinations.Action("G2", "Carga muerta"),"permanente","default")
G3= lcg.insert("IAP11","permanentes",loadCombinations.Action("G3", "Retracc."),"permanente","")
Q1a_1= lcg.insert("IAP11","variables",loadCombinations.Action("Q1a_1", "Tren cargas pos. 1a_1"),"vehículos_pesados","SCuso")
Q1a_2= lcg.insert("IAP11","variables",loadCombinations.Action("Q1a_2", "Tren cargas pos. 1a_2"),"vehículos_pesados","SCuso")

      

lcg.genera()
coeficientesRef_elu_persistentes= [[1.0, 1.0, 1.0, 0.0, 0.0], [1.0, 1.0, 1.35, 0.0, 0.0], [1.0, 1.35, 1.0, 0.0, 0.0], [1.0, 1.35, 1.35, 0.0, 0.0], [1.35, 1.0, 1.0, 0.0, 0.0], [1.35, 1.0, 1.35, 0.0, 0.0], [1.35, 1.35, 1.0, 0.0, 0.0], [1.35, 1.35, 1.35, 0.0, 0.0], [1.0, 1.0, 1.0, 1.35, 0.0], [1.0, 1.0, 1.0, 1.35, 1.01], [1.0, 1.0, 1.0, 0.0, 1.35], [1.0, 1.0, 1.0, 1.01, 1.35], [1.0, 1.0, 1.35, 1.35, 0.0], [1.0, 1.0, 1.35, 1.35, 1.01], [1.0, 1.0, 1.35, 0.0, 1.35], [1.0, 1.0, 1.35, 1.01, 1.35], [1.0, 1.35, 1.0, 1.35, 0.0], [1.0, 1.35, 1.0, 1.35, 1.01], [1.0, 1.35, 1.0, 0.0, 1.35], [1.0, 1.35, 1.0, 1.01, 1.35], [1.0, 1.35, 1.35, 1.35, 0.0], [1.0, 1.35, 1.35, 1.35, 1.01], [1.0, 1.35, 1.35, 0.0, 1.35], [1.0, 1.35, 1.35, 1.01, 1.35], [1.35, 1.0, 1.0, 1.35, 0.0], [1.35, 1.0, 1.0, 1.35, 1.01], [1.35, 1.0, 1.0, 0.0, 1.35], [1.35, 1.0, 1.0, 1.01, 1.35], [1.35, 1.0, 1.35, 1.35, 0.0], [1.35, 1.0, 1.35, 1.35, 1.01], [1.35, 1.0, 1.35, 0.0, 1.35], [1.35, 1.0, 1.35, 1.01, 1.35], [1.35, 1.35, 1.0, 1.35, 0.0], [1.35, 1.35, 1.0, 1.35, 1.01], [1.35, 1.35, 1.0, 0.0, 1.35], [1.35, 1.35, 1.0, 1.01, 1.35], [1.35, 1.35, 1.35, 1.35, 0.0], [1.35, 1.35, 1.35, 1.35, 1.01], [1.35, 1.35, 1.35, 0.0, 1.35], [1.35, 1.35, 1.35, 1.01, 1.35]]

coeficientes_elu_persistentes= []
combAcc= lcg.getLoadCombinations.getULSTransientCombinations
base= xc_base.vector_string_from_py_list(["G1","G2","G3","Q1a_1","Q1a_2"])
for comb in combAcc:
  coeficientes_elu_persistentes.append(xc_base.vector_double_to_py_list(comb.getCoeficientes(base)))

error= 0
import numpy
sz= len(coeficientesRef_elu_persistentes)
for i in range(0,sz):
  vR= coeficientesRef_elu_persistentes[i]
  v= coeficientes_elu_persistentes[i]
  #print "vR", vR, " v= ", v
  resta= numpy.subtract(vR,v)
  error+= numpy.linalg.norm(resta)**2
  #print resta
  #print "error= ", error

import math
error= math.sqrt(error)


'''
utils.listActionWeighting(lcg.actionWeighting)
print coeficientes_elu_persistentes
print "error= ", error
lc=lcg.getLoadCombinations
ULS=lc.getULSTransientCombinations
comb=[c for c in ULS]
for c in comb:
    print c.descripcion
'''
import os
fname= os.path.basename(__file__)
if (abs(error)<1e-6):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."


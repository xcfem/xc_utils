# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#Coeficientes de ponderación para acciones permanentes.
gammaf_permanentes_42IC= loadCombinations.GammaF(loadCombinations.GammaFULS(0.9,1.6,1,1),loadCombinations.GammaFSLS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante.
gammaf_permanentes_nc_42IC= loadCombinations.GammaF(loadCombinations.GammaFULS(0.9,0.75*1.6,0,1),loadCombinations.GammaFSLS(1,1))
#Coeficientes de ponderación para acciones variables.
gammaf_variables_42IC= loadCombinations.GammaF(loadCombinations.GammaFULS(0,1.6,0,1),loadCombinations.GammaFSLS(0,1))



# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#Coeficientes de ponderación para acciones permanentes.
gammaf_permanentes_EAE= loadCombinations.GammaF(loadCombinations.GammaFULS(1,1.35,1,1),loadCombinations.GammaFSLS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante.
gammaf_permanentes_nc_EAE= loadCombinations.GammaF(loadCombinations.GammaFULS(1,1.5,1,1),loadCombinations.GammaFSLS(1,1))
#Coeficientes de ponderación para acciones variables.
gammaf_variables_EAE= loadCombinations.GammaF(loadCombinations.GammaFULS(0,1.5,0,1),loadCombinations.GammaFSLS(0,1))
#Coeficientes de ponderación para acciones sísmicas.
gammaf_sismicas_EAE= loadCombinations.GammaF(loadCombinations.GammaFULS(0,1,1,1),loadCombinations.GammaFSLS(0,0))
#Coeficientes de ponderación para acciones accidentales.
gammaf_accidentales_EAE= loadCombinations.GammaF(loadCombinations.GammaFULS(0,0,1,1),loadCombinations.GammaFSLS(0,0))

combination_factors_EAE= loadCombinations.CombinationFactorsDict()

combination_factors_EAE.insert("zonas_residenciales",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EAE.insert("zonas_oficinas",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EAE.insert("zonas_reunion",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EAE.insert("zonas_comerciales",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EAE.insert("zonas_almacen",loadCombinations.CombinationFactors(1.0,0.9,0.8))
combination_factors_EAE.insert("zonas_trafico_veh_ligeros",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EAE.insert("zonas_trafico_veh_pesados",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EAE.insert("cubiertas_inaccesibles",loadCombinations.CombinationFactors(0.0,0.0,0.0))





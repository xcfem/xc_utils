# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#Coeficientes de ponderación para acciones permanentes.
partial_safety_factors_permanentes_EAE= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante.
partial_safety_factors_permanentes_nc_EAE= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.5,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones variables.
partial_safety_factors_variables_EAE= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.5,0,1),loadCombinations.SLSPartialSafetyFactors(0,1))
#Coeficientes de ponderación para acciones sísmicas.
partial_safety_factors_sismicas_EAE= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))
#Coeficientes de ponderación para acciones accidentales.
partial_safety_factors_accidentales_EAE= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,0,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))

combination_factors_EAE= loadCombinations.CombinationFactorsDict()

combination_factors_EAE.insert("zonas_residenciales",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EAE.insert("zonas_oficinas",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EAE.insert("zonas_reunion",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EAE.insert("zonas_comerciales",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EAE.insert("zonas_almacen",loadCombinations.CombinationFactors(1.0,0.9,0.8))
combination_factors_EAE.insert("zonas_trafico_veh_ligeros",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EAE.insert("zonas_trafico_veh_pesados",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EAE.insert("cubiertas_inaccesibles",loadCombinations.CombinationFactors(0.0,0.0,0.0))





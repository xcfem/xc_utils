# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#Coeficientes de ponderación para acciones permanentes.
partial_safety_factors_permanentes_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P1 (armaduras postesas).
partial_safety_factors_permanentes_nc_Pret1Post_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1,1,1),loadCombinations.SLSPartialSafetyFactors(0.9,1.1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P1 (armaduras pretesas).
partial_safety_factors_permanentes_nc_Pret1Pret_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1,1,1),loadCombinations.SLSPartialSafetyFactors(0.95,1.05))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P2.
partial_safety_factors_permanentes_nc_Pret2_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a efectos reológicos (retracción y fluencia).
partial_safety_factors_permanentes_nc_Reol_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a acciones provocadas por el balasto.
partial_safety_factors_permanentes_nc_CMBalasto_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.35,0,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a acciones provocadas por empujes o movimientos del terreno.
partial_safety_factors_permanentes_nc_Terr_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.5,0,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a otras presolicitaciones distintas del pretensado.
partial_safety_factors_permanentes_nc_OtrasPresol_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0.95,1.05,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones variables.
partial_safety_factors_variables_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.5,0,1),loadCombinations.SLSPartialSafetyFactors(0,1))
#Coeficientes de ponderación para acciones accidentales.
partial_safety_factors_accidentales_IAP= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,0,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))

combination_factors_IAP= loadCombinations.CombinationFactorsDict()

combination_factors_IAP.insert("permanent",loadCombinations.CombinationFactors(1,1,1))
combination_factors_IAP.insert("snow",loadCombinations.CombinationFactors(0.6,0.2,0.0))
combination_factors_IAP.insert("wind",loadCombinations.CombinationFactors(0.6,0.5,0.0))
combination_factors_IAP.insert("thermal",loadCombinations.CombinationFactors(0.6,0.5,0.0))
combination_factors_IAP.insert("sismo",loadCombinations.CombinationFactors(0,0,0))
combination_factors_IAP.insert("arranque_frenado",loadCombinations.CombinationFactors(0.6,0.2,0))
combination_factors_IAP.insert("por_defecto",loadCombinations.CombinationFactors(0.7,0.7,0.6))

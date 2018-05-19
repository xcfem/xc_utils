# -*- coding: utf-8 -*-
#import sys
#sys.path.append('usr/local/src/fuentes/c/biblioteca/xc_utils/lib/')

import xc_base
import loadCombinations

#Coeficientes de ponderación para acciones permanentes.
partial_safety_factors_permanentes_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P1 (armaduras postesas).
partial_safety_factors_permanentes_nc_Pret1Post_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1,1,1),loadCombinations.SLSPartialSafetyFactors(0.9,1.1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P1 (armaduras pretesas).
partial_safety_factors_permanentes_nc_Pret1Pret_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1,1,1),loadCombinations.SLSPartialSafetyFactors(0.95,1.05))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P2.
partial_safety_factors_permanentes_nc_Pret2_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a efectos reológicos (retracción y fluencia).
partial_safety_factors_permanentes_nc_Reol_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a acciones provocadas por el balasto.
partial_safety_factors_permanentes_nc_CMBalasto_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.35,0,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a acciones provocadas por empujes o movimientos del terreno.
partial_safety_factors_permanentes_nc_Terr_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.5,0,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a otras presolicitaciones distintas del pretensado.
partial_safety_factors_permanentes_nc_OtrasPresol_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0.95,1.05,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones variables.
partial_safety_factors_variables_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.5,0,1),loadCombinations.SLSPartialSafetyFactors(0,1))
#Coeficientes de ponderación para acciones sísmicas.
partial_safety_factors_sismicas_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))
#Coeficientes de ponderación para acciones accidentales.
partial_safety_factors_accidentales_IAPF= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,0,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))

combination_factors_IAPF= loadCombinations.CombinationFactorsDict()

combination_factors_IAPF.insert("permanent",loadCombinations.CombinationFactors(1,1,1))
combination_factors_IAPF.insert("snow",loadCombinations.CombinationFactors(0.6,0.2,0.0))
combination_factors_IAPF.insert("wind",loadCombinations.CombinationFactors(0.6,0.5,0.0))
combination_factors_IAPF.insert("thermal",loadCombinations.CombinationFactors(0.6,0.5,0.0))
combination_factors_IAPF.insert("sismo",loadCombinations.CombinationFactors(0,0,0))
combination_factors_IAPF.insert("arranque_frenado",loadCombinations.CombinationFactors(0.6,0.2,0))
combination_factors_IAPF.insert("por_defecto",loadCombinations.CombinationFactors(0.7,0.7,0.6))


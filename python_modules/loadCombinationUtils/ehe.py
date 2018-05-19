# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

combination_factors_EHE= loadCombinations.CombinationFactorsDict()

combination_factors_EHE.insert("permanent",loadCombinations.CombinationFactors(1,1,1))
combination_factors_EHE.insert("snow",loadCombinations.CombinationFactors(0.6,0.2,0.0))
combination_factors_EHE.insert("wind",loadCombinations.CombinationFactors(0.6,0.5,0.0))
combination_factors_EHE.insert("thermal",loadCombinations.CombinationFactors(0.6,0.5,0.0))
combination_factors_EHE.insert("sismo",loadCombinations.CombinationFactors(0,0,0))
combination_factors_EHE.insert("azotea_solo_conserv",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EHE.insert("vivienda",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EHE.insert("dormitorios_hotel",loadCombinations.CombinationFactors(0.7,0.5,0.3))
combination_factors_EHE.insert("pasillos_escaleras_hotel",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EHE.insert("salones_hotel",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EHE.insert("aulas_escuela",loadCombinations.CombinationFactors(0.7,0.7,0.6))
combination_factors_EHE.insert("pasillos_escaleras_escuela",loadCombinations.CombinationFactors(0.7,0.7,0.6))
#Coeficientes de ponderación para acciones permanentes, control de ejecución normal.
partial_safety_factors_permanentes_EHE_ctr_normal= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))

#Coeficientes de ponderación para acciones permanentes de valor no constante, control de ejecución normal.
partial_safety_factors_permanentes_nc_EHE_ctr_normal= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.5,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones variables, control de ejecución normal.
partial_safety_factors_variables_EHE_ctr_normal= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.5,0,1),loadCombinations.SLSPartialSafetyFactors(0,1))
#Coeficientes de ponderación para acciones sísmicas, control de ejecución normal.
partial_safety_factors_sismicas_EHE_ctr_normal= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))
#Coeficientes de ponderación para acciones accidentales, control de ejecución normal.
partial_safety_factors_accidentales_EHE_ctr_normal= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,0,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))
#Coeficientes de ponderación para acciones permanentes, control de ejecución intenso.
partial_safety_factors_permanentes_EHE_ctr_intenso= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.35,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))

#Coeficientes de ponderación para acciones permanentes de valor no constante, control de ejecución intenso.
partial_safety_factors_permanentes_nc_EHE_ctr_intenso= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(1,1.5,1,1),loadCombinations.SLSPartialSafetyFactors(1,1))
#Coeficientes de ponderación para acciones variables, control de ejecución intenso.
partial_safety_factors_variables_EHE_ctr_intenso= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.5,0,1),loadCombinations.SLSPartialSafetyFactors(0,1))
#Coeficientes de ponderación para acciones sísmicas, control de ejecución intenso.
partial_safety_factors_sismicas_EHE_ctr_intenso= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))
#Coeficientes de ponderación para acciones accidentales, control de ejecución intenso.
partial_safety_factors_accidentales_EHE_ctr_intenso= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,0,1,1),loadCombinations.SLSPartialSafetyFactors(0,0))

intenseControlCombGenerator= loadCombinations.LoadCombGenerator()
pond= intenseControlCombGenerator.defPonderacion("EHEIntenso",combination_factors_EHE)
pond.permanentActions['default'].partial_safety_factors= partial_safety_factors_permanentes_EHE_ctr_intenso
pond.variableActions['default'].partial_safety_factors= partial_safety_factors_variables_EHE_ctr_intenso
pond.accidentalActions.partial_safety_factors= partial_safety_factors_accidentales_EHE_ctr_intenso
pond.seismicActions.partial_safety_factors= partial_safety_factors_sismicas_EHE_ctr_intenso

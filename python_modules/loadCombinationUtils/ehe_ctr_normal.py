# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#Coeficientes de ponderación para acciones permanentes, control de ejecución normal.
gammaf_permanentes_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante, control de ejecución normal.
gammaf_permanentes_nc_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.5,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones variables, control de ejecución normal.
gammaf_variables_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Coeficientes de ponderación para acciones sísmicas, control de ejecución normal.
gammaf_sismicas_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1,1,1),loadCombinations.GammaFELS(0,0))
#Coeficientes de ponderación para acciones accidentales, control de ejecución normal.
gammaf_accidentales_EHE_ctr_normal= loadCombinations.GammaF(loadCombinations.GammaFELU(0,0,1,1),loadCombinations.GammaFELS(0,0))

coefs_psi_EHE= loadCombinations.DictCoefsPsi()

coefs_psi_EHE.insert("permanente",loadCombinations.CoefsPsi(1,1,1))
coefs_psi_EHE.insert("nieve",loadCombinations.CoefsPsi(0.6,0.2,0.0))
coefs_psi_EHE.insert("viento",loadCombinations.CoefsPsi(0.6,0.5,0.0))
coefs_psi_EHE.insert("term",loadCombinations.CoefsPsi(0.6,0.5,0.0))
coefs_psi_EHE.insert("sismo",loadCombinations.CoefsPsi(0,0,0))
coefs_psi_EHE.insert("azotea_solo_conserv",loadCombinations.CoefsPsi(0.7,0.5,0.3))
coefs_psi_EHE.insert("vivienda",loadCombinations.CoefsPsi(0.7,0.5,0.3))
coefs_psi_EHE.insert("dormitorios_hotel",loadCombinations.CoefsPsi(0.7,0.5,0.3))
coefs_psi_EHE.insert("pasillos_escaleras_hotel",loadCombinations.CoefsPsi(0.7,0.7,0.6))
coefs_psi_EHE.insert("salones_hotel",loadCombinations.CoefsPsi(0.7,0.7,0.6))
coefs_psi_EHE.insert("aulas_escuela",loadCombinations.CoefsPsi(0.7,0.7,0.6))
coefs_psi_EHE.insert("pasillos_escaleras_escuela",loadCombinations.CoefsPsi(0.7,0.7,0.6))





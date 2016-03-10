# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#Coeficientes de ponderación para acciones permanentes.
gammaf_permanentes_EAE= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante.
gammaf_permanentes_nc_EAE= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.5,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones variables.
gammaf_variables_EAE= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Coeficientes de ponderación para acciones sísmicas.
gammaf_sismicas_EAE= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1,1,1),loadCombinations.GammaFELS(0,0))
#Coeficientes de ponderación para acciones accidentales.
gammaf_accidentales_EAE= loadCombinations.GammaF(loadCombinations.GammaFELU(0,0,1,1),loadCombinations.GammaFELS(0,0))

coefs_psi_EAE= loadCombinations.PsiCoeffsDict()

coefs_psi_EAE.insert("zonas_residenciales",loadCombinations.PsiCoeffs(0.7,0.5,0.3))
coefs_psi_EAE.insert("zonas_oficinas",loadCombinations.PsiCoeffs(0.7,0.5,0.3))
coefs_psi_EAE.insert("zonas_reunion",loadCombinations.PsiCoeffs(0.7,0.7,0.6))
coefs_psi_EAE.insert("zonas_comerciales",loadCombinations.PsiCoeffs(0.7,0.7,0.6))
coefs_psi_EAE.insert("zonas_almacen",loadCombinations.PsiCoeffs(1.0,0.9,0.8))
coefs_psi_EAE.insert("zonas_trafico_veh_ligeros",loadCombinations.PsiCoeffs(0.7,0.7,0.6))
coefs_psi_EAE.insert("zonas_trafico_veh_pesados",loadCombinations.PsiCoeffs(0.7,0.5,0.3))
coefs_psi_EAE.insert("cubiertas_inaccesibles",loadCombinations.PsiCoeffs(0.0,0.0,0.0))





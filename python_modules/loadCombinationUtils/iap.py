# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#Coeficientes de ponderación para acciones permanentes.
gammaf_permanentes_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P1 (armaduras postesas).
gammaf_permanentes_nc_Pret1Post_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1,1,1),loadCombinations.GammaFELS(0.9,1.1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P1 (armaduras pretesas).
gammaf_permanentes_nc_Pret1Pret_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1,1,1),loadCombinations.GammaFELS(0.95,1.05))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P2.
gammaf_permanentes_nc_Pret2_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a efectos reológicos (retracción y fluencia).
gammaf_permanentes_nc_Reol_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a acciones provocadas por el balasto.
gammaf_permanentes_nc_CMBalasto_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.35,0,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a acciones provocadas por empujes o movimientos del terreno.
gammaf_permanentes_nc_Terr_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.5,0,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a otras presolicitaciones distintas del pretensado.
gammaf_permanentes_nc_OtrasPresol_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(0.95,1.05,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones variables.
gammaf_variables_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Coeficientes de ponderación para acciones accidentales.
gammaf_accidentales_IAP= loadCombinations.GammaF(loadCombinations.GammaFELU(0,0,1,1),loadCombinations.GammaFELS(0,0))

coefs_psi_IAP= loadCombinations.DictCoefsPsi()

coefs_psi_IAP.insert("permanente",loadCombinations.CoefsPsi(1,1,1))
coefs_psi_IAP.insert("nieve",loadCombinations.CoefsPsi(0.6,0.2,0.0))
coefs_psi_IAP.insert("viento",loadCombinations.CoefsPsi(0.6,0.5,0.0))
coefs_psi_IAP.insert("term",loadCombinations.CoefsPsi(0.6,0.5,0.0))
coefs_psi_IAP.insert("sismo",loadCombinations.CoefsPsi(0,0,0))
coefs_psi_IAP.insert("arranque_frenado",loadCombinations.CoefsPsi(0.6,0.2,0))
coefs_psi_IAP.insert("por_defecto",loadCombinations.CoefsPsi(0.7,0.7,0.6))

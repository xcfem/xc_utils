# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#Coef. FELU("favorable","desfavorable","favorable accidental","desfavorable accidental")
#Coeficientes de ponderación para acciones permanentes de valor constante (G)
#(válido para peso propio y carga muerta)
gammaf_permanentes_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))

#Coef. de ponderación para acciones permanentes de valor no constante (G*)
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P1 (armaduras postesas).
gammaf_permanentes_nc_Pret1Post_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1,1,1),loadCombinations.GammaFELS(0.9,1.1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P1 (armaduras pretesas).
gammaf_permanentes_nc_Pret1Pret_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1,1,1),loadCombinations.GammaFELS(0.95,1.05))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas al pretensado P2.
gammaf_permanentes_nc_Pret2_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a otras presolicitaciones distintas del pretensado.
gammaf_permanentes_nc_OtrasPresol_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1.00,1.00,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a efectos reológicos (retracción y fluencia).
gammaf_permanentes_nc_Reol_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a acciones provocadas por empujes o movimientos del terreno.
gammaf_permanentes_nc_Terr_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.5,0,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a asientos en cálculo elástico
gammaf_permanentes_nc_AsientElast_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.2,0,1),loadCombinations.GammaFELS(0,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a asientos en cálculo elasto-plástico
gammaf_permanentes_nc_AsientPlast_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,0,1),loadCombinations.GammaFELS(0,1))
#Coeficientes de ponderación para acciones permanentes de valor no constante debidas a rozamiento de apoyos deslizantes
gammaf_permanentes_nc_RozApoyos_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(1,1.35,1,1),loadCombinations.GammaFELS(1,1))


#Coeficientes de ponderación para acciones variables (Q).
#Sobrecarga de  uso
gammaf_variables_SCuso_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.35,0,1),loadCombinations.GammaFELS(0,1))
#Sobrecarga de uso en terraplenes
gammaf_variables_SCusoTerrapl_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Acciones climáticas
gammaf_variables_climatica_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Empuje hidrostático
gammaf_variables_empHidrost_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Empuje hidrodinámico
gammaf_variables_empHidrodin_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
#Sobrecargas de construcción
gammaf_variables_SCconstruccion_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.35,0,1),loadCombinations.GammaFELS(0,1))


#Coeficientes de ponderación para acciones accidentales.
gammaf_accidentales_IAP11= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1,1,1),loadCombinations.GammaFELS(0,0))

#Factores de simultaneidad (tabla 6.1-a)
coefs_psi_IAP11= loadCombinations.PsiCoeffsDict()
# SC uso
#cargas verticales
coefs_psi_IAP11.insert("permanente",loadCombinations.PsiCoeffs(1,1,1))
coefs_psi_IAP11.insert("vehículos_pesados",loadCombinations.PsiCoeffs(0.75,0.75,0))
coefs_psi_IAP11.insert("sobrecarga_uniforme",loadCombinations.PsiCoeffs(0.4,0.4,0))
coefs_psi_IAP11.insert("carga_en_aceras",loadCombinations.PsiCoeffs(0.4,0.4,0))
#
coefs_psi_IAP11.insert("f_horizontal",loadCombinations.PsiCoeffs(0,0,0))
coefs_psi_IAP11.insert("peatones",loadCombinations.PsiCoeffs(0,0,0))
coefs_psi_IAP11.insert("aglomeraciones",loadCombinations.PsiCoeffs(0,0,0))
coefs_psi_IAP11.insert("SCuso_pasarelas",loadCombinations.PsiCoeffs(0.4,0.4,0))
#Viento
coefs_psi_IAP11.insert("viento_sit_persistente",loadCombinations.PsiCoeffs(0.6,0.2,0.0))
coefs_psi_IAP11.insert("viento_sit_construccion",loadCombinations.PsiCoeffs(0.8,0.0,0.0))
coefs_psi_IAP11.insert("viento_pasarelas",loadCombinations.PsiCoeffs(0.3,0.2,0.0))
# Acción térmica
coefs_psi_IAP11.insert("termica",loadCombinations.PsiCoeffs(0.6,0.6,0.5))
# Nieve
coefs_psi_IAP11.insert("nieve_construccion",loadCombinations.PsiCoeffs(0.8,0.0,0.0))
#Acción del agua
coefs_psi_IAP11.insert("emp_hidrost",loadCombinations.PsiCoeffs(1.0,1.0,1.0))
coefs_psi_IAP11.insert("emp_hidrodin",loadCombinations.PsiCoeffs(1.0,1.0,1.0))
#Sobrecargas de construcción
coefs_psi_IAP11.insert("sc_construc",loadCombinations.PsiCoeffs(1.0,0.0,1.0))

coefs_psi_IAP11.insert("por_defecto",loadCombinations.PsiCoeffs(0.7,0.7,0.6))

# Está apañado para un caso concreto . NECESITA REVISIÓN EN EL CASO GENERAL
controlCombGenerator= loadCombinations.LoadCombGenerator()
actionWeighting= controlCombGenerator.defPonderacion("IAP11",coefs_psi_IAP11)
#No need to define a new family, we change the default gamma_f values for the 'default' family.
actionWeighting.permanentActions['default'].gammaF= gammaf_permanentes_IAP11 #Partial safety factors for permanent actions.

actionWeighting.ncPermanentActions.newActionsFamily('nc_Terr', gammaf_permanentes_nc_Terr_IAP11) #Partial safety factors for non-constant permanent actions.
actionWeighting.variableActions.newActionsFamily('SCuso',gammaf_variables_SCuso_IAP11)
actionWeighting.variableActions.newActionsFamily('climatica',gammaf_variables_climatica_IAP11)
actionWeighting.accidentalActions.gammaF= gammaf_accidentales_IAP11
#actionWeighting.seismicActions.gammaF= gammaf_sismicas_EHE_ctr_intenso

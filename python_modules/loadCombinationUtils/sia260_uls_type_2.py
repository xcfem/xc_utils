# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#SIA 260 Tableau 1 (chiffre 4.4.3)
gammaf_permanentes= loadCombinations.GammaF(loadCombinations.GammaFELU(0.8,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Poussée des terres.
gammaf_terres= loadCombinations.GammaF(loadCombinations.GammaFELU(0.7,1.35,1,1),loadCombinations.GammaFELS(1,1))
#Coeficientes de ponderación para acciones variables
gammaf_variables= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.5,0,1),loadCombinations.GammaFELS(0,1))
gammaf_trafic_ferroviaire= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.45,0,1),loadCombinations.GammaFELS(0,1))
gammaf_trafic_ferroviaire_model_3= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1.20,0,1),loadCombinations.GammaFELS(0,1))
#Coeficientes de ponderación para acciones sísmicas
gammaf_sismicas= loadCombinations.GammaF(loadCombinations.GammaFELU(0,1,1,1),loadCombinations.GammaFELS(0,0))
#Coeficientes de ponderación para acciones accidentales
gammaf_accidentales= loadCombinations.GammaF(loadCombinations.GammaFELU(0,0,1,1),loadCombinations.GammaFELS(0,0))


coefs_psi_SIA260_ponts_ferroviaires_voie_normale= loadCombinations.DictCoefsPsi()

coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("permanente",loadCombinations.CoefsPsi(1,1,1))
coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("load_model_1",loadCombinations.CoefsPsi(1.0,1.0,0.0))
coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("load_model_2",loadCombinations.CoefsPsi(1.0,1.0,0.0))
coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("load_model_3",loadCombinations.CoefsPsi(0.0,1.0,0.0))
coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("vent",loadCombinations.CoefsPsi(0.8,0.5,0.0))
coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("force_aerodynamiques_train",loadCombinations.CoefsPsi(1.0,0.5,0.0))
coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("temperature",loadCombinations.CoefsPsi(0.6,0.6,0.5))
coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("poussee_terres",loadCombinations.CoefsPsi(0.7,0.7,0.7))
coefs_psi_SIA260_ponts_ferroviaires_voie_normale.insert("pression_hydraulique",loadCombinations.CoefsPsi(0.7,0.7,0.7))

combGeneratorPontFerroviaireVoieNormale= loadCombinations.LoadCombGenerator()
pond= combGeneratorPontFerroviaireVoieNormale.defPonderacion("SIA260ULSType2",coefs_psi_SIA260_ponts_ferroviaires_voie_normale)
pond.permanentActions.gammaF= gammaf_permanentes
pond.variableActions.gammaF= gammaf_variables
pond.accidentalActions.gammaF= gammaf_accidentales
pond.seismicActions.gammaF= gammaf_sismicas

coefs_psi_SIA260_ponts_routes= loadCombinations.DictCoefsPsi()

coefs_psi_SIA260_ponts_routes.insert("permanente",loadCombinations.CoefsPsi(1,1,1))
coefs_psi_SIA260_ponts_routes.insert("load_model_1",loadCombinations.CoefsPsi(0.75,0.75,0.0))
coefs_psi_SIA260_ponts_routes.insert("load_model_3",loadCombinations.CoefsPsi(0.0,0.0,0.0))
coefs_psi_SIA260_ponts_routes.insert("choc",loadCombinations.CoefsPsi(0.0,0.0,0.0))
coefs_psi_SIA260_ponts_routes.insert("neige",loadCombinations.CoefsPsi(0.6,0.2,0.0))
coefs_psi_SIA260_ponts_routes.insert("vent",loadCombinations.CoefsPsi(0.6,0.2,0.0))
coefs_psi_SIA260_ponts_routes.insert("temperature",loadCombinations.CoefsPsi(0.6,0.6,0.5))
coefs_psi_SIA260_ponts_routes.insert("poussee_terres",loadCombinations.CoefsPsi(0.7,0.7,0.7))
coefs_psi_SIA260_ponts_routes.insert("pression_hydraulique",loadCombinations.CoefsPsi(0.7,0.7,0.7))

combGeneratorPontRoutier= loadCombinations.LoadCombGenerator()
pond= combGeneratorPontRoutier.defPonderacion("SIA260ULSType2",coefs_psi_SIA260_ponts_routes)
pond.permanentActions.gammaF= gammaf_permanentes
pond.variableActions.gammaF= gammaf_variables
pond.accidentalActions.gammaF= gammaf_accidentales
pond.seismicActions.gammaF= gammaf_sismicas



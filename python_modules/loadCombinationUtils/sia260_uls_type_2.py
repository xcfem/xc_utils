# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

#SIA 260 Tableau 1 (chiffre 4.4.3)
partial_safety_factors_permanentes= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0.8,1.35,1,1),loadCombinations.PartialSafetyFactorsELS(1,1))
#Poussée des terres.
partial_safety_factors_terres= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0.7,1.35,1,1),loadCombinations.PartialSafetyFactorsELS(1,1))
#Coeficientes de ponderación para acciones variables
partial_safety_factors_variables= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.5,0,1),loadCombinations.PartialSafetyFactorsELS(0,1))
partial_safety_factors_trafic_ferroviaire= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.45,0,1),loadCombinations.PartialSafetyFactorsELS(0,1))
partial_safety_factors_trafic_ferroviaire_model_3= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.20,0,1),loadCombinations.PartialSafetyFactorsELS(0,1))
#Coeficientes de ponderación para acciones sísmicas
partial_safety_factors_sismicas= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1,1,1),loadCombinations.PartialSafetyFactorsELS(0,0))
#Coeficientes de ponderación para acciones accidentales
partial_safety_factors_accidentales= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,0,1,1),loadCombinations.PartialSafetyFactorsELS(0,0))


combination_factors_SIA260_ponts_ferroviaires_voie_normale= loadCombinations.CombinationFactorsDict()

combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("permanente",loadCombinations.CombinationFactors(1,1,1))
combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("load_model_1",loadCombinations.CombinationFactors(1.0,1.0,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("load_model_2",loadCombinations.CombinationFactors(1.0,1.0,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("load_model_3",loadCombinations.CombinationFactors(0.0,1.0,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("vent",loadCombinations.CombinationFactors(0.8,0.5,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("force_aerodynamiques_train",loadCombinations.CombinationFactors(1.0,0.5,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("temperature",loadCombinations.CombinationFactors(0.6,0.6,0.5))
combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("poussee_terres",loadCombinations.CombinationFactors(0.7,0.7,0.7))
combination_factors_SIA260_ponts_ferroviaires_voie_normale.insert("pression_hydraulique",loadCombinations.CombinationFactors(0.7,0.7,0.7))

combGeneratorPontFerroviaireVoieNormale= loadCombinations.LoadCombGenerator()
pond= combGeneratorPontFerroviaireVoieNormale.defPonderacion("SIA260ULSType2",combination_factors_SIA260_ponts_ferroviaires_voie_normale)
pond.permanentActions.partial_safety_factors= partial_safety_factors_permanentes
pond.variableActions.partial_safety_factors= partial_safety_factors_variables
pond.accidentalActions.partial_safety_factors= partial_safety_factors_accidentales
pond.seismicActions.partial_safety_factors= partial_safety_factors_sismicas

combination_factors_SIA260_ponts_ferroviaires_voie_etroite= loadCombinations.CombinationFactorsDict()

combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("permanente",loadCombinations.CombinationFactors(1,1,1))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("load_model_4",loadCombinations.CombinationFactors(1.0,1.0,0.3))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("load_model_5",loadCombinations.CombinationFactors(1.0,1.0,0.3))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("load_model_6",loadCombinations.CombinationFactors(0.0,1.0,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("load_model_7",loadCombinations.CombinationFactors(0.0,1.0,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("load_model_8",loadCombinations.CombinationFactors(0.0,1.0,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("choc",loadCombinations.CombinationFactors(0.0,0.0,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("vent",loadCombinations.CombinationFactors(0.8,0.5,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("force_aerodynamiques_train",loadCombinations.CombinationFactors(1.0,0.5,0.0))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("temperature",loadCombinations.CombinationFactors(0.6,0.6,0.5))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("poussee_terres",loadCombinations.CombinationFactors(0.7,0.7,0.7))
combination_factors_SIA260_ponts_ferroviaires_voie_etroite.insert("pression_hydraulique",loadCombinations.CombinationFactors(0.7,0.7,0.7))

combGeneratorPontFerroviaireVoieEtroite= loadCombinations.LoadCombGenerator()
pond= combGeneratorPontFerroviaireVoieEtroite.defPonderacion("SIA260ULSType2",combination_factors_SIA260_ponts_ferroviaires_voie_etroite)
pond.permanentActions.partial_safety_factors= partial_safety_factors_permanentes
pond.variableActions.partial_safety_factors= partial_safety_factors_variables
pond.accidentalActions.partial_safety_factors= partial_safety_factors_accidentales
pond.seismicActions.partial_safety_factors= partial_safety_factors_sismicas

combination_factors_SIA260_ponts_routes= loadCombinations.CombinationFactorsDict()

combination_factors_SIA260_ponts_routes.insert("permanente",loadCombinations.CombinationFactors(1,1,1))
combination_factors_SIA260_ponts_routes.insert("load_model_1",loadCombinations.CombinationFactors(0.75,0.75,0.0))
combination_factors_SIA260_ponts_routes.insert("load_model_3",loadCombinations.CombinationFactors(0.0,0.0,0.0))
combination_factors_SIA260_ponts_routes.insert("choc",loadCombinations.CombinationFactors(0.0,0.0,0.0))
combination_factors_SIA260_ponts_routes.insert("neige",loadCombinations.CombinationFactors(0.6,0.2,0.0))
combination_factors_SIA260_ponts_routes.insert("vent",loadCombinations.CombinationFactors(0.6,0.2,0.0))
combination_factors_SIA260_ponts_routes.insert("temperature",loadCombinations.CombinationFactors(0.6,0.6,0.5))
combination_factors_SIA260_ponts_routes.insert("poussee_terres",loadCombinations.CombinationFactors(0.7,0.7,0.7))
combination_factors_SIA260_ponts_routes.insert("pression_hydraulique",loadCombinations.CombinationFactors(0.7,0.7,0.7))

combGeneratorPontRoutier= loadCombinations.LoadCombGenerator()
pond= combGeneratorPontRoutier.defPonderacion("SIA260ULSType2",combination_factors_SIA260_ponts_routes)
pond.permanentActions.partial_safety_factors= partial_safety_factors_permanentes
pond.variableActions.partial_safety_factors= partial_safety_factors_variables
pond.accidentalActions.partial_safety_factors= partial_safety_factors_accidentales
pond.seismicActions.partial_safety_factors= partial_safety_factors_sismicas



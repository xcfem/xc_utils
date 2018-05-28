# -*- coding: utf-8 -*-

import xc_base
import loadCombinations

factors= loadCombinations.Factors()
partial_safety_factors= factors.getPartialSafetyFactors()

#SIA 260 Tableau 1 (chiffre 4.4.3)
partial_safety_factors["permanentes"]= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0.8,1.35,1,1),loadCombinations.PartialSafetyFactorsELS(1,1))
#Poussée des terres.
partial_safety_factors["terres"]= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0.7,1.35,1,1),loadCombinations.PartialSafetyFactorsELS(1,1))
#Coeficientes de ponderación para acciones variables
partial_safety_factors["variables"]= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.5,0,1),loadCombinations.PartialSafetyFactorsELS(0,1))
partial_safety_factors["trafic_ferroviaire"]= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.45,0,1),loadCombinations.PartialSafetyFactorsELS(0,1))
partial_safety_factors["trafic_ferroviaire_model_3"]= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1.20,0,1),loadCombinations.PartialSafetyFactorsELS(0,1))
#Coeficientes de ponderación para acciones sísmicas
partial_safety_factors["sismicas"]= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,1,1,1),loadCombinations.PartialSafetyFactorsELS(0,0))
#Coeficientes de ponderación para acciones accidentales
partial_safety_factors["accidentales"]= loadCombinations.PartialSafetyFactors(loadCombinations.ULSPartialSafetyFactors(0,0,1,1),loadCombinations.PartialSafetyFactorsELS(0,0))


combination_factors= factors.getCombinationFactors()

combination_factors.insert("permanente",loadCombinations.CombinationFactors(1,1,1))
combination_factors.insert("load_model_1",loadCombinations.CombinationFactors(1.0,1.0,0.0))
combination_factors.insert("load_model_2",loadCombinations.CombinationFactors(1.0,1.0,0.0))
combination_factors.insert("load_model_3",loadCombinations.CombinationFactors(0.0,1.0,0.0))
combination_factors.insert("vent",loadCombinations.CombinationFactors(0.8,0.5,0.0))
combination_factors.insert("force_aerodynamiques_train",loadCombinations.CombinationFactors(1.0,0.5,0.0))
combination_factors.insert("temperature",loadCombinations.CombinationFactors(0.6,0.6,0.5))
combination_factors.insert("poussee_terres",loadCombinations.CombinationFactors(0.7,0.7,0.7))
combination_factors.insert("pression_hydraulique",loadCombinations.CombinationFactors(0.7,0.7,0.7))


combination_factors.insert("voie_etroite_load_model_4",loadCombinations.CombinationFactors(1.0,1.0,0.3))
combination_factors.insert("voie_etroite_load_model_5",loadCombinations.CombinationFactors(1.0,1.0,0.3))
combination_factors.insert("voie_etroite_load_model_6",loadCombinations.CombinationFactors(0.0,1.0,0.0))
combination_factors.insert("voie_etroite_load_model_7",loadCombinations.CombinationFactors(0.0,1.0,0.0))
combination_factors.insert("voie_etroite_load_model_8",loadCombinations.CombinationFactors(0.0,1.0,0.0))
combination_factors.insert("voie_etroite_choc",loadCombinations.CombinationFactors(0.0,0.0,0.0))
combination_factors.insert("voie_etroite_vent",loadCombinations.CombinationFactors(0.8,0.5,0.0))
combination_factors.insert("voie_etroite_force_aerodynamiques_train",loadCombinations.CombinationFactors(1.0,0.5,0.0))
combination_factors.insert("voie_etroite_temperature",loadCombinations.CombinationFactors(0.6,0.6,0.5))
combination_factors.insert("voie_etroite_poussee_terres",loadCombinations.CombinationFactors(0.7,0.7,0.7))
combination_factors.insert("voie_etroite_pression_hydraulique",loadCombinations.CombinationFactors(0.7,0.7,0.7))

combination_factors.insert("ponts_routes_load_model_1",loadCombinations.CombinationFactors(0.75,0.75,0.0))
combination_factors.insert("ponts_routes_load_model_3",loadCombinations.CombinationFactors(0.0,0.0,0.0))
combination_factors.insert("ponts_routes_choc",loadCombinations.CombinationFactors(0.0,0.0,0.0))
combination_factors.insert("ponts_routes_neige",loadCombinations.CombinationFactors(0.6,0.2,0.0))
combination_factors.insert("ponts_routes_vent",loadCombinations.CombinationFactors(0.6,0.2,0.0))
combination_factors.insert("ponts_routes_temperature",loadCombinations.CombinationFactors(0.6,0.6,0.5))
combination_factors.insert("ponts_routes_poussee_terres",loadCombinations.CombinationFactors(0.7,0.7,0.7))
combination_factors.insert("ponts_routes_pression_hydraulique",loadCombinations.CombinationFactors(0.7,0.7,0.7))

combGeneratorPontFerroviaireVoieNormale= loadCombinations.LoadCombGenerator()
actionsAndFactors= combGeneratorPontFerroviaireVoieNormale.actionWeighting.create("SIA260ULSType2",factors)

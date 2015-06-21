# -*- coding: utf-8 -*-
'''Coeficientes de ponderación según EHE para acciones variables y control intenso.'''
\variables
  {
    \gammaf
      {
        \gammaf_elu
           {
             # En situaciones persitentes o transitorias:
             \favorable{0} \desfavorable{1.5}
             # En situaciones accidentales:
             \favorable_accidental{0} \desfavorable_accidental{1}
           }
        \gammaf_els
           { \favorable{0} \desfavorable{1} }
      }
  }

# -*- coding: utf-8 -*-
'''Coeficientes de ponderación según EAE para acciones
accidentales.'''
\accidentales
  {
    \gammaf
      {
        \gammaf_elu
           {
             # En situaciones persitentes o transitorias:
             \favorable{0} \desfavorable{0}
             # En situaciones accidentales:
             \favorable_accidental{1} \desfavorable_accidental{1}
           }
        \gammaf_els
           { \favorable{0} \desfavorable{0} }
      }
  }

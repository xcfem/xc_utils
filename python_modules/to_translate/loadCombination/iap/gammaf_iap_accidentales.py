# -*- coding: utf-8 -*-
'''Coeficientes de ponderación según IAP para acciones
accidentales.'''
\accidentales
  {
    \gammaf
      {
        # ver cuadro 4.1 IAPF
        \gammaf_elu
           {
             \favorable{0} \desfavorable{0} # En situaciones persitentes o transitorias:
             \favorable_accidental{1} \desfavorable_accidental{1} # En situaciones accidentales:
           }
        # ver cuadro 4.2 IAPF
        \gammaf_els{ \favorable{0} \desfavorable{0} }
      }
  }

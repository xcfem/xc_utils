# -*- coding: utf-8 -*-
'''Coeficientes de ponderación según IAPF para acciones
variables y control intenso.'''
\variables
  {
    \gammaf
      {
        # ver cuadro 4.1 IAPF
        \gammaf_elu
           {
             \favorable{0} \desfavorable{1.5} # En situaciones persitentes o transitorias.
             \favorable_accidental{0} \desfavorable_accidental{1} # En situaciones accidentales.
           }
        # ver cuadro 4.2 IAPF
        \gammaf_els{ \favorable{0} \desfavorable{1} }
      }
  }

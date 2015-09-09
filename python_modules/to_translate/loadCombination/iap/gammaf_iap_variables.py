# -*- coding: utf-8 -*-
''Coeficientes de ponderación según IAP para acciones
variables y control intenso.'''
\variables
  {
    \gammaf
      {
        # ver cuadro 6.2-b IAP 2011
        \gammaf_elu
           {
             \favorable{0} \desfavorable{1.5} # En situaciones persitentes o transitorias.
             \favorable_accidental{0} \desfavorable_accidental{1} # En situaciones accidentales.
           }
        # ver cuadro 6.2-b IAP 2011
        \gammaf_els{ \favorable{0} \desfavorable{1} }
      }
  }

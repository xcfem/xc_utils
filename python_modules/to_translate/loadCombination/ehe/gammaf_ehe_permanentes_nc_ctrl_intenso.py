# -*- coding: utf-8 -*-
'''Coeficientes de ponderación según EHE para acciones
permanentes de valor no constante con control de ejecución normal.'''
\permanentes_nc
  {
    \defFamiliaAcciones["PNC"]{}
    \PNC
      {
        \gammaf
          {
            \gammaf_elu
               {
                 \favorable{1} \desfavorable{1.5}# En situaciones persitentes o transitorias. 
                 \favorable_accidental{1} \desfavorable_accidental{1} # En situaciones accidentales.
               }
            \gammaf_els
               { \favorable{1} \desfavorable{1} }
          }
      }
  }

# -*- coding: utf-8 -*-
# Coeficientes de ponderación según IAP para acciones permanentes.
\permanentes
  {
    \gammaf
      {
        # ver cuadro  6.2-b IAP 2011
        \gammaf_elu
          {
           \favorable{1} \desfavorable{1.35}# En situaciones persitentes o transitorias:
           \favorable_accidental{1} \desfavorable_accidental{1}# En situaciones accidentales:
          }
        # ver cuadro  6.2-b IAP 2011
        \gammaf_els{ \favorable{1} \desfavorable{1} }
      }
  }

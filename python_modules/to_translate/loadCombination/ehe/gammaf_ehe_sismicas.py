# -*- coding: utf-8 -*-
# Coeficientes de ponderación según EHE para acciones sísmicas.
\sismicas
  {
    \gammaf
      {
        \gammaf_elu
          {
            # En situaciones persitentes o transitorias:
            \favorable{0} \desfavorable{1.0}
            # En situaciones accidentales:
            \favorable_accidental{1} \desfavorable_accidental{1}
          }
        \gammaf_els
           { \favorable{0} \desfavorable{0} }
      }
  }

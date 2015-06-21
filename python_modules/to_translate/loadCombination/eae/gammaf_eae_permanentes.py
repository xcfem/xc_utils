# -*- coding: utf-8 -*-
# Coeficientes de ponderación según EAE para acciones permanentes.
\permanentes
  {
    \gammaf
      {
        \gammaf_elu
           {
             # En situaciones persitentes o transitorias:
             \favorable{1} \desfavorable{1.35} # Revisar
             # En situaciones accidentales:
             \favorable_accidental{1} \desfavorable_accidental{1} # Revisar
           }
        \gammaf_els
           { \favorable{1} \desfavorable{1} }
      }
  }

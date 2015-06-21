# -*- coding: utf-8 -*-
'''Coeficientes de ponderación según IAPF para acciones
permanentes de valor no constante .'''

\permanentes_nc
  {
    \defFamiliaAcciones["Pret1Post"]{}
    \Pret1Post
      {
        \c{Coeficientes de ponderación para acciones permanentes
           de valor no constante debidas al pretensado P1
           (armaduras postesas).}
        \gammaf
          {
            # ver cuadro 4.1 IAPF
            \gammaf_elu
               {
                 \favorable{1} \desfavorable{1} # En situaciones persitentes o transitorias.         
                 \favorable_accidental{1} \desfavorable_accidental{1} # En situaciones accidentales.
               }
            # ver cuadro 4.2 IAPF
            \gammaf_els{ \favorable{0.9} \desfavorable{1.1} }
          }
      }
    \defFamiliaAcciones["Pret1Pret"]{}
    \Pret1Pret
      {
        \c{Coeficientes de ponderación para acciones permanentes
           de valor no constante debidas al pretensado P1
           (armaduras pretesas).}
        \gammaf
          {
            # ver cuadro 4.1 IAPF
            \gammaf_elu
               {
                 \favorable{1} \desfavorable{1} # En situaciones persitentes o transitorias.         
                 \favorable_accidental{1} \desfavorable_accidental{1} # En situaciones accidentales.
               }
            # ver cuadro 4.2 IAPF
            \gammaf_els{ \favorable{0.95} \desfavorable{1.05} }
          }
      }
    \defFamiliaAcciones["Pret2"]{}
    \Pret2
      {
        \c{Coeficientes de ponderación para acciones permanentes
           de valor no constante debidas al pretensado P2.}
        \gammaf
          {
            # ver cuadro 4.1 IAPF
            \gammaf_elu
               {
                 \favorable{1} \desfavorable{1.35} # En situaciones persitentes o transitorias.         
                 \favorable_accidental{1} \desfavorable_accidental{1} # En situaciones accidentales.
               }
            # ver cuadro 4.2 IAPF
            \gammaf_els{ \favorable{1} \desfavorable{1} }
          }
      }
    \defFamiliaAcciones["Reol"]{}
    \Reol
      {
        \c{Coeficientes de ponderación para acciones permanentes
           de valor no constante debidas a efectos reológicos (retracción y fluencia).}
        \gammaf
          {
            # ver cuadro 4.1 IAPF
            \gammaf_elu
               {
                 \favorable{1} \desfavorable{1.35} # En situaciones persitentes o transitorias.         
                 \favorable_accidental{1} \desfavorable_accidental{1} # En situaciones accidentales.
               }
            # ver cuadro 4.2 IAPF
            \gammaf_els{ \favorable{1} \desfavorable{1} }
          }
      }
    \defFamiliaAcciones["CMBalasto"]{}
    \CMBalasto
      {
        \c{Coeficientes de ponderación para acciones permanentes
           de valor no constante debidas a acciones provocadas por el balasto.}
        \gammaf
          {
            # ver cuadro 4.1 IAPF
            \gammaf_elu
               {
                 \favorable{0} \desfavorable{1.35} # En situaciones persitentes o transitorias.      
                 \favorable_accidental{0} \desfavorable_accidental{1} # En situaciones accidentales.
               }
            # ver cuadro 4.2 IAPF
            \gammaf_els{ \favorable{1} \desfavorable{1} }
          }
      }
    \defFamiliaAcciones["Terr"]{}
    \Terr
      {
        \c{Coeficientes de ponderación para acciones permanentes
           de valor no constante debidas a acciones provocadas por empujes o movimientos del terreno.}
        \gammaf
          {
            # ver cuadro 4.1 IAPF
            \gammaf_elu
               {
                 \favorable{1} \desfavorable{1.5} # En situaciones persitentes o transitorias.      
                 \favorable_accidental{0} \desfavorable_accidental{1} # En situaciones accidentales.
               }
            # ver cuadro 4.2 IAPF
            \gammaf_els{ \favorable{1} \desfavorable{1} }
          }
      }
    \defFamiliaAcciones["OtrasPresol"]{}
    \OtrasPresol
      {
        \c{Coeficientes de ponderación para acciones permanentes
           de valor no constante debidas a otras presolicitaciones
           distintas del pretensado.}
        \gammaf
          {
            # ver cuadro 4.1 IAPF
            \gammaf_elu
               {
                 \favorable{0.95} \desfavorable{1.05} # En situaciones persitentes o transitorias.      
                 \favorable_accidental{1} \desfavorable_accidental{1} # En situaciones accidentales.
               }
            # ver cuadro 4.2 IAPF
            \gammaf_els{ \favorable{1} \desfavorable{1} }
          }
      }
   }

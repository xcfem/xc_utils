# -*- coding: utf-8 -*-
# Elaboración propia a partir de los propuestos por EHE
\coefs_psi
  {
    \defCoefs["iapf_permanente"]{\psi_0{1} \psi_1{1} \psi_2{1}}
    \defCoefs["iapf_nieve"]{\psi_0{0.6} \psi_1{0.2} \psi_2{0.0}}
    \defCoefs["iapf_viento"]{\psi_0{0.6} \psi_1{0.5} \psi_2{0.0}}
    \defCoefs["iapf_term"]{\psi_0{0.6} \psi_1{0.5} \psi_2{0.0}}
    \defCoefs["iapf_sismo"]{\psi_0{0} \psi_1{0} \psi_2{0}}
    \defCoefs["iapf_arranque_frenado"]{\psi_0{0.6} \psi_1{0.2} \psi_2{0}}
    \defCoefs["iapf_por_defecto"]{\psi_0{0.7} \psi_1{0.7} \psi_2{0.6}}
  }

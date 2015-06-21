# -*- coding: utf-8 -*-
\pond_acciones
  {
    \defPonderacion["IAPF"]{}
    \IAPF
      {
        execfile(""comb_acciones/iapf/gammaf_iapf_permanentes.cmbm"")
        execfile(""comb_acciones/iapf/gammaf_iapf_permanentes_nc.cmbm"")
        execfile(""comb_acciones/iapf/gammaf_iapf_variables.cmbm"")
        execfile(""comb_acciones/iapf/gammaf_iapf_accidentales.cmbm"")
      }
  }

# -*- coding: utf-8 -*-
\pond_acciones
  {
    \defPonderacion["EAE"]{}
    \EAE
      {
        execfile(""comb_acciones/eae/gammaf_eae_permanentes.cmbm"")
        execfile(""comb_acciones/eae/gammaf_eae_permanentes_nc.cmbm"")
        execfile(""comb_acciones/eae/gammaf_eae_variables.cmbm"")
        execfile(""comb_acciones/eae/gammaf_eae_sismicas.cmbm"")
        execfile(""comb_acciones/eae/gammaf_eae_accidentales.cmbm"")
        execfile(""comb_acciones/eae/coefs_psi_eae.cmbm"")
      }
  }

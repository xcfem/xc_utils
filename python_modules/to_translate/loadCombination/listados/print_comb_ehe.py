# -*- coding: utf-8 -*-
\combinaciones
  {
    \comb_elu_persistentes
      {
        print "Obtenidas: ",num_combinaciones," combinaciones en situaciones persistentes o transitorias.\n"
        arch_salida_ltx.open("./examples/output/comb_ehe_elu_pt.tex","w")
        execfile("print_combinaciones.acc")
        arch_salida_ltx.close()
      }
    \comb_elu_accidentales
      {
        print "Obtenidas: ",num_combinaciones," combinaciones en situaciones accidentales.\n"
        arch_salida_ltx.open("./examples/output/comb_ehe_elu_acc.tex","w")
        execfile("print_combinaciones.acc")
        arch_salida_ltx.close()
      }
    \comb_elu_sismicas
      {
        print "Obtenidas: ",num_combinaciones," combinaciones en situaciones sísmicas.\n"
        arch_salida_ltx.open("./examples/output/comb_ehe_elu_sism.tex","w")
        execfile("print_combinaciones.acc")
        arch_salida_ltx.close()
      }
    \comb_els_poco_frecuentes
      {
        print "Obtenidas: ",num_combinaciones," combinaciones en situaciones poco frecuentes.\n"
        arch_salida_ltx.open("./examples/output/comb_ehe_els_pf.tex","w")
        execfile("print_combinaciones.acc")
        arch_salida_ltx.close()
      }
    \comb_els_frecuentes
      {
        print "Obtenidas: ",num_combinaciones," combinaciones en situaciones frecuentes.\n"
        arch_salida_ltx.open("./examples/output/comb_ehe_els_f.tex","w")
        execfile("print_combinaciones.acc")
        arch_salida_ltx.close()
      }
    \comb_els_cuasi_permanentes
      {
        print "Obtenidas: ",num_combinaciones," combinaciones en situaciones cuasi permanentes.\n"
        arch_salida_ltx.open("./examples/output/comb_ehe_els_cp.tex","w")
        execfile("print_combinaciones.acc")
        arch_salida_ltx.close()
      }
  }

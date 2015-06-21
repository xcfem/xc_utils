# -*- coding: utf-8 -*-
# Combinaciones poco frecuentes
def_hip_elspf.open("./def_hip_elspf.xci","w")
calc_hip_elspf.open("./calc_hip_elspf.xci","w")
hip_elspf_tex.open("./hipotesis_elspf.tex","w")
\printCabeceraListaHipotesis("hip_elspf_tex"){}
\combinaciones
  {
    \comb_els_poco_frecuentes
      {
        \expr{conta= 1}
        \for_each
          {
            def_hip_elspf.write("\combinacion[\"",format(int(conta),"ELSPF%03u"),"\"]{ \descomp{\"",getNombre,"\"}}\n")
            calc_hip_elspf.write("\\resuelveCombEstatLin(\"",format(int(conta),"ELSPF%03u"),"\"){}","\n")
            calc_hip_elspf.write("\\trataResultsComb(\"",format(int(conta),"ELSPF%03u"),"\"){}","\n")
            hip_elspf_tex.write(format(int(conta),"ELSPF%03u")," & ",getNombre,"\\\\\n")
            \expr{conta= tonum(conta+1)}
          }
      }
  }
hip_elspf_tex.write("\\end{supertabular}\n")
hip_elspf_tex.write("\\end{center}\n")
def_hip_elspf.close()
calc_hip_elspf.close()
hip_elspf_tex.close()

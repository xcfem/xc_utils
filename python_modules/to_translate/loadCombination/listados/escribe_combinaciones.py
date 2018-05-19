# -*- coding: utf-8 -*-
def escribeCombinacionesULS(nmbArchivoDef, nmbArchivoLatex,nmbFormat):
  {
    def_hip_elu.open(nmbArchivoDef,"w")
    \combinaciones
      {
        \comb_elu_persistentes
          {
            \expr{conta= 1}
            \for_each
              {
                def_hip_elu.write("\combinacion[\"",format(int(conta),nmbFormat),"\"]{ \descomp{\"",getNombre,"\"}}\n")
                \expr{conta= tonum(conta+1)}
              }
          }
        \comb_elu_accidentales
          {
            \for_each
              {
                def_hip_elu.write("\combinacion[\"",format(int(conta),nmbFormat),"\"]{ \descomp{\"",getNombre,"\"}}\n")
                \expr{conta= tonum(conta+1)}
              }
          }
      }
    def_hip_elu.close()
    hip_elu_tex.open(nmbArchivoLatex,"w")
    \printCabeceraListaHipotesis("hip_elu_tex"){}
    \combinaciones
      {
        \comb_elu_persistentes
          {
            \expr{conta= 1}
            \for_each
              {
                hip_elu_tex.write(format(int(conta),nmbFormat)," & ",getNombre,"\\\\\n")
                \expr{conta= tonum(conta+1)}
              }
          }
        \comb_elu_accidentales
          {
            \for_each
              {
                hip_elu_tex.write(format(int(conta),nmbFormat)," & ",getNombre,"\\\\\n")
                \expr{conta= tonum(conta+1)}
              }
          }
      }
    hip_elu_tex.write("\\end{supertabular}\n")
    hip_elu_tex.write("\\end{center}\n")
    hip_elu_tex.close()
  }

def escribeCombinacionesSLSFrecuentes(nmbArchivoDef, nmbArchivoLatex,nmbFormat):
  {
    def_hip_els.open(nmbArchivoDef,"w")
    \combinaciones
      {
        \comb_els_frecuentes
          {
            \expr{conta= 1}
            \for_each
              {
                def_hip_els.write("\combinacion[\"",format(int(conta),nmbFormat),"\"]{ \descomp{\"",getNombre,"\"}}\n")
                \expr{conta= tonum(conta+1)}
              }
          }
      }
    def_hip_els.close()
    hip_els_tex.open(nmbArchivoLatex,"w")
    \printCabeceraListaHipotesis("hip_els_tex"){}
    \combinaciones
      {
        \comb_els_frecuentes
          {
            \expr{conta= 1}
            \for_each
              {
                hip_els_tex.write(format(int(conta),nmbFormat)," & ",getNombre,"\\\\\n")
                \expr{conta= tonum(conta+1)}
              }
          }
      }
    hip_els_tex.write("\\end{supertabular}\n")
    hip_els_tex.write("\\end{center}\n")
    hip_els_tex.close()
  }

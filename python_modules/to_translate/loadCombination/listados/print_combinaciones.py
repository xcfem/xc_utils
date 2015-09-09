# -*- coding: utf-8 -*-
def printComb(pathArchSalida):
  {
    arch_salida_ltx.open(pathArchSalida,"w")
    arch_salida_ltx.write("\\begin{center}\n")
    arch_salida_ltx.write("\\begin{small}\n")
    arch_salida_ltx.write("\\begin{longtable}{|c|l|}\n")
    arch_salida_ltx.write("\\hline\n")
    arch_salida_ltx.write("Combinación & Descomposición \\\\\n")
    arch_salida_ltx.write("\\hline\n")
    arch_salida_ltx.write("\\endfirsthead\n")
    arch_salida_ltx.write("\\hline\n")
    arch_salida_ltx.write("\\multicolumn{2}{|l|}{../..}\\\\\n")
    arch_salida_ltx.write("\\hline\n")
    arch_salida_ltx.write("Combinación & Descomposición \\\\\n")
    arch_salida_ltx.write("\\hline\n")
    arch_salida_ltx.write("\\endhead\n")
    arch_salida_ltx.write("\\hline\n")
    arch_salida_ltx.write("\\multicolumn{2}{|r|}{../..}\\\\\n")
    arch_salida_ltx.write("\\hline\n")
    arch_salida_ltx.write("\\endfoot\n")
    arch_salida_ltx.write("\\hline \\hline\n")
    arch_salida_ltx.write("\\endlastfoot\n")
    \expr{cont= 1}
    \for_each
      {
        arch_salida_ltx.write(cont," & ",ascii2ltx(getNombreExpandido),"\\\\\n")
        \expr{cont= tonum(cont+1)}
      }
    arch_salida_ltx.write("\\end{longtable}\n")
    arch_salida_ltx.write("\\end{small}\n")
    arch_salida_ltx.write("\\end{center}\n")
    arch_salida_ltx.close()
  }

'''Imprime las combinaciones correspondientes a estados límite últimos
 en situaciones permanentes o transitorias.'''
def printCombEluSitPersistentes(pathArchSalida):
  {
    \combinaciones{ \comb_elu_persistentes{ \printComb(pathArchSalida){} } }
  }

'''Imprime las combinaciones correspondientes a estados límite últimos
 en situaciones accidentales.'''
def printCombEluSitAccidentales(pathArchSalida):
  {
    \combinaciones{ \comb_elu_accidentales{ \printComb(pathArchSalida){} } }
  }

'''Imprime las combinaciones correspondientes a estados límite últimos
 en situaciones sismicas.'''
def printCombEluSitSismicas(pathArchSalida):
  {
    \combinaciones{ \comb_elu_sismicas{ \printComb(pathArchSalida){} } }
  }

'''Imprime las combinaciones correspondientes a estados límite de servicio
 en situaciones poco frecuentes.'''
def printCombElsSitPocoFrecuentes(pathArchSalida):
  {
    \combinaciones{ \comb_els_poco_frecuentes{ \printComb(pathArchSalida){} } }
  }

'''Imprime las combinaciones correspondientes a estados límite de servicio
 en situaciones frecuentes.'''
def printCombElsSitFrecuentes(pathArchSalida):
  {
    \combinaciones{ \comb_els_frecuentes{ \printComb(pathArchSalida){} } }
  }

#Imprime las combinaciones correspondientes a estados límite de servicio en situaciones cuasi permanentes.
def printCombElsSitCuasiPermanentes(pathArchSalida):
  {
    \combinaciones{ \comb_els_cuasi_permanentes{ \printComb(pathArchSalida){} } }
  }

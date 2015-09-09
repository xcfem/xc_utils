# -*- coding: utf-8 -*-

import xc_base
import loadCombinations
from loadCombinationUtils import ehe_ctr_intenso

dbName= "/tmp/test_accidentales.db"
tbName= "combinaciones"

lcg= loadCombinations.LoadCombGenerator()
lcg.defPonderacion("EHEIntenso",ehe_ctr_intenso.coefs_psi_EHE)
lcg.insert("EHEIntenso","accidentales",loadCombinations.Accion("A1","Hipot. 1"),"","")
lcg.insert("EHEIntenso","accidentales",loadCombinations.Accion("A2","Hipot. 2"),"","")
lcg.insert("EHEIntenso","accidentales",loadCombinations.Accion("A3","Hipot. 3"),"","")
lcg.insert("EHEIntenso","accidentales",loadCombinations.Accion("A4","Hipot. 4"),"","")
lcg.insert("EHEIntenso","accidentales",loadCombinations.Accion("A5","Hipot. 5"),"","")
lcg.insert("EHEIntenso","accidentales",loadCombinations.Accion("A6","Hipot. 6"),"","")

import os
os.system("rm -f "+dbName)

import sqlite3 as sqlite
from sqliteUtils import macros_sqlite


macros_sqlite.SQLTcreaDBase(dbName)
nmbTablaComb= "comb_elu_accidentales"

lcg.genera()
combAcc= lcg.getLoadCombinations.getULSAccidentalCombinations
cont= len(combAcc)
    
    
ratio1= abs(cont-7)/7

'''    
print "ratio1= ", ratio1
for comb in combAcc:
  print comb.nombre
'''   
 
fname= os.path.basename(__file__)
if (abs(ratio1)<1e-15):
  print "test ",fname,": ok."
else:
  print "test ",fname,": ERROR."

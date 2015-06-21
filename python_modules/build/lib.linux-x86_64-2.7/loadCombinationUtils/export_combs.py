# -*- coding: utf-8 -*-

import math
import loadCombinations

def writeLoadCombinations(outputFileName, prefix, loadCombs):
  f= open(outputFileName,'w')
  f.write("combs= loadLoader.getLoadCombinations\n")
  conta= 1
  sz= len(loadCombs)
  szLength= int(math.log(sz,10))+1
  for comb in loadCombs:
    cod= prefix+str(conta).zfill(szLength)
    output= 'comb= combs.newLoadCombination('
    output+= '"'+cod+'","'+comb.nombre+'")\n'
    f.write(output)
    conta+= 1

//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//IndPol.cc

#include "IndPol.h"

bool operator<(const IndPol &i1,const IndPol &i2)
  {
    assert(i1.size() == i2.size());
    IndPol::size_type ultimo= i1.size() - 1;
    long i;
    if (i1.Grado() < i2.Grado())
      return 1;
    else
      if (i1.Grado() > i2.Grado()) 
        return 0;
    for(i=ultimo;i>=0;i--)
      if (i1[i] < i2[i]) 
        return 1;
      else
        if (i1[i] > i2[i]) 
          return 0;
    return 0;
  }

IndPol Conv(const NmbVars &destVars,const NmbVars &srcVars, const IndPol &srcInd) 
//Convierte el indice Indpol referido al conjunto de variables
//srcVars al conjunto de variables destVars, devolviendo
//este ultimo.
  {
    if (destVars == srcVars) return srcInd;
    IndPol conv(destVars.size(),0);
    IndPol::size_type i;
    vZ_sui ind= destVars.Indices(srcVars);
    for(i=0;i<srcInd.size();i++)
      conv[ind[i]]= srcInd[i];
    return conv;
  }

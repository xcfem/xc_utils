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
//descomp.h
//Decomposition of a matrix in two triangular matrices.

#ifndef DESCOMP_H
#define DESCOMP_H

#include <cmath>
#include "xc_utils/src/matrices/ZMatrix.h"
#include "xc_utils/src/utils/misc_utils/matem.h"

template <class treal>
void descomp(ZMatrix<treal> &a)
  {
   size_t i,j,k;
   const size_t n= a.getNumberOfRows();
   for(i=1;i<= n-1;i++)
     {
       for(j= i+1;j<= n;j++)
         {
	   if(i>1)
             for(k=1;k<= i-1;k++)
               a(i,j)-= a(i,k)*a(k,j);
	   a(i,j)/= a(i,i);
         }
       for(j=i+1;j<=n;j++)
	 for(k=1;k<= i;k++)
           a(j,i+1)-= a(j,k)*a(k,i+1);
     }
}
#endif

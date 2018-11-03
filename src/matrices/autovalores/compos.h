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
//compos.h
//Computing the product of two triangular matrices.

#ifndef COMPOS_H
#define COMPOS_H

#include <cmath>
#include "xc_utils/src/matrices/ZMatrix.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/matrices/solvers/gj_aux.h"

template <class treal>
void compos(ZMatrix<treal> &a,treal &max)
  {
    size_t i,j,k,l,n= a.getNumberOfRows();
    treal s,xx;
    max=0;
    for(i=1;i<= n;i++)
      for(j=1;j<= n;j++)
        {
          if(i<j)
            { s= 0.0;k=j; }
          else
            {s= a(i,j);k=i+1;}
          if(k<=n)
            for(l=k;l<=n;l++) s+=a(i,l)*a(l,j);
          a(i,j)= s;
          if(i<j)
            {
              xx= gj_abs(s);
              if(xx>max) max=xx;
            }
        }
  }
#endif

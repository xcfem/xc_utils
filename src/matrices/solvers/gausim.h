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
//Gauss.h
//Gauss procedure to solve a linear system of equations with a symmetric
//coefficient matrix.

#ifndef GAUSIM_H
#define GAUSIM_H

#include <cmath>
#include "xc_utils/src/matrices/matsimZ.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/matrices/solvers/gj_aux.h"

template <class treal>
void elim( matsimZ<treal> &a,
           ZMatrix<treal> &b,
           const size_t &j)
  {
    size_t i,n= a.getNumberOfRows();
    i=j;
    while(i<n)
      {
        i++; treal s= a(j,i)/a(j,j);
        if( gj_abs(s)> zero)
          {
            for(size_t k=i;k<=n;k++) a(i,k)-= s*a(j,k);
            b(i)-= s*b(j);
            a(j,i)= s;
          }
      }
    b(j)/= a(j,j);
  }

template <class treal>
ZMatrix<treal> calcularx( const matsimZ<treal> &a,
                          const ZMatrix<treal> &b)
  {
    size_t l,k,n= a.getNumberOfRows();
    ZMatrix<treal> x(n,1,0.0);
    for(l=n;l>=1;l--)
      {
        k= l; x(l)=b(l);
        while(k<n)
          {
            k++;
            x(l)-= a(l,k)*x(k);
          }
      }
    return x;
  }

template <class treal>
ZMatrix<treal> gausim(matsimZ<treal> &a,ZMatrix<treal> &b,int &simreg)
  {
    size_t j= 0,n= a.getNumberOfRows();
    simreg=1;
    while(simreg && (j<n))
      {
        j++;
        simreg= (gj_abs(a(j,j))>zero);
        if(simreg) elim(a,b,j);
      }
    ZMatrix<treal> x;
    if(simreg) x= calcularx(a,b);
    return x;
  }
#endif



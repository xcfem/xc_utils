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
//Cholesky.h
//Cholesky procedure to solve a linear system of equations with a symmetric
//and positive definite coefficient matrix.

#ifndef CHOLESKY_H
#define CHOLESKY_H

#include <cmath>
#include "xc_utils/src/matrices/matsimZ.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/matrices/solvers/gj_aux.h"

template <class treal>
treal prod( const size_t &i,
            const size_t &j,
            const matsimZ<treal> &a)
  {
    size_t k;
    treal s;
    s= a(i,j); k=1;   // j<i 
    while(k<j)
      {
        s-= a(i,k)*a(j,k);
        k++;
      }
    return s;
  }

template <class treal>
void colum(const size_t &j,matsimZ<treal> &a)
  {
    size_t i,n= a.getNumberOfRows();
    treal s= sqrt(a(j,j)); a(j,j)=s; i=j+1;
    while(i<=n)
      { a(i,j)= prod(i,j,a)/s; i++; }
  }

template <class treal>
ZMatrix<treal> calcularx(const matsimZ<treal> &a, const ZMatrix<treal> &b)
  {
    size_t i,k,n= a.getNumberOfRows();
    ZMatrix<treal> x(n,1,0.0);
    for(i= 1;i<=n;i++)          //primer sistema
      {
        x(i,1)= b(i,1); k=1;
        while(k<i)
          {
            x(i,1)-= x(k,1)*a(i,k);
            k++;
          }
        x(i,1)/= a(i,i);
      }
    for(i=n;i>=1;i--)      //segundo sistema
      {
        k=n;
        while(k>i)
          {
            x(i,1)-= x(k,1)*a(k,i);
            k--;
          }
        x(i,1)/= a(i,i);
      }
    return x;
  }

template <class treal>
ZMatrix<treal> cholesky(matsimZ<treal> &a,ZMatrix<treal> &b,int &defpos)
  {
    defpos= 1; size_t j=0,n= a.getNumberOfRows();
    while(defpos && (j<n))
      {
        j++; a(j,j)= prod(j,j,a);
        defpos= (a(j,j)>zero);
        if(defpos) colum(j,a);
      }
     ZMatrix<treal> x;
     if(defpos) x= calcularx(a,b);
     return x;
  }
#endif

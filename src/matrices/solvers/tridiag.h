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
//Tridiag.h
//Procedimiento para la soluciOn de un sistema de ecuaciones tridiagonal.
//Que el mEtodo devuelva como resultado regular= 1 sOlo quiere decir
//que no puede calcular la solucion no que no exista. Por tanto en
//estos casos deberA intentarse encontrar la soluciOn mediante un mEtodo
//general (gauss,...)

#ifndef TRIDIAG_H
#define TRIDIAG_H

#include <cmath>
#include "xc_utils/src/matrices/matridZ.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "gj_aux.h"

template <class treal>
void fil(const size_t &i,
         matridZ<treal> &a,
         ZMatrix<treal> &b,
         int &regular)
  {
    a(i,i)-= a(i,i-1)*a(i-1,i);
    regular= (gj_abs(a(i,i))>zero);
    if(regular)
      {
        a(i,i+1)/=a(i,i);
        b(i)= (b(i)-a(i,i-1)*b(i-1))/a(i,i);
      }
  }

template<class treal>
ZMatrix<treal> calcularx(matridZ<treal> &a,ZMatrix<treal> &b)
  {
    size_t n= a.getNumberOfRows();
    ZMatrix<treal> x(n,1,0.0);
    x(n)= b(n);
    for(size_t k=n-1;k>=1;k--) x(k)=b(k)-x(k+1)*a(k,k+1);
    return x;
  }

template <class treal>
ZMatrix<treal> tridiag(matridZ<treal> &a,ZMatrix<treal> &b,int &regular)
  {
    size_t i,n= a.getNumberOfRows();
    i=0; regular=1;
    while(regular && (i<n))
      { i++; fil(i,a,b,regular); }
    ZMatrix<treal> x;
    if(regular) x= calcularx(a,b);
    return x;
  }
#endif

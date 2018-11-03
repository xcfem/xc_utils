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
//Orto.h
//Procedimiento de ortogonalizaciOn para la soluciOn
//de un sistema de ecuaciones lineal.

#ifndef ORTO_H
#define ORTO_H

#include <cmath>
#include "xc_utils/src/matrices/ZMatrix.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/matrices/solvers/gj_aux.h"

template <class treal>
treal escalar(const size_t &i,const size_t &j,const ZMatrix<treal> &a)
  {
    treal s=0.0,n= a.getNumberOfRows();
    for(size_t k=1;k<=n;k++) s+=a(i,k)*a(j,k);
    return s;
  }

template <class treal>
ZMatrix<treal> calcularx( const ZMatrix<treal> &a,
                          ZMatrix<treal> &b,
                          const ZMatrix<treal> &r)
  {
    size_t i,n= a.getNumberOfRows();
    ZMatrix<treal> x(n,1,0.0);
    for(i=1;i<=n;i++) b(i,1)*=r(i,1);
    for(i=1;i<=n;i++)
      for(size_t k=1;k<=n;k++) x(i)+= a(k,i)*b(k,1);
    return x;
  }

template <class treal>
ZMatrix<treal> ortoresol(ZMatrix<treal> &a,ZMatrix<treal> &b,int &regular)
  {
    size_t   i=0,l=0,n= a.getNumberOfRows();
    ZMatrix<treal> r(n,1,0.0),landa(n,1,0.0);
    regular=1;
    while( regular && (l<n))
      {
        l++; i=1;
        while(i<l)
          {
            landa(i,1)= r(i,1)*escalar(i,l,a);
            i++;
          }
        i=1;
        while(i<l)
          {
            for(size_t k=1;k<=n;k++) a(l,k)-= landa(i,1)*a(i,k);
            b(l,1)-= landa(i,1)*b(i,1);
            i++;
          }
        r(l,1)= escalar(l,l,a);
        regular= (gj_abs(r(l,1)) > zero);
        if(regular) r(l,1)= gj_inv(r(l,1));
      }
    ZMatrix<treal> x;
    if(regular) x= calcularx(a,b,r);
    return x;
  }
#endif

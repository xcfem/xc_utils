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
//Procedimiento de Gauss para la solución de un sistema de ecuaciones lineal.

#ifndef GAUSS_H
#define GAUSS_H

#include <cmath>
#include "xc_utils/src/matrices/ZMatrix.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/matrices/solvers/pivote.h"
#include "xc_utils/src/matrices/solvers/calcularx.h"

template <class treal>
void eliminar( ZMatrix<treal> &a,
               ZMatrix<treal> &b,
               const size_t &j,
               size_t *pivot,
               const set_szt &fp)
  {
    size_t i,k,l,n= a.getNumberOfRows(),m=b.getNumberOfColumns();
    l=pivot[j-1]; treal r=gj_inv(a(l,j));
    for(k=j+1;k<= n;k++) a(l,k)*=r;
    for(k=1;k<=m;k++) b(l,k)*=r;
    for(i=1;i<=n;i++)
      if (!In(fp,i) && (gj_abs(a(i,j))>zero))
	{
          for(k=j+1;k<=n;k++) a(i,k)-= a(i,j)*a(l,k);
          for(k=1;k<=m;k++) b(i,k)-= a(i,j)*b(l,k);
        }
  }

template <class treal>
ZMatrix<treal> gauss(ZMatrix<treal> &a,ZMatrix<treal> &b,int &regular)
  {
    size_t j;
    //Dimension of the pivot indices matrix.
    typename ZMatrix<treal>::size_type n= a.getNumberOfRows();
    typename ZMatrix<treal>::size_type *pivot= new typename ZMatrix<treal>::size_type[n];
    set_szt fp;
    regular=1; j=0;
    while (regular && (j<n))
      {
        j++;
        pivot[j-1]= pivote(j,a,fp);
        regular=(pivot[j-1]>0);
        if(regular)
          {
            fp.insert(pivot[j-1]);
            eliminar(a,b,j,pivot,fp);
          }
      }
    ZMatrix<treal> x;
    if(regular) x= calcularx(a,b,pivot);
    delete[] pivot;
    return x;
  }

template <class treal>
ZMatrix<treal> gauss_const(const ZMatrix<treal> &a,const ZMatrix<treal> &b,int &regular)
  {
    ZMatrix<treal> c=a,d=b;
    return gauss(c,d,regular);
  }

template <class treal>  
ZMatrix<treal> operator /(const ZMatrix<treal> &b, const ZMatrix<treal> &a)
//Se le pasan copias de los valores de b y a.
  {
    if (b.getNumberOfRows() != a.getNumberOfRows())
      {
	std::cerr << "Matrices de dimensiones incompatibles en operador /" << std::endl;
        abort();      
      }
    int regular;
    ZMatrix<treal> x= gauss_const(a,b,regular);
    if (!regular) std::cerr << " singular matrix" << std::endl;
    return x;
  }

template <class treal>
ZMatrix<treal> operator /(const ZMatrix<treal> &m,const treal &d)
  { return m*gj_inv(d); }

//! @brief Return inverse matrix.
template <class treal>
ZMatrix<treal> gauss_invierte(const ZMatrix<treal> &a,int &regular)
  {
    ZMatrix<treal> b(a.getNumberOfRows(),a.getNumberOfColumns());
    b.Idn();
    ZMatrix<treal> x= gauss_const(a,b,regular);
    return x;
  }

#endif



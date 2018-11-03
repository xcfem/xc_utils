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
//souriau.h
// Computation of the characteristic equation of a matrix using the Souriau
// procedure.

#ifndef SOURIAU_H
#define SOURIAU_H

#include <cmath>
#include "xc_utils/src/matrices/ZMatrix.h"
#include "xc_utils/src/utils/misc_utils/matem.h"

template <class treal>
ZMatrix<treal> calbk(const ZMatrix<treal> &ak,const treal &tk)
  {
    size_t n= ak.getNumberOfRows();
    ZMatrix<treal> b(ak);
    for(size_t i=1;i<=n;i++)
      b(i,i)+=tk;
    return b;  
  }

template <class treal>  
vectorZ<treal> souriau(ZMatrix<treal> &a)
//Souriau procedure to compute the characteristic equation of a matrix.
//Devuelve un 
//	a:	matrix to obtain the characteristic equation of.
//	Valor devuelto:
//		vector en el que el elemento de Indice (k,1) es el
//		coeficiente de grado n-k del polinomio.
  {
    size_t n= a.getNumberOfRows();
    vectorZ<treal> t(n+1,1);    
    ZMatrix<treal>  ak(n,n,0.0),b(n,n);
    t[0]= 1;
    for(size_t k=1;k<=n;k++)
      {
        b= calbk(ak,t[k-1]);
        ak= a*b;
        t[k]=-ak.Traza()/k;
      }
    return t;
  }
#endif

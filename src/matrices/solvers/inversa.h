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
//inversa.h

#ifndef INVERSA_H
#define INVERSA_H


#include "gauss.h"

template <class treal>
ZMatrix<treal> inversa(ZMatrix<treal> &m,int &regular)
  {
    if (!m.Cuadrada()) ZMatrixError("Not a square matrix.");
    if(m.getNumberOfRows()<2)
      {
        //invierte kii
        ZMatrix<treal> t(m);
        treal det= t(1,1)*t(2,2)-t(2,1)*t(1,2);
        if(det == 0.0)
          regular= 0;
        else
          {
            treal dum= t(1,1)/det;
            t(1,1)= t(2,2)/det;
            t(1,2)= -t(1,2)/det;
            t(2,1)= -t(2,1)/det;
            t(2,2)= dum;
          }
        return t;
      }
    else //Mejorar (ver matrix++)
      return gauss_invierte(m,regular);
  }

#endif

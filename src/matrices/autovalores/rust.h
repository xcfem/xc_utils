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
//rust.h
// Computation of the characteristic equation of a matrix using the Rustihauser
// procedure.

#ifndef RUST_H
#define RUST_H

#include <cmath>
#include "xc_utils/src/matrices/ZMatrix.h"
#include "xc_utils/src/matrices/util/matem.h"


template <class treal>
void rust(ZMatrix<treal> &a,treal &epsi)
  {
    const int maxiter = 500;
    int j;
    treal max;
    j= 0;
    do
      {
        descomp(a);
        compos(a,max);
        j++;
      }
    while (!(max<epsi) || (j>maxiter));
    epsi= max;
  }
#endif

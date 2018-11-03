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
//potiter.h

#ifndef POTITER_H
#define POTITER_H

#include <cmath>
#include "xc_utils/src/matrices/ZMatrix.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/matrices/norm.h"

template <class treal>
treal valorp(const ZMatrix<treal> &a)
  {
    const treal epsi = 1e-5;
    size_t n= a.getNumberOfRows();
    ZMatrix<treal> v(n,1,1.0),va(n,1);
    treal ln=10*epsi,la= 0.0;
    while (gj_abs(la-ln)>epsi)
      {
        va= v; la= ln;
        v= a*va;
        ln= norm(v);
        v*=(gj_inv(ln));
      }
    if (v(1)*va(1)< 0)
       return -ln;
    else
       return ln;
  }
#endif

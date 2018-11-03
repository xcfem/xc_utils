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
//norm.h

#ifndef NORM_H
#define NORM_H

#include "math.h"
#include "ZMatrix.h"
#include "xc_utils/src/utils/misc_utils/matem.h"

template <class treal>
treal norm(const ZMatrix<treal> &x)
  {
    treal r;
    size_t n= x.getNumberOfRows();
    r= gj_abs(x(1));
    for(size_t i= 2;i<=n;i++)
      if (r<gj_abs(x(i))) r= gj_abs(x(i));
    return r;
  }

#endif

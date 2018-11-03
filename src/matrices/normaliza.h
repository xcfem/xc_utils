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
//Normaliza.h

#ifndef NORMALIZA_H
#define NORMALIZA_H


#include "ZMatrix.h"

template<class treal>
//! @brief Divide the components of the matrix by its norm.
inline void Normaliza(ZMatrix<treal> &m)
  {
    const treal vabs= Abs(m);
    if(vabs>0) m*= 1.0/vabs;
  }

template<class treal>
//! @brief Divide the components of the matrix by its norm.
inline ZMatrix<treal> Normaliza(const ZMatrix<treal> &m)
  {
    ZMatrix<treal> retval(m);
    Normaliza(retval);
    return retval;
  }

#endif

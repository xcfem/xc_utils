//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
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
//Prism3d.h

#ifndef PRISM3D_H
#define PRISM3D_H

#include "xc_utils/src/geom/d3/Solid3d.h"


//! @ingroup GEOM
//
//! @brief Base class for prims in a three-dimensional space.
class Prism3d : public Solid3d
  {
  public:
    Prism3d(void): Solid3d(){}
    Prism3d(const Prism3d &p): Solid3d(p){}
    Prism3d &operator=(const Prism3d &p)
      {
	Solid3d::operator=(p);
        return *this;
      }
  };
#endif




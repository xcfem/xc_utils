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
//VectorPos3d

#ifndef VECTORPOS3D_H
#define VECTORPOS3D_H

#include "Pos3d.h"
#include "VectorPos.h"

//! @ingroup GEOM
//
//! @brief Vector de posiciones en tres dimensiones [(x1,y1,z1),(x1,y2,z2),...].
class VectorPos3d: public VectorPos<Pos3d>
  {
  public:
    VectorPos3d(const size_t &f=1): VectorPos<Pos3d>(f) {}
    VectorPos3d(const Pos3d &p1,const Pos3d &p2,const size_t &num,const GEOM_FT &ratio)
      : VectorPos<Pos3d>(p1,p2,num,ratio) {}
    VectorPos3d(const Pos3d &p1,const Pos3d &p2,const size_t &ndiv)
      : VectorPos<Pos3d>(p1,p2,ndiv) {}
  };

#endif

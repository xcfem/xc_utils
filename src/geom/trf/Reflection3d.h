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
//Reflection3d.h
//Rotación en el plano.

#ifndef REFLECTION3D_H
#define REFLECTION3D_H

#include "Trf3d.h"

class Plane;


//! @ingroup GEOM
//
//! @brief Reflexión en 3d.
class Reflection3d: public Trf3d
  {
  private:
    static matriz_FT matriz_reflection3d(const Pos3d &Q,const Vector3d &d);

  public:
    Reflection3d(void);
    Reflection3d(const Pos3d &Q,const Vector3d &d);
    Reflection3d(const Plane &M);
  };

#endif

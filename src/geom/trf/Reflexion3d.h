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
//Reflexion3d.h
//Rotación en el plano.

#ifndef REFLEXION3D_H
#define REFLEXION3D_H

#include "Trf3d.h"

class Plano3d;


//! @ingroup GEOM
//
//! @brief Reflexión en 3d.
class Reflexion3d: public Trf3d
  {
  private:
    static matriz_FT matriz_reflexion3d(const Pos3d &Q,const Vector3d &d);

  public:
    Reflexion3d(void);
    Reflexion3d(const Pos3d &Q,const Vector3d &d);
    Reflexion3d(const Plano3d &M);
  };

#endif

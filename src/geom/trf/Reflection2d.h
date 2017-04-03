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
//Reflection2d.h
//Rotación en el plano.

#ifndef REFLECTION2D_H
#define REFLECTION2D_H

#include "Trf2d.h"

class Recta2d;


//! @ingroup GEOM
//
//! @brief Reflexión en dos dimensiones.
class Reflection2d: public Trf2d
  {
  private:
    static Reflection2d crea_reflection2d(const  Pos2d &Q,const Vector2d &d);

    Reflection2d( const GEOM_FT & m00,const GEOM_FT & m01,const GEOM_FT & m02,
                 const GEOM_FT & m10,const GEOM_FT & m11,const GEOM_FT & m12);
/*     Reflection2d( const GEOM_RT & m00,const GEOM_RT & m01,const GEOM_RT & m02, */
/*                  const GEOM_RT & m10,const GEOM_RT & m11,const GEOM_RT & m12, */
/*                  const GEOM_RT & hw = GEOM_RT(1.0)); */
  public:
    Reflection2d(const Pos2d &Q,const Vector2d &d);
    Reflection2d(const Recta2d &r);
  };

#endif

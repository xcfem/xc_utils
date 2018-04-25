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
//PrincipalAxesOfInertia2D.h

#ifndef PRINCIPALAXESOFINERTIA2D_H
#define PRINCIPALAXESOFINERTIA2D_H

#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"

class Ref2d2d;

//! @ingroup GEOM
//
//! @brief Principals axes of inertia in planar geometry.
class PrincipalAxesOfInertia2D
  {
    Pos2d cdg; //! Centroid.
    Vector2d axis1; //!< Direction of the first principal moment of inertia.
    GEOM_FT i1; //!< First principal moment of inertia.
    GEOM_FT i2; //!< Second principal moment of inertia.
  public:
    PrincipalAxesOfInertia2D(const Pos2d &cdg_,const GEOM_FT &Ix,const GEOM_FT &Iy,const GEOM_FT &Pxy);
    Ref2d2d getAxis(void) const;
    const GEOM_FT &I1() const;
    const GEOM_FT &I2() const;
    inline Vector2d getAxis1VDir(void) const
      { return axis1; }
    Vector2d getAxis2VDir(void) const;
  };

std::ostream &operator<<(std::ostream &os,const PrincipalAxesOfInertia2D &axis);


#endif





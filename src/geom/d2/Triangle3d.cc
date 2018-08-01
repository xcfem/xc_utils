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
//Triangle3d.cc

#include "Triangle3d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Triangle2d.h"
#include "../Wm3/Wm3DistVector3Triangle3.h"


Triangle3d::Triangle3d(const Ref2d3d &rf,const Triangle2d &t)
  : Polygon3d(rf,t.getPolygon()) {}
Triangle3d::Triangle3d(void): Polygon3d() {}
Triangle3d::Triangle3d(const Triangle3d &other)
  : Polygon3d(other) {}
Triangle3d::Triangle3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : Polygon3d(p1,p2,p3) {}

Triangle3d &Triangle3d::operator =(const Triangle3d &other) 
  {
    Polygon3d::operator=(other);
    return *this;
  }

//! @brief Return the squared distance from the point to the triangle.
GEOM_FT Triangle3d::dist2(const Pos3d &p) const
  {
    Wm3::DistVector3Triangle3ft d(p.VectorPos(),*this);
    return d.GetSquared();
  }

//! @brief Return the distance from the point to the triangle.
GEOM_FT Triangle3d::dist(const Pos3d &p) const
  {
    Wm3::DistVector3Triangle3ft d(p.VectorPos(),*this);
    return d.Get();
  }

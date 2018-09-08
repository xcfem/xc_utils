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
//Ref3d3d.cc
#include "Ref3d3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/d1/Line3d.h"
#include "xc_utils/src/geom/d2/Plane.h"

//! @brief Constructor.
Ref3d3d::Ref3d3d(void): BaseRef() {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o) : BaseRef(o) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o,const Rect3d3dCooSys &sc)
  : BaseRef(o,sc) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o,const Pos3d &p) : BaseRef(o,p) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : BaseRef(p1,Rect3d3dCooSys(p1,p2,p3)) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o,const Vector3d &v1,const Vector3d &v2)
  : BaseRef(o,Rect3d3dCooSys(v1,v2)) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o,const Vector3d &v1,const Vector3d &v2,const Vector3d &v3)
  : BaseRef(o,Rect3d3dCooSys(v1,v2,v3)) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Line3d &r,const Pos3d &p)
  : BaseRef(r.Point(0),Rect3d3dCooSys(r.Point(0),r.Point(100),p)) {}

Ref3d3d::~Ref3d3d(void)
  {}

//! @brief Return the unary vector I expressed in global coordinates.
Vector3d Ref3d3d::GetI(void) const
  { return getAxisVDir(1); }
//! @brief Return the unary vector J expressed in global coordinates.
Vector3d Ref3d3d::GetJ(void) const
  { return getAxisVDir(2); }
//! @brief Return the unary vector K expressed in global coordinates.
Vector3d Ref3d3d::GetK(void) const
  { return getAxisVDir(3); }

//! @brief Return the line defining the x axis.
Line3d Ref3d3d::getXAxis(void) const
  {
    const Pos3d dest(org+1000.0*GetI());
    return Line3d(org,dest);
  }

//! @brief Return the line defining the y axis.
Line3d Ref3d3d::getYAxis(void) const
  {
    const Pos3d dest(org+1000.0*GetJ());
    return Line3d(org,dest);
  }

//! @brief Return the line defining the z axis.
Line3d Ref3d3d::getZAxis(void) const
  {
    const Pos3d dest(org+1000.0*GetK());
    return Line3d(org,dest);
  }

Plane Ref3d3d::getXYPlane(void) const
  { return Plane(org,1000.0*GetI(),1000.0*GetJ()); }
Plane Ref3d3d::getXZPlane(void) const
  { return Plane(org,1000.0*GetI(),1000.0*GetK()); }
Plane Ref3d3d::getYZPlane(void) const
  { return Plane(org,1000.0*GetJ(),1000.0*GetK()); }

// GEOM_FT Ref3d3d::GetZLocal(const Pos3d &p) const
// //Return the local Z of the point p expressed in local coordinates
//   {
//     m_double inv(trf.getColumn(3));
//     inv.Trn();
//     return dot(inv,(p - org));
//   }


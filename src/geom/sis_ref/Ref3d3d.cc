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
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"

//! @brief Constructor.
Ref3d3d::Ref3d3d(void): BaseRef() {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o) : BaseRef(o) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o,const SisCooRect3d3d &sc)
  : BaseRef(o,sc) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o,const Pos3d &p) : BaseRef(o,p) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : BaseRef(p1,SisCooRect3d3d(p1,p2,p3)) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o,const Vector3d &v1,const Vector3d &v2)
  : BaseRef(o,SisCooRect3d3d(v1,v2)) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Pos3d &o,const Vector3d &v1,const Vector3d &v2,const Vector3d &v3)
  : BaseRef(o,SisCooRect3d3d(v1,v2,v3)) {}

//! @brief Constructor.
Ref3d3d::Ref3d3d(const Recta3d &r,const Pos3d &p)
  : BaseRef(r.Point(0),SisCooRect3d3d(r.Point(0),r.Point(100),p)) {}

Ref3d3d::~Ref3d3d(void)
  {}

Vector3d Ref3d3d::GetI(void) const
//Devuelve el vector unitario I en el sistema global.
  { return GetVDirEje(1); }
Vector3d Ref3d3d::GetJ(void) const
//Devuelve el vector unitario J en el sistema global.
  { return GetVDirEje(2); }
Vector3d Ref3d3d::GetK(void) const
//Devuelve el vector unitario K en el sistema global.
  { return GetVDirEje(3); }

Recta3d Ref3d3d::GetEjeX(void) const
//Return the recta que define el eje x.
  {
    const Pos3d dest(org+1000.0*GetI());
    return Recta3d(org,dest);
  }

Recta3d Ref3d3d::GetEjeY(void) const
//Return the recta que define el eje y.
  {
    const Pos3d dest(org+1000.0*GetJ());
    return Recta3d(org,dest);
  }

Recta3d Ref3d3d::GetEjeZ(void) const
//Return the recta que define el eje z.
  {
    const Pos3d dest(org+1000.0*GetK());
    return Recta3d(org,dest);
  }

Plano3d Ref3d3d::GetPlanoXY(void) const
  { return Plano3d(org,1000.0*GetI(),1000.0*GetJ()); }
Plano3d Ref3d3d::GetPlanoXZ(void) const
  { return Plano3d(org,1000.0*GetI(),1000.0*GetK()); }
Plano3d Ref3d3d::GetPlanoYZ(void) const
  { return Plano3d(org,1000.0*GetJ(),1000.0*GetK()); }

// GEOM_FT Ref3d3d::GetZLocal(const Pos3d &p) const
// //Return the local Z of the point p expressed in local coordinates
//   {
//     m_double inv(trf.GetCol(3));
//     inv.Trn();
//     return dot(inv,(p - org));
//   }


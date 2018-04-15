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
//Ref2d3d.cc
#include "Ref2d3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"

//! @brief Constructor.
Ref2d3d::Ref2d3d(void)
  : BaseRef() {}

//! @brief Constructor.
Ref2d3d::Ref2d3d(const Pos3d &o)
  : BaseRef(o) {}

//! @brief Constructor.
Ref2d3d::Ref2d3d(const Pos3d &o,const SisCooRect2d3d &sc)
  : BaseRef(o,sc) {}

//! @brief Constructor.
Ref2d3d::Ref2d3d(const Pos3d &o,const Pos3d &p,const Pos3d &q)
  : BaseRef(o,SisCooRect2d3d(o,p,q)) {}

//! @brief Constructor.
Ref2d3d::Ref2d3d(const Pos3d &o,const Vector3d &v)
  : BaseRef(o,SisCooRect2d3d(v)) {}

//! @brief Constructor.
Ref2d3d::Ref2d3d(const Pos3d &o,const Vector3d &v1,const Vector3d &v2)
  : BaseRef(o,SisCooRect2d3d(v1,v2)) {}


//! @brief Return el vector unitario I en el sistema global.
Vector3d Ref2d3d::GetI(void) const
  { return GetVDirEje(1); }

//! @brief Return el vector unitario I en el sistema global.
Vector3d Ref2d3d::GetJ(void) const
  { return GetVDirEje(2); }

//! @brief Return la recta que define el x axis.
Recta3d Ref2d3d::GetEjeX(void) const
  {
    const Pos3d dest(org+1000.0*GetI());
    return Recta3d(org,dest);
  }

//! @brief Return la recta que define el x axis.
Recta3d Ref2d3d::GetEjeY(void) const
  {
    const Pos3d dest(org+1000.0*GetJ());
    return Recta3d(org,dest);
  }

Plano3d Ref2d3d::GetPlanoXY(void) const
  { return Plano3d(org,1000.0*GetI(),1000.0*GetJ()); }


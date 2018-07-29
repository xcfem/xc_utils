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
//Ref2d2d.cc
#include "Ref2d2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/pos_vec/Dir2d.h"
#include "xc_utils/src/geom/d1/Line2d.h"



Ref2d2d::Ref2d2d(void): BaseRef() {}
Ref2d2d::Ref2d2d(const Pos2d &o) : BaseRef(o) {}
Ref2d2d::Ref2d2d(const Pos2d &o,const SisCooRect2d2d &sc): BaseRef(o,sc) {}
Ref2d2d::Ref2d2d(const Pos2d &o,const Vector2d &vX): BaseRef(o,vX) {}
Ref2d2d::Ref2d2d(const Pos2d &o,const Dir2d &dirX): BaseRef(o,dirX) {}
Ref2d2d::Ref2d2d(const Pos2d &o,const Pos2d &p): BaseRef(o,p) {}

//! @brief Return the unary vector I expressed in global coordinates.
Vector2d Ref2d2d::GetI(void) const
  { return getAxisVDir(1); }
//! @brief Return the unary vector J expressed in global coordinates.
Vector2d Ref2d2d::GetJ(void) const
  { return getAxisVDir(2); }

//! @brief Return la line defining the x axis.
Line2d Ref2d2d::getXAxis(void) const
  {
    const Pos2d dest(org+1000.0*GetI());
    return Line2d(org,dest);
  }
//! @brief Return la line defining the y axis.
Line2d Ref2d2d::getYAxis(void) const
  {
    const Pos2d dest(org+1000.0*GetJ());
    return Line2d(org,dest);
  }


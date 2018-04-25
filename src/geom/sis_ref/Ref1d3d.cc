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
//Ref1d3d.cc
#include "Ref1d3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"



Ref1d3d::Ref1d3d(void): BaseRef() {}
Ref1d3d::Ref1d3d(const Pos3d &o): BaseRef(o) {}
Ref1d3d::Ref1d3d(const Pos3d &o,const SisCooRect1d3d &sc): BaseRef(o,sc) {}
Ref1d3d::Ref1d3d(const Pos3d &o,const Vector3d &vX): BaseRef(o,vX) {}
Ref1d3d::Ref1d3d(const Pos3d &o,const Dir3d &dirX): BaseRef(o,dirX) {}
Ref1d3d::Ref1d3d(const Pos3d &o,const Pos3d &p) : BaseRef(o,p) {}

//! @brief Return the global coordinates of unit vector I.
Vector3d Ref1d3d::GetI(void) const
  { return getAxisVDir(1); }

//! @brief Returns the line defined by X axis.
Recta3d Ref1d3d::getXAxis(void) const
  {
    const Pos3d dest(org+1000.0*GetI());
    return Recta3d(org,dest);
  }


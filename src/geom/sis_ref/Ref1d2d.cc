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
//Ref1d2d.cc
#include "Ref1d2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/pos_vec/Dir2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"



Ref1d2d::Ref1d2d(void): BaseRef() {}
Ref1d2d::Ref1d2d(const Pos2d &o) : BaseRef(o) {}
Ref1d2d::Ref1d2d(const Pos2d &o,const SisCooRect1d2d &sc): BaseRef(o,sc) {}
Ref1d2d::Ref1d2d(const Pos2d &o,const Vector2d &vX): BaseRef(o,vX) {}
Ref1d2d::Ref1d2d(const Pos2d &o,const Dir2d &dirX): BaseRef(o,dirX) {}
Ref1d2d::Ref1d2d(const Pos2d &o,const Pos2d &p): BaseRef(o,p) {}

Vector2d Ref1d2d::GetI(void) const
//Devuelve el vector unitario I en el sistema global.
  { return GetVDirEje(1); }
Recta2d Ref1d2d::GetEjeX(void) const
//Devuelve la recta que define el eje x.
  {
    const Pos2d dest(org+1000.0*GetI());
    return Recta2d(org,dest);
  }


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
//ThreePoints3d.h

#ifndef THREEPOINTS3D_H
#define THREEPOINTS3D_H

#include "../pos_vec/Pos3d.h"


//! @ingroup GEOM
//
//! @brief Data structure that stores three points.
class ThreePoints3d : public ProtoGeom
  {
    Pos3d _org;
    Pos3d _p1;
    Pos3d _p2;
  protected:
    //void salva_miembros(std::ostream &os,const std::string &indent) const;
  public:
    ThreePoints3d(void): ProtoGeom() {}
    ThreePoints3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3): ProtoGeom()
      { ThreePoints3d(p1,p2,p3); }
    const Pos3d &Org(void) const
      { return _org; }
    const Pos3d &P1(void) const
      { return _p1; }
    const Pos3d &P2(void) const
      { return _p2; }
  };

#endif

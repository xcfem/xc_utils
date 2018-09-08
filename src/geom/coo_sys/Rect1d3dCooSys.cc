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
//Rect1DCooSys.cc

#include "Rect1d3dCooSys.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Pos3d.h"



Rect1d3dCooSys::Rect1d3dCooSys(const VGlobal &vX)
  : Xd3dCooSys(1,vX)  //Axis 1 parallelo to Vx.
  {}
Rect1d3dCooSys::Rect1d3dCooSys(const PGlobal &o,const PGlobal &p)
  : Xd3dCooSys(1,o,p) {}

Rect1d3dCooSys::VGlobal Rect1d3dCooSys::GetI(void) const
//Return el vector unitario I en el sistema global.
  { return getAxisVDir(1); }
Rect1d3dCooSys::VGlobal Rect1d3dCooSys::GetCooGlobales(const VLocal &v) const
{ return Xd3dCooSys::GetCooGlobales(FT_matrix(1,1,v)); }
Rect1d3dCooSys::VLocal Rect1d3dCooSys::GetCooLocales(const Rect1d3dCooSys::VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const FT_matrix tmp= Xd3dCooSys::GetCooLocales(v);
    return VLocal(tmp(1));
  }


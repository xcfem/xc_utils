//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details. 
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//Rect3d3dCooSys.cc

#include "Rect3d3dCooSys.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"

Rect3d3dCooSys::Rect3d3dCooSys(const VGlobal &v1,const VGlobal &v2)
  : Xd3dCooSys(3,v1,v2) {}
Rect3d3dCooSys::Rect3d3dCooSys(const PGlobal &o,const PGlobal &p)
  : Xd3dCooSys(3,o,p) {}
Rect3d3dCooSys::Rect3d3dCooSys(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : Xd3dCooSys(3,p1,p2,p3) {}
Rect3d3dCooSys::Rect3d3dCooSys(const VGlobal &v1,const VGlobal &v2,const VGlobal &v3)
  : Xd3dCooSys(3,v1,v2,v3) {}
Rect3d3dCooSys::VGlobal Rect3d3dCooSys::GetI(void) const
//Return el vector unitario I en el sistema global.
  { return getAxisVDir(1); }
Rect3d3dCooSys::VGlobal Rect3d3dCooSys::GetJ(void) const
//Return el vector unitario J en el sistema global.
  { return getAxisVDir(2); }
Rect3d3dCooSys::VGlobal Rect3d3dCooSys::GetK(void) const
//Return el vector unitario K en el sistema global.
  { return getAxisVDir(3); }
Rect3d3dCooSys::VGlobal Rect3d3dCooSys::GetCooGlobales(const VLocal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  { return Xd3dCooSys::GetCooGlobales(v.getMatrix()); }
Rect3d3dCooSys::VLocal Rect3d3dCooSys::GetCooLocales(const VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const FT_matrix tmp= Xd3dCooSys::GetCooLocales(v);
    return VLocal(tmp(1),tmp(2),tmp(3));
  }


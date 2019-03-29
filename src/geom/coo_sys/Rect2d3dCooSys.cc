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
//Rect2d3dCooSys.cc

#include "Rect2d3dCooSys.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Vector2d.h"

#include "xc_utils/src/utils/text/text_string.h"



//! @brief Constructor.
//!
//! @param v: rotation angles about the axis 3, 2 and 1 that
//! applied sequentially align the global system with this one.
Rect2d3dCooSys::Rect2d3dCooSys(const VGlobal &v)
  : Xd3dCooSys(2,v) {}
//! @brief Define un sistema de coordenadas de dimensión i
//! el x axis tendrá la dirección y sentido del vector v1
//! se pasa como parámetro.
Rect2d3dCooSys::Rect2d3dCooSys(const VGlobal &v1,const VGlobal &v2)
  : Xd3dCooSys(2,v1,v2) {}
//! @brief Build the 2D coordinate system defined in a 3D space, so 
//! the axis 1 goes from p1 to p2 and p3 defines the plane that contains the
//! axis 1 and 2.
Rect2d3dCooSys::Rect2d3dCooSys(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : Xd3dCooSys(2,p1,p2,p3) {}

//! @brief Return el vector unitario I en el sistema global.
Rect2d3dCooSys::VGlobal Rect2d3dCooSys::GetI(void) const
  { return getAxisVDir(1); }
//! @brief Return el vector unitario J en el sistema global.
Rect2d3dCooSys::VGlobal Rect2d3dCooSys::GetJ(void) const
  { return getAxisVDir(2); }

Rect2d3dCooSys::VGlobal Rect2d3dCooSys::GetCooGlobales(const VLocal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  { return Xd3dCooSys::GetCooGlobales(v.getMatrix()); }

Rect2d3dCooSys::VLocal Rect2d3dCooSys::GetCooLocales(const VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const FT_matrix tmp= Xd3dCooSys::GetCooLocales(v);
    return VLocal(tmp(1),tmp(2));
  }


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
//Rect1d2dCooSys.cc

#include "Rect1d2dCooSys.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/pos_vec/Dir2d.h"

#include "xc_utils/src/utils/text/text_string.h"
#include "xc_utils/src/functions/algebra/ExprAlgebra.h"


Rect1d2dCooSys::Rect1d2dCooSys(const VGlobal &vX)
  : Xd2dCooSys(1,vX) {} //Axis 1 paralelo a Vx.
Rect1d2dCooSys::Rect1d2dCooSys(const PGlobal &p1,const PGlobal &p2)
  : Xd2dCooSys(1,p1,p2) {} //Axis 1 desde p1 a p2.

Rect1d2dCooSys::VGlobal Rect1d2dCooSys::GetI(void) const
//Return el vector unitario I en el sistema global.
  { return getAxisVDir(1); }
Rect1d2dCooSys::VGlobal Rect1d2dCooSys::GetCooGlobales(const VLocal &v) const
//Return las componentes del vector v 
//que se pasa como parámetro expresado en locales
//expresadas en coordenadas globales.
  { return Xd2dCooSys::GetCooGlobales(FT_matrix(1,1,v)); }
Rect1d2dCooSys::VLocal Rect1d2dCooSys::GetCooLocales(const Rect1d2dCooSys::VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const FT_matrix tmp= Xd2dCooSys::GetCooLocales(v);
    return tmp(1,1);
  }


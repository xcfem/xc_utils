//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//utils_list_pos3d.h

#ifndef UTILS_LIST_POS3D_H
#define UTILS_LIST_POS3D_H

#include "xc_utils/src/geom/GeomObj.h"

class BND3d;
class Trf3d;
class Vector3d;

//Auxiliary functions for manipulation of position lists.


//! @ingroup GEOM
//
void move(GeomObj::list_Pos3d &l,const Vector3d &);
void transform(GeomObj::list_Pos3d &l,const Trf3d &);
Pos3d getPMax(const GeomObj::list_Pos3d &);
Pos3d getPMin(const GeomObj::list_Pos3d &);
BND3d getBnd(const GeomObj::list_Pos3d &);

#endif


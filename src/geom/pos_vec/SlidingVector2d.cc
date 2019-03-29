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
//SlidingVector2d.cc

#include "SlidingVector2d.h"





//! @brief Constructor.
SlidingVector2d::SlidingVector2d(const Pos2d &o,const Pos2d &p)
  : Vector2d(p-o), org(o) {}

//! @brief Moment of a sliding vector with respect to a point.
GEOM_FT SlidingVector2d::getMoment(const Pos2d &o) const
  {
    GEOM_FT retval(0.0);
    if(!this->Nulo()) //Si ESTE vector no es nulo.
      {
        Vector2d r= org - o;
        if(!r.Nulo()) //Si r no es nulo.
          if(!paralelos(r,*this)) //Si r y ESTE no son paralelos
            retval= r.x()*this->y()-this->x()*r.y();
      }
    return retval;
  }

GEOM_FT inverso(const GEOM_FT &p)
  { return GEOM_FT(1.0/p); }

SlidingVector2d operator/(const SlidingVector2d &m,const GEOM_FT &p)
  { return m*inverso(p); }

SlidingVector2d operator-(const SlidingVector2d &v)
  {
    SlidingVector2d neg(v);
    neg.Neg();
    return neg;
  }


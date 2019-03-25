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
//d2to3D.h

#ifndef D2TO3D_H
#define D2TO3D_H

#include "xc_utils/src/geom/d2/Surface3d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"
#include "../cgal_types.h"

class Plane;
class Segment2d;
class Segment3d;
class Pos3dArray;
class Pos2dArray;

//! @ingroup GEOM
//
//! @brief Class that places 2D objects
//! (circle, ellipse, polygons, ...) in a 3D space.
class D2to3d: public Surface3d
  {
    Ref2d3d ref;

  protected:
    Pos3d to_3d(const Pos2d &p2d) const;
    Segment3d to_3d(const Segment2d &sg2d) const;
    Pos3dArray to_3d(const Pos2dArray &p2d) const;
    Pos2d to_2d(const Pos3d &p3d) const;

    D2to3d(const Ref2d3d &rf)
      : ref(rf) {}
    D2to3d(const Pos3d &o);
    D2to3d(const Pos3d &o,const Pos3d &p,const Pos3d &q);
    D2to3d(const Pos3d &o,const Vector3d &n,const Vector3d &i);

    const Ref2d3d &get_ref(void) const
      { return ref; }
  public:
    D2to3d(void);
    D2to3d(const D2to3d &);
    D2to3d &operator =(const D2to3d &);
    void ThreePoints(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);

    inline virtual unsigned short int Dimension(void) const
    //Return the dimensión del objeto 0, 1, 2 ó 3.
      { return 2; }

    Plane getPlane(void) const;

    friend bool operator ==(const D2to3d &a,const D2to3d &b);
    void Print(std::ostream &os) const;
  };

#endif

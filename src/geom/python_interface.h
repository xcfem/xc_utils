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
//python_interface.h

#ifndef python_interface_h
#define python_interface_h

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/docstring_options.hpp>
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/pos_vec/VectorPos2d.h"
#include "xc_utils/src/geom/pos_vec/VectorPos3d.h"
#include "xc_utils/src/geom/pos_vec/Pos2dArray.h"
#include "xc_utils/src/geom/pos_vec/Pos3dArray.h"
#include "xc_utils/src/geom/pos_vec/Pos2dArray3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3dArray3d.h"
#include "xc_utils/src/geom/d1/Line2d.h"
#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d1/Line3d.h"
#include "xc_utils/src/geom/d1/function_from_points/FunctionFromPointsR_R.h"
#include "xc_utils/src/geom/d1/function_from_points/FunctionFromPointsR2_R.h"
#include "xc_utils/src/geom/d2/BND2d.h"
#include "xc_utils/src/geom/d2/Surface2d.h"
#include "xc_utils/src/geom/d2/HalfPlane2d.h"
#include "xc_utils/src/geom/d2/Circle2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/PolygonalSurface2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Triangle2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Square2d.h"
#include "xc_utils/src/geom/d1/Polyline2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2dList.h"
#include "xc_utils/src/geom/d2/2d_polygons/Polygon2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/PolygonWithHoles2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/polygon2d_bool_op.h"
#include "xc_utils/src/geom/d1/Segment2d.h"
#include "xc_utils/src/geom/pos_vec/SlidingVector2d.h"
#include "xc_utils/src/geom/pos_vec/SlidingVector3d.h"
#include "xc_utils/src/geom/d1/Ray2d.h"
#include "xc_utils/src/geom/d1/Ray3d.h"
#include "xc_utils/src/geom/d1/Segment3d.h"
#include "xc_utils/src/geom/d3/BND3d.h"
#include "xc_utils/src/geom/d3/HalfSpace3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/PolyhedronBase.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/Tetrahedron3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/Polyhedron3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/Hexahedron3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3dList.h"
#include "xc_utils/src/geom/d1/Polyline3d.h"
//#include "xc_utils/src/geom/d3/Solid3d.h"
#include "xc_utils/src/geom/d2/Surface3d.h"
#include "xc_utils/src/geom/d2/GeneralEquationOfPlane.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d2/Triangle3d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Quadrilateral2d.h"
#include "xc_utils/src/geom/d2/Grid2d.h"
#include "xc_utils/src/geom/pos_vec/SlidingVectorsSystem2d.h"
#include "xc_utils/src/geom/pos_vec/SlidingVectorsSystem3d.h"
#include "xc_utils/src/geom/sis_ref/PrincipalAxesOfInertia2D.h"
#include "xc_utils/src/geom/sis_ref/Ref1d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref1d2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/sis_ref/Ref3d3d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/geom/trf/Scaling2d.h"
#include "xc_utils/src/geom/trf/Scaling3d.h"
#include "xc_utils/src/geom/trf/Identity2d.h"
#include "xc_utils/src/geom/trf/Identity3d.h"
#include "xc_utils/src/geom/trf/Reflection2d.h"
#include "xc_utils/src/geom/trf/Reflection3d.h"
#include "xc_utils/src/geom/trf/Revolution3d.h"
#include "xc_utils/src/geom/trf/Rotation2d.h"
#include "xc_utils/src/geom/trf/Rotation3d.h"
#include "xc_utils/src/geom/trf/Translation2d.h"
#include "xc_utils/src/geom/trf/Translation3d.h"

typedef std::deque<Pos2d> dq_pos2d;
typedef PolyPos<Pos2d> polyPos2d;
typedef std::deque<Pos3d> dq_pos3d;
typedef PolyPos<Pos3d> polyPos3d;

std::list<Polygon2d> from_python_list(boost::python::list &);
boost::python::list to_python_list(const std::list<Polygon2d> &);

//! @brief Return the Voronoi partition of the polygons in the list.
boost::python::list python_particiona(boost::python::list &);
boost::python::list python_clip(boost::python::list &, const Polygon2d &);

#endif

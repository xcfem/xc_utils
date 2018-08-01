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
#include "xc_utils/src/geom/d2/Superficie2d.h"
#include "xc_utils/src/geom/d2/HalfPlane2d.h"
#include "xc_utils/src/geom/d2/Circle2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/PolygonalSurface2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Triangle2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Cuadrado2d.h"
#include "xc_utils/src/geom/d1/Polyline2d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Polygon2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/PolygonWithHoles2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/polygon2d_bool_op.h"
#include "xc_utils/src/geom/d1/Segment2d.h"
#include "xc_utils/src/geom/pos_vec/VDesliz2d.h"
#include "xc_utils/src/geom/pos_vec/VDesliz3d.h"
#include "xc_utils/src/geom/d1/Ray2d.h"
#include "xc_utils/src/geom/d1/Ray3d.h"
#include "xc_utils/src/geom/d1/Segment3d.h"
#include "xc_utils/src/geom/d3/BND3d.h"
#include "xc_utils/src/geom/d3/HalfSpace3d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos3d.h"
#include "xc_utils/src/geom/d1/Polyline3d.h"
//#include "xc_utils/src/geom/d3/Solido3d.h"
#include "xc_utils/src/geom/d2/Superficie3d.h"
#include "xc_utils/src/geom/d2/GeneralEquationOfPlane.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d2/Triangle3d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Cuadrilatero2d.h"
#include "xc_utils/src/geom/d2/Rejilla2d.h"
#include "xc_utils/src/geom/pos_vec/SVD2d.h"
#include "xc_utils/src/geom/pos_vec/SVD3d.h"
#include "xc_utils/src/geom/sis_ref/PrincipalAxesOfInertia2D.h"
#include "xc_utils/src/geom/sis_ref/Ref1d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref1d2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/sis_ref/Ref3d3d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/geom/trf/Scaling2d.h"
#include "xc_utils/src/geom/trf/Scaling3d.h"
#include "xc_utils/src/geom/trf/Identidad2d.h"
#include "xc_utils/src/geom/trf/Identidad3d.h"
#include "xc_utils/src/geom/trf/Reflection2d.h"
#include "xc_utils/src/geom/trf/Reflection3d.h"
#include "xc_utils/src/geom/trf/Revolucion3d.h"
#include "xc_utils/src/geom/trf/Rotation2d.h"
#include "xc_utils/src/geom/trf/Rotation3d.h"
#include "xc_utils/src/geom/trf/Translation2d.h"
#include "xc_utils/src/geom/trf/Translation3d.h"

typedef std::deque<Pos2d> dq_pos2d;
typedef PoliPos<Pos2d> poliPos2d;
typedef std::deque<Pos3d> dq_pos3d;
typedef PoliPos<Pos3d> poliPos3d;

std::list<Polygon2d> from_python_list(boost::python::list &);
boost::python::list to_python_list(const std::list<Polygon2d> &);

//! @brief Return the Voronoi partition of the polygons in the list.
boost::python::list python_particiona(boost::python::list &);
boost::python::list python_clip(boost::python::list &, const Polygon2d &);

#endif

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
//tipos_cgal.h

#ifndef TIPOS_CGAL_H
#define TIPOS_CGAL_H

#include <CGAL/Homogeneous.h>
#include <CGAL/Lazy_exact_nt.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Point_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/enum.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Tetrahedron_3.h>
#include <iostream>
#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif

//typedef CGAL::Homogeneous<CGAL::Gmpz>  GEOMKernel; //kernel.
typedef CGAL::Exact_predicates_inexact_constructions_kernel GEOMKernel; //kernel.
typedef GEOMKernel::RT GEOM_RT;
typedef GEOMKernel::FT GEOM_FT;

static const GEOM_FT geom_epsilon(1/100000);
static const GEOM_FT geom_epsilon2= geom_epsilon*geom_epsilon;
inline GEOM_FT Abs(const GEOM_FT &x) { return x >= GEOM_FT(0) ? x : -x; }


//Enums
typedef CGAL::Orientation Orientacion;

//2D
typedef CGAL::Point_2<GEOMKernel> CGPoint_2;
typedef CGAL::Vector_2<GEOMKernel> CGVector_2;
typedef CGAL::Direction_2<GEOMKernel> CGDirection_2;
typedef CGAL::Line_2<GEOMKernel> CGRecta_2;
typedef CGAL::Ray_2<GEOMKernel> CGSemiRecta_2;
typedef CGAL::Segment_2<GEOMKernel> CGSegmento_2;
typedef CGAL::Circle_2<GEOMKernel> CGCirculo_2;
typedef CGAL::Triangle_2<GEOMKernel> CGTriangulo_2;
typedef CGAL::Iso_rectangle_2<GEOMKernel> CGIsoRectangle_2;
typedef CGAL::Polygon_2<GEOMKernel> CGPoligono_2;
typedef CGAL::Polygon_with_holes_2<GEOMKernel> CGPoligonoConAgujeros_2;
typedef CGAL::Aff_transformation_2<GEOMKernel> CGTrfAfin_2;

//3D
typedef CGAL::Point_3<GEOMKernel> CGPoint_3;
typedef CGAL::Vector_3<GEOMKernel> CGVector_3;
typedef CGAL::Direction_3<GEOMKernel> CGDirection_3;
typedef CGAL::Line_3<GEOMKernel> CGRecta_3;
typedef CGAL::Ray_3<GEOMKernel> CGSemiRecta_3;
typedef CGAL::Segment_3<GEOMKernel> CGSegmento_3;
typedef CGAL::Plane_3<GEOMKernel> CGPlane_3;
typedef CGAL::Iso_cuboid_3<GEOMKernel> CGIsoCuboid_3;
typedef CGAL::Polyhedron_3<GEOMKernel> CGPoliedro_3;
typedef CGAL::Tetrahedron_3<GEOMKernel> CGTetrahedron_3;
typedef CGAL::Bbox_3 CGBbox_3;
typedef CGAL::Aff_transformation_3<GEOMKernel> CGTrfAfin_3;


//Funciones

//Misc
typedef CGAL::Geomview_stream CGview_stream;

GEOM_FT double_to_FT(const double &d);
GEOM_FT sqrt_FT(const GEOM_FT &n);
GEOM_FT abs_FT(const GEOM_FT &n);

CGPoint_2 Point_2_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y);
CGDirection_2 Dir_2_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y);
CGVector_2 Vector_2_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y);
CGPoint_2 Point_2_from_doubles(const double &x,const double &y);
CGVector_2 Vector_2_from_doubles(const double &x,const double &y);

CGPoint_3 Point_3_from_cartesianas(const GEOM_FT &,const GEOM_FT &,const GEOM_FT &);
CGDirection_3 Dir_3_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y,const GEOM_FT &);
CGVector_3 Vector_3_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y,const GEOM_FT &);
CGPoint_3 Point_3_from_doubles(const double &x,const double &y,const double &z);
CGVector_3 Vector_3_from_doubles(const double &x,const double &y,const double &z);

const GEOM_FT VARIABLE_IS_NOT_USED M_PI_FT= double_to_FT(M_PI);

#endif

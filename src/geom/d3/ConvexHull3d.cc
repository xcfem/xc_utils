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
//ConvexHull3d.cc

#include "ConvexHull3d.h"
#include <CGAL/Homogeneous.h>
#include <CGAL/Convex_hull_traits_3.h>
#include <CGAL/convex_hull_3.h>
#include <vector>
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>
#include "xc_utils/src/geom/d3/3d_polyhedrons/Polyhedron3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/PolygonMap.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include <CGAL/cartesian_homogeneous_conversion.h>
#include <CGAL/Cartesian_converter.h>

typedef CGAL::Gmpz RT;
//typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Homogeneous<RT>                     K;
typedef CGAL::Convex_hull_traits_3<K>             Traits;
typedef Traits::Polyhedron_3                      Polyhedron_3;
typedef K::Segment_3                              Segment_3;
typedef K::Point_3                                Point_3;

const double escala= 1e3;

inline double double2intdouble(const double &d)
  { return floor(d*escala); }

inline Point_3 Pos3d_to_Point_3(const Pos3d &p3d)
  {
    return Point_3(double2intdouble(p3d.hx()),double2intdouble(p3d.hy()),double2intdouble(p3d.hz()),double2intdouble(p3d.hw()));
  }

inline CGPoint_3 Point_to_Pos3d(const Point_3 &np)
  { return CGPoint_3(to_double(np.hx())/escala,to_double(np.hy())/escala,to_double(np.hz())/escala,to_double(np.hw())/escala); }

class Point2Pos3d
  {
  public:
    CGPoint_3 operator()(const Point_3 &np) const
     { return Point_to_Pos3d(np); }
  };

CGPolyhedron_3 Polyhedron_to_Polyhedron3d(const Polyhedron_3 &np)
  {
    typedef CGPolyhedron_3::HalfedgeDS HalfedgeDS;
    CGPolyhedron_3 retval;
    Build_tdest_polyhedron<Polyhedron_3,HalfedgeDS,Point2Pos3d> bpoli(np);
    retval.delegate(bpoli);
    return retval;
  }

template <class InputIterator>
Polyhedron3d get_convex_hull(InputIterator first,InputIterator last)
  {
    Polyhedron3d retval;
    const size_t num_points= last-first;
    std::vector<Point_3> points(num_points);
    GeomObj::list_Pos3d::const_iterator j= first;
    for(register size_t i=0;i<num_points;i++)
      {
        points[i]= Pos3d_to_Point_3(*j);
        j++;
      }
    // define object to hold convex hull 
    CGAL::Object ch_object;
    // compute convex hull 
    CGAL::convex_hull_3(points.begin(), points.end(), ch_object);

    // determine what kind of object it is
    Segment_3 segment;
    Polyhedron_3 polyhedron;
    if( CGAL::assign(segment, ch_object) )
      std::cerr << "convex hull is a segment " << std::endl;
    else
      if( CGAL::assign (polyhedron, ch_object))
        {
          retval= Polyhedron3d(Polyhedron_to_Polyhedron3d(polyhedron));
        }
      else
        std::cerr << "convex hull error!" << std::endl;
    return retval;
  }
Polyhedron3d get_convex_hull(const GeomObj::list_Pos3d &lp)
  { return get_convex_hull(lp.begin(),lp.end()); }

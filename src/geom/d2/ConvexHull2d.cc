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
//ConvexHull2d.cc

#include "ConvexHull2d.h"
#include <vector>
#include "xc_utils/src/geom/d2/2d_polygons/Polygon2d.h"
//#include "xc_utils/src/geom/d2/PolygonMap.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;


const double escala= 1e3;

inline double double2intdouble(const double &d)
  { return floor(d*escala); }

inline Point_2 Pos2d_to_Point_2(const Pos2d &p2d)
  {
    return Point_2(double2intdouble(p2d.x()),double2intdouble(p2d.y()));
  }

inline CGPoint_2 Point_to_Pos2d(const Point_2 &np)
  { return CGPoint_2(np.x()/escala,np.y()/escala); }

// class Point2Pos2d
//   {
//   public:
//     CGPoint_2 operator()(const Point_2 &np) const
//      { return Point_to_Pos2d(np); }
//   };

template <class InputIterator>
Polygon2d get_convex_hull2d(InputIterator first,InputIterator last)
  {
    std::vector<Point_2> result;
     CGAL::convex_hull_2(first, last, std::back_inserter(result));
    Polygon2d retval;
    for(std::vector<Point_2>::const_iterator i= result.begin();i!=result.end();i++)
      retval.push_back(Point_to_Pos2d(*i));
    return retval;
  }
Polygon2d get_convex_hull2d(const GeomObj::list_Pos2d &lp)
  {
    std::vector<Point_2> input;
    for(GeomObj::list_Pos2d::const_iterator i= lp.begin();i!=lp.end();i++)
      input.push_back(Pos2d_to_Point_2(*i));
    return get_convex_hull2d(input.begin(),input.end());
 }

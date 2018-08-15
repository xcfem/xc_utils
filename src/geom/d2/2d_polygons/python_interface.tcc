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
//python_interface.cxx


Segment2d (PolygonalSurface2d::*getSide0Segment)(unsigned int i) const= &PolygonalSurface2d::Lado0;
class_<PolygonalSurface2d, bases<Surface2d>, boost::noncopyable >("PolygonalSurface2d", no_init)
  .def("getPerimeter",&PolygonalSurface2d::getPerimeter)
  .def("getCenterOfMass",&PolygonalSurface2d::getCenterOfMass)
  .def("getIx",&PolygonalSurface2d::Ix)
  .def("getIy",&PolygonalSurface2d::Iy)
  .def("getPxy",&PolygonalSurface2d::Pxy)
  .def("getVertice",&PolygonalSurface2d::Vertice0)
  .def("getLado",getSide0Segment)
  .def("getNormalLado",&PolygonalSurface2d::getLado0Normal)
  .def("getNormalVertice",&PolygonalSurface2d::getVertex0Normal)
  .def("getPolyline",&PolygonalSurface2d::getPolyline)
  .def("getApproxTangentPositions",&PolygonalSurface2d::getApproxTangentPositions,"Return the points for which the polygon is almost tangent to the direction argument.")
  ;

typedef std::list<Polygon2d> polygon_2D_list;
class_<polygon_2D_list >("polygon_2D_list")
  .def("__iter__", iterator<polygon_2D_list >())
  .add_property("size", &polygon_2D_list::size)
  .def("__len__", &polygon_2D_list::size)
  .def("empty", &polygon_2D_list::empty)
  .def("append", static_cast<void (polygon_2D_list::*)(const Polygon2d&)>(&polygon_2D_list::push_back))
  ;

void (Polygon2d::*unePolygon2d)(const Polygon2d &) =&Polygon2d::une;
Segment2d (Polygon2d::*clipLine)(const Line2d &) const=&Polygon2d::Clip;
Segment2d (Polygon2d::*clipRay)(const Ray2d &) const=&Polygon2d::Clip;
Segment2d (Polygon2d::*clipSegment)(const Segment2d &) const=&Polygon2d::Clip;
class_<Polygon2d, Polygon2d *, bases<PolygonalSurface2d> >("Polygon2d")
  .def(init<>())
  .def(init<Polyline2d>())
  .def(init<Polygon2d>())
  .def(init<boost::python::list>())
  .def("getNumVertices",&Polygon2d::GetNumVertices)
   //.def("insert",&Polygon2d::insert, "insert(vertex_iterator i,InputIterator first,InputIterator last) Insert the vertices between [first,last) before the vertex pointed by i.")
  .def("__getitem__",&Polygon2d::Vertice0,"return the i-th vertex.")
  .def("__iter__",range(&Polygon2d::vertices_begin, &Polygon2d::vertices_end))
  .def("offset",&Polygon2d::Offset)
  .def("getTributaryAreas",&Polygon2d::getTributaryAreas,"Return the tributary areas.")
  .def("agregaVertice",&Polygon2d::push_back)
  .def("getArea",&Polygon2d::getArea,"Return the polygon area.")
  .def("getRecubrimiento",&Polygon2d::GetRecubrimiento)
  .def("unePolygon2d",unePolygon2d)
  .def("clipLine",clipLine)
  .def("clipRay",clipRay)
  .def("clipSegment",clipSegment)
  .def("clipUsingPolygon",&Polygon2d::clipBy);

class_<Cuadrilatero2d, bases<Polygon2d> >("Cuadrilatero2d")
  .def(init<>())
  .def(init<Pos2d, Pos2d, Pos2d, Pos2d>())
  ;


class_<Square2d, bases<Cuadrilatero2d> >("Square2d")
  .def(init<>())
  ;

class_<Triangle2d, bases<Polygon2d> >("Triangle2d")
  .def(init<>())
  ;

class_<PolygonWithHoles2d, bases<Surface2d> >("PolygonWithHoles2d")
  .def(init<>())
  .def(init<Polygon2d>())
  .def("contour",&PolygonWithHoles2d::contour)
  .def("addHole",&PolygonWithHoles2d::add_hole)
  ;

def("particiona",python_particiona);
def("clip",python_clip);


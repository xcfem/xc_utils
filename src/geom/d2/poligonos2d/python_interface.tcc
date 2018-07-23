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


Segment2d (SupPoligonal2d::*getSide0Segment)(unsigned int i) const= &SupPoligonal2d::Lado0;
class_<SupPoligonal2d, bases<Superficie2d>, boost::noncopyable >("SupPoligonal2d", no_init)
  .def("getPerimetro",&SupPoligonal2d::Perimetro)
  .def("getCenterOfMass",&SupPoligonal2d::getCenterOfMass)
  .def("getIx",&SupPoligonal2d::Ix)
  .def("getIy",&SupPoligonal2d::Iy)
  .def("getPxy",&SupPoligonal2d::Pxy)
  .def("getVertice",&SupPoligonal2d::Vertice0)
  .def("getLado",getSide0Segment)
  .def("getNormalLado",&SupPoligonal2d::getLado0Normal)
  .def("getNormalVertice",&SupPoligonal2d::getVertex0Normal)
  .def("getPolyline",&SupPoligonal2d::getPolyline)
  .def("getApproxTangentPositions",&SupPoligonal2d::getApproxTangentPositions,"Return the points for which the polygon is almost tangent to the direction argument.")
  ;

typedef std::list<Poligono2d> polygon_2D_list;
class_<polygon_2D_list >("polygon_2D_list")
  .def("__iter__", iterator<polygon_2D_list >())
  .add_property("size", &polygon_2D_list::size)
  .def("__len__", &polygon_2D_list::size)
  .def("empty", &polygon_2D_list::empty)
  .def("append", static_cast<void (polygon_2D_list::*)(const Poligono2d&)>(&polygon_2D_list::push_back))
  ;

void (Poligono2d::*unePoligono2d)(const Poligono2d &) =&Poligono2d::une;
Segment2d (Poligono2d::*clipRecta)(const Recta2d &) const=&Poligono2d::Clip;
Segment2d (Poligono2d::*clipSemiRecta)(const SemiRecta2d &) const=&Poligono2d::Clip;
Segment2d (Poligono2d::*clipSegment)(const Segment2d &) const=&Poligono2d::Clip;
class_<Poligono2d, Poligono2d *, bases<SupPoligonal2d> >("Poligono2d")
  .def(init<>())
  .def(init<Polyline2d>())
  .def(init<Poligono2d>())
  .def(init<boost::python::list>())
  .def("getNumVertices",&Poligono2d::GetNumVertices)
   //.def("insert",&Poligono2d::insert, "insert(vertex_iterator i,InputIterator first,InputIterator last) Insert the vertices between [first,last) before the vertex pointed by i.")
  .def("__getitem__",&Poligono2d::Vertice0,"return the i-th vertex.")
  .def("__iter__",range(&Poligono2d::vertices_begin, &Poligono2d::vertices_end))
  .def("offset",&Poligono2d::Offset)
  .def("getTributaryAreas",&Poligono2d::getTributaryAreas,"Return the tributary areas.")
  .def("agregaVertice",&Poligono2d::push_back)
  .def("getArea",&Poligono2d::getArea,"Return the polygon area.")
  .def("getRecubrimiento",&Poligono2d::GetRecubrimiento)
  .def("unePoligono2d",unePoligono2d)
  .def("clipRecta",clipRecta)
  .def("clipSemiRecta",clipSemiRecta)
  .def("clipSegment",clipSegment)
  .def("clipPorPoligono",&Poligono2d::clipBy);

class_<Cuadrilatero2d, bases<Poligono2d> >("Cuadrilatero2d")
  .def(init<>())
  .def(init<Pos2d, Pos2d, Pos2d, Pos2d>())
  ;


class_<Cuadrado2d, bases<Cuadrilatero2d> >("Cuadrado2d")
  .def(init<>())
  ;

class_<Triangle2d, bases<Poligono2d> >("Triangle2d")
  .def(init<>())
  ;

class_<PoligonoConAgujeros2d, bases<Superficie2d> >("PoligonoConAgujeros2d")
  .def(init<>())
  .def(init<Poligono2d>())
  .def("contour",&PoligonoConAgujeros2d::contour)
  .def("addHole",&PoligonoConAgujeros2d::add_hole)
  ;

def("particiona",python_particiona);
def("clip",python_clip);


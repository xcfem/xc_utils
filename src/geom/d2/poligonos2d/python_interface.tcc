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


Segmento2d (SupPoligonal2d::*getSegmentoLado0)(unsigned int i) const= &SupPoligonal2d::Lado0;
class_<SupPoligonal2d, bases<Superficie2d>, boost::noncopyable >("SupPoligonal2d", no_init)
  .def("getPerimetro",&SupPoligonal2d::Perimetro)
  .def("getCdg",&SupPoligonal2d::Cdg)
  .def("getIx",&SupPoligonal2d::Ix)
  .def("getIy",&SupPoligonal2d::Iy)
  .def("getPxy",&SupPoligonal2d::Pxy)
  .def("getVertice",&SupPoligonal2d::Vertice0)
  .def("getLado",getSegmentoLado0)
  .def("getNormalLado",&SupPoligonal2d::getLado0Normal)
  .def("getNormalVertice",&SupPoligonal2d::getVertex0Normal)
  .def("getPolilinea",&SupPoligonal2d::GetPolilinea);


void (Poligono2d::*unePoligono2d)(const Poligono2d &) =&Poligono2d::une;
Segmento2d (Poligono2d::*recortaRecta)(const Recta2d &) const=&Poligono2d::Clip;
Segmento2d (Poligono2d::*recortaSemiRecta)(const SemiRecta2d &) const=&Poligono2d::Clip;
Segmento2d (Poligono2d::*recortaSegmento)(const Segmento2d &) const=&Poligono2d::Clip;
class_<Poligono2d, bases<SupPoligonal2d> >("Poligono2d")
  .def(init<>())
  .def(init<Polilinea2d>())
  .def(init<Poligono2d>())
  .def(init<boost::python::list>())
  .def("getNumVertices",&Poligono2d::GetNumVertices)
   //.def("insert",&Poligono2d::insert, "insert(vertex_iterator i,InputIterator first,InputIterator last) Inserta los vértices comprendidos en [first,last) antes antes del vértice al que se refiere i.")
  .def("__getitem__",&Poligono2d::Vertice0,"return the i-th vertex.")
  .def("__iter__",range(&Poligono2d::vertices_begin, &Poligono2d::vertices_end))
  .def("offset",&Poligono2d::Offset)
  .def("getAreasTributarias",&Poligono2d::getAreasTributarias)
  .def("agregaVertice",&Poligono2d::push_back)
  .def("getArea",&Poligono2d::Area)
  .def("getRecubrimiento",&Poligono2d::GetRecubrimiento)
  .def("unePoligono2d",unePoligono2d)
  .def("recortaRecta",recortaRecta)
  .def("recortaSemiRecta",recortaSemiRecta)
  .def("recortaSegmento",recortaSegmento)
  .def("recortaPorPoligono",&Poligono2d::clipBy);

class_<Cuadrilatero2d, bases<Poligono2d> >("Cuadrilatero2d")
  .def(init<>())
  .def(init<Pos2d, Pos2d, Pos2d, Pos2d>())
  ;


class_<Cuadrado2d, bases<Cuadrilatero2d> >("Cuadrado2d")
  .def(init<>())
  ;

class_<Triangulo2d, bases<Poligono2d> >("Triangulo2d")
  .def(init<>())
  ;

class_<PoligonoConAgujeros2d, bases<Superficie2d> >("PoligonoConAgujeros2d")
  .def(init<>())
  .def(init<Poligono2d>())
  .def("contour",&PoligonoConAgujeros2d::contour)
  .def("addHole",&PoligonoConAgujeros2d::add_hole)
  ;

def("particiona",python_particiona);
def("recorta",python_recorta);


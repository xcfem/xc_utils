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

class_<Superficie2d, bases<GeomObj2d>, boost::noncopyable  >("Superficie2d", no_init);

class_<Semiplano2d, bases<Superficie2d> >("HalfPlane2d")
  .def(init<>())
  .def(init<Recta2d>())
  ;

class_<Circulo2d, bases<Superficie2d> >("Circulo2d")
  .def(init<>())
  .def(init<Pos2d, Pos2d, Pos2d>())
  .def(init<Pos2d,double>())
  .def(init<Circulo2d>())
  .def("getCentro",&Circulo2d::Centro)
  .def("getRadio",&Circulo2d::Radio)
  .def("getDiametro",&Circulo2d::Diametro)
  .def("getPerimetro",&Circulo2d::Perimetro)
  .def("getArea", &Circulo2d::Area)
  .def("getIx", &Circulo2d::Ix)
  .def("getIy", &Circulo2d::Iy)
  .def("getIy", &Circulo2d::Iy)
  .def("getPxy", &Circulo2d::Pxy)
  .def("getCdg", &Circulo2d::Cdg);

#include "poligonos2d/python_interface.tcc"


class_<Superficie3d, bases<GeomObj3d>, boost::noncopyable  >("Superficie3d", no_init);

class_<EcuacionGeneralPlano3d, boost::noncopyable>("EcuacionGeneralPlano3d", no_init)
  .def(init<double,double,double,double>());

double (Plano3d::*AnguloPlano3d)(const Plano3d &p) const= &Plano3d::Angulo;
double (Plano3d::*AnguloVector3d)(const Vector3d &) const= &Plano3d::Angulo;
Pos3d (Plano3d::*ProyeccionPos3d)(const Pos3d &) const= &Plano3d::Proyeccion;
Vector3d (Plano3d::*ProyeccionVector3d)(const Vector3d &) const= &Plano3d::Proyeccion;
Recta3d (Plano3d::*ProyeccionRecta3d)(const Recta3d &) const= &Plano3d::Proyeccion;
Recta3d (Plano3d::*IntersPlano3d)(const Plano3d &p) const= &Plano3d::Interseccion;
Pos3d (Plano3d::*IntersRecta3d)(const Recta3d &p) const= &Plano3d::Interseccion;
Pos3d (Plano3d::*IntersSemiRecta3d)(const SemiRecta3d &p) const= &Plano3d::Interseccion;
Pos3d (Plano3d::*IntersSegmento3d)(const Segmento3d &p) const= &Plano3d::Interseccion;

class_<Plano3d, bases<Superficie3d> >("Plano3d")
  .def(init<Pos3d,Pos3d,Pos3d>())
  .def(init<Pos3d,Vector3d>())
  .def(init<Pos3d,Vector3d,Vector3d>())
  .def(init<Recta3d,Pos3d>()) 
  .def(init<EcuacionGeneralPlano3d>()) 
  .def(init<Plano3d>())
  .def("getAnguloPlano3d",AnguloPlano3d)
  .def("getAnguloVector3d",AnguloVector3d)
  .def("getProyeccionPos3d",ProyeccionPos3d)
  .def("getProyeccionVector3d",ProyeccionVector3d)
  .def("getProyeccionRecta3d",ProyeccionRecta3d)
  .def("getIntersPlano3d",IntersPlano3d)
  .def("getIntersRecta3d",IntersRecta3d)
  .def("getIntersSemiRecta3d",IntersSemiRecta3d)
  .def("getIntersSegmento3d",IntersSegmento3d)
  .def("getNormal", &Plano3d::Normal)
  .def("getBase1", &Plano3d::Base1)
  .def("getBase2", &Plano3d::Base2);

 class_<Rejilla2d, bases<Superficie2d> >("Rejilla2d")
   .def(init<>())
   .def("getMax",&Rejilla2d::GetMax)
   .def("getMin",&Rejilla2d::GetMin)
   .def("Area",&Rejilla2d::Area)
   .def("Ix",&Rejilla2d::Ix)
   .def("Iy",&Rejilla2d::Iy)
   .def("Pxy",&Rejilla2d::Pxy)
   .def("Cdg",&Rejilla2d::Cdg)
   .def("getPunto",&Rejilla2d::GetPunto)
   .def("getQuad",&Rejilla2d::GetQuad)
   .def("In",&Rejilla2d::In)
   .def("getPoints",make_function(&Rejilla2d::getPoints,return_internal_reference<>()))
   ;

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

class_<Superficie2d, bases<GeomObj2d>, boost::noncopyable  >("Surface2d", no_init);

class_<HalfPlane2d, bases<Superficie2d> >("HalfPlane2d")
  .def(init<>())
  .def(init<Recta2d>())
  ;

class_<BND2d, bases<GeomObj2d> >("BND2d")
  .def(init<>())
  .def(init<Pos2d, Pos2d>())
  .def(init<BND2d>())
  .add_property("width", &BND2d::Anchura, "returns object width.")
  .add_property("height", &BND2d::Altura, "returns object height.")
  .add_property("length", &BND2d::getLength, "returns object length.")
  .add_property("diagonal", &BND2d::Diagonal, "returns a vector from PMin to PMax.")
  .add_property("area", &BND2d::getArea, "returns object area.")
  .add_property("volume", &BND2d::getVolume, "returns object volume.")


  .def("update", &BND2d::Update)
  .add_property("pMax", &BND2d::GetPMax, &BND2d::PutPMax,"upper right corner.")
  .add_property("pMin", &BND2d::GetPMin, &BND2d::PutPMin,"lower left corner.")

  .def("getIx", &BND2d::Ix)
  .def("getIy", &BND2d::Iy)
  .def("getPxy", &BND2d::Pxy)
  .def("getCenterOfMass", &BND2d::getCenterOfMass)
  .def("getMax", &BND2d::GetMax,"returns maximum value of i coordinate.")
  .def("getMin", &BND2d::GetMin,"return minimum value of i coordinate.")
  ;

class_<Circulo2d, bases<Superficie2d> >("Circle2d")
  .def(init<>())
  .def(init<Pos2d, Pos2d, Pos2d>())
  .def(init<Pos2d,double>())
  .def(init<Circulo2d>())
  .def("getCentro",&Circulo2d::Centro)
  .def("getRadio",&Circulo2d::Radio)
  .def("getDiametro",&Circulo2d::Diametro)
  .def("getPerimetro",&Circulo2d::Perimetro)
  .def("getArea", &Circulo2d::getArea, "Return the object area.")
  .def("getIx", &Circulo2d::Ix)
  .def("getIy", &Circulo2d::Iy)
  .def("getPxy", &Circulo2d::Pxy)
  .def("getCenterOfMass", &Circulo2d::getCenterOfMass);

#include "poligonos2d/python_interface.tcc"


class_<Superficie3d, bases<GeomObj3d>, boost::noncopyable  >("Surface3d", no_init);

class_<D2to3d, bases<Superficie3d>, boost::noncopyable  >("D2to3d", no_init)
  .def("getPlane",&D2to3d::GetPlano)
  ;

class_<GeneralEquationOfPlane, boost::noncopyable>("GeneralEquationOfPlane", no_init)
  .def(init<double,double,double,double>());

double (Plane::*PlaneAngle)(const Plane &p) const= &Plane::Angulo;
double (Plane::*AnguloVector3d)(const Vector3d &) const= &Plane::Angulo;
Pos3d (Plane::*Pos3dProjection)(const Pos3d &) const= &Plane::Projection;
Vector3d (Plane::*Vector3dProjection)(const Vector3d &) const= &Plane::Projection;
Recta3d (Plane::*Recta3dProjection)(const Recta3d &) const= &Plane::Projection;
Recta3d (Plane::*IntersPlane)(const Plane &p) const= &Plane::Interseccion;
Pos3d (Plane::*IntersRecta3d)(const Recta3d &p) const= &Plane::Interseccion;
Pos3d (Plane::*IntersSemiRecta3d)(const SemiRecta3d &p) const= &Plane::Interseccion;
Pos3d (Plane::*IntersSegmento3d)(const Segmento3d &p) const= &Plane::Interseccion;
class_<Plane, bases<Superficie3d> >("Plane3d")
  .def(init<Pos3d,Pos3d,Pos3d>())
  .def(init<Pos3d,Vector3d>())
  .def(init<Pos3d,Vector3d,Vector3d>())
  .def(init<Recta3d,Pos3d>()) 
  .def(init<GeneralEquationOfPlane>()) 
  .def(init<Plane>())
  .def("getPlaneAngle",PlaneAngle)
  .def("getAnguloVector3d",AnguloVector3d)
  .def("getPos3dProjection",Pos3dProjection)
  .def("getVector3dProjection",Vector3dProjection)
  .def("getRecta3dProjection",Recta3dProjection)
  .def("getXYTrace",&Plane::XYTrace,"return the trace on the XY plane.")
  .def("getXZTrace",&Plane::XZTrace,"return the trace on the XZ plane.")
  .def("getYZTrace",&Plane::YZTrace,"return the trace on the YZ plane.")
  .def("getIntersPlane",IntersPlane)
  .def("getIntersRecta3d",IntersRecta3d)
  .def("getIntersSemiRecta3d",IntersSemiRecta3d)
  .def("getIntersSegmento3d",IntersSegmento3d)
  .def("getNormal", &Plane::Normal)
  .def("getBase1", &Plane::Base1)
  .def("getBase2", &Plane::Base2);

class_<Poligono3d, bases<D2to3d> >("Polygon3d");

class_<Triangulo3d, bases<Poligono3d>  >("Triangle3d")
  .def(init<Pos3d,Pos3d,Pos3d>())
  .def(init<Triangulo3d>())
  ;


class_<Rejilla2d, bases<Superficie2d> >("Grid2d")
  .def(init<>())
  .def("getMax",&Rejilla2d::GetMax)
  .def("getMin",&Rejilla2d::GetMin)
  .def("getArea",&Rejilla2d::getArea, "Return the object area.")
  .def("Ix",&Rejilla2d::Ix)
  .def("Iy",&Rejilla2d::Iy)
  .def("Pxy",&Rejilla2d::Pxy)
  .def("getCenterOfMass",&Rejilla2d::getCenterOfMass)
  .def("getPoint",&Rejilla2d::getPoint)
  .def("getQuad",&Rejilla2d::GetQuad)
  .def("In",&Rejilla2d::In)
  .def("getPoints",make_function(&Rejilla2d::getPoints,return_internal_reference<>()))
   ;

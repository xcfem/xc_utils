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

double (SemiEspacio3d::*AnguloConSemiEspacio3d)(const SemiEspacio3d &) const= &SemiEspacio3d::getAngulo;
double (SemiEspacio3d::*AnguloConPlano3d)(const Plano3d &) const= &SemiEspacio3d::getAngulo;
double (SemiEspacio3d::*AnguloConVector3d)(const Vector3d &) const= &SemiEspacio3d::getAngulo;

class_<SemiEspacio3d, bases<GeomObj3d> >("SemiEspacio3d")
  .def(init<Plano3d>())
  .def(init<SemiEspacio3d>())
  .def("anguloConSemiEspacio3d", AnguloConSemiEspacio3d)
  .def("anguloConPlano3d", AnguloConPlano3d)
  .def("anguloConVector3d", AnguloConVector3d)
  .def("getLima", &SemiEspacio3d::getLima)
  .def("getNormalExterior", &SemiEspacio3d::NormalExterior)
  .def("getNormalInterior", &SemiEspacio3d::NormalInterior)
  .def("getPlanoLimite", &SemiEspacio3d::getPlanoLimite,return_internal_reference<>() );

class_<BND3d, bases<GeomObj3d> >("BND3d")
  .def(init<>())
  .def(init<Pos3d, Pos3d>())
  .def(init<BND3d>())
  .add_property("width", &BND3d::Anchura, "returns object's width.")
  .add_property("height", &BND3d::Altura, "returns object's height.")
  .add_property("length", &BND3d::Longitud, "returns object's length.")
  .add_property("diagonal", &BND3d::Diagonal, "returns a vector from PMin to PMax.")
  .add_property("area", &BND3d::Area, "returns object's area.")
  .add_property("volume", &BND3d::Volumen, "returns object's volume.")


  .def("update", &BND3d::Update)
  .add_property("pMax", &BND3d::GetPMax, &BND3d::PutPMax,"upper right corner.")
  .add_property("pMin", &BND3d::GetPMin, &BND3d::PutPMin,"lower left corner.")

  .def("getIx", &BND3d::Ix)
  .def("getIy", &BND3d::Iy)
  .def("getPxy", &BND3d::Pxy)
  .def("getCdg", &BND3d::Cdg)
  .def("getMax", &BND3d::GetMax,"returns maximum value of i coordinate.")
  .def("getMin", &BND3d::GetMin,"returns minimum value of i coordinate.")
  ;

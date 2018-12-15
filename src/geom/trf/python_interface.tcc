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
class_<Trf, boost::noncopyable >("Trf", no_init)
  ;

Pos2d (Trf2d::*TrfPos2d)(const Pos2d &) const= &Trf2d::Transform;
Vector2d (Trf2d::*TrfVector2d)(const Vector2d &) const= &Trf2d::Transform;
class_<Trf2d, bases<Trf>, boost::noncopyable >("Trf2d", no_init)
//.def("getInverse", &Trf2d::Inversa)
  .def("getTrfVector2d", TrfVector2d)
  .def("getTrfPos2d", TrfPos2d)
   ;

// class_<Identity2d, bases<Trf2d> >("Identity2d");
// class_<Escalado2d, bases<Trf2d> >("Escalado2d");
// class_<Reflexion2d, bases<Trf2d> >("Reflexion2d");
class_<Rotation2d, bases<Trf2d> >("Rotation2d")
  .def(init<double>())
  ;
//class_<Translation2d, bases<Trf2d> >("Translation2d");

Pos3d (Trf3d::*TrfPos3d)(const Pos3d &) const= &Trf3d::Transform;
Vector3d (Trf3d::*TrfVector3d)(const Vector3d &) const= &Trf3d::Transform;
class_<Trf3d, bases<Trf>, boost::noncopyable >("Trf3d", no_init)
  .def("getTrfVector3d", TrfVector3d)
  .def("getTrfPos3d", TrfPos3d)
  ;

// class_<Escalado3d, bases<Trf3d> >("Escalado3d");
// class_<Identity3d, bases<Trf3d> >("Identity3d");
// class_<Reflexion3d, bases<Trf3d> >("Reflexion3d");
// class_<Rotation3d, bases<Trf3d> >("Rotation3d");

class_<Translation3d, bases<Trf3d> >("Translation3d")
  .def(init<Vector3d>())
;



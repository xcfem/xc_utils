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
typedef Ref<SisCooRect1d2d> ref_SisCooRect1d2d;
const ref_SisCooRect1d2d::PGlobal &(ref_SisCooRect1d2d::*getOrg1d2d)(void) const= &ref_SisCooRect1d2d::Org;
const SisCooRect1d2d &(ref_SisCooRect1d2d::*getCoordTransformation1d2d)(void) const= &ref_SisCooRect1d2d::Trf;
class_<ref_SisCooRect1d2d, bases<ProtoGeom>, boost::noncopyable >("ref_SisCooRect1d2d", no_init)
  .def("getVDirEje",&ref_SisCooRect1d2d::GetVDirEje)
  .def("getPosGlobal",&ref_SisCooRect1d2d::GetPosGlobal)
  .def("getCooGlobales",&ref_SisCooRect1d2d::GetCooGlobales)
  .def("getPosLocal",&ref_SisCooRect1d2d::GetPosLocal)
  .def("getCooLocales",&ref_SisCooRect1d2d::GetCooLocales)
  .def("getOrg",make_function(getOrg1d2d,return_internal_reference<>()))
  .def("getCoordTransformation",make_function(getCoordTransformation1d2d,return_internal_reference<>()))
  ;

class_<Ref1d2d , bases<ref_SisCooRect1d2d> >("Ref1d2d")
  .def(init<const Pos2d &>())
  .def(init<const Pos2d &,const Vector2d &>())
  .def(init<const Pos2d &,const Dir2d &>())
  .def(init<const Pos2d &,const Pos2d &>())
  .def("getI",&SisCooRect1d2d::GetI)
  ;

typedef Ref<SisCooRect1d3d> ref_SisCooRect1d3d;
const ref_SisCooRect1d3d::PGlobal &(ref_SisCooRect1d3d::*getOrg1d3d)(void) const= &ref_SisCooRect1d3d::Org;
const SisCooRect1d3d &(ref_SisCooRect1d3d::*getCoordTransformation1d3d)(void) const= &ref_SisCooRect1d3d::Trf;
class_<ref_SisCooRect1d3d, bases<ProtoGeom>, boost::noncopyable >("ref_SisCooRect1d3d", no_init)
  .def("getVDirEje",&ref_SisCooRect1d3d::GetVDirEje)
  .def("getPosGlobal",&ref_SisCooRect1d3d::GetPosGlobal)
  .def("getCooGlobales",&ref_SisCooRect1d3d::GetCooGlobales)
  .def("getPosLocal",&ref_SisCooRect1d3d::GetPosLocal)
  .def("getCooLocales",&ref_SisCooRect1d3d::GetCooLocales)
  .def("getOrg",make_function(getOrg1d3d,return_internal_reference<>()))
  .def("getCoordTransformation",make_function(getCoordTransformation1d3d,return_internal_reference<>()))
  ;

class_<Ref1d3d , bases<ref_SisCooRect1d3d> >("Ref1d3d")
  .def(init<const Pos3d &>())
  .def(init<const Pos3d &,const Vector3d &>())
  .def(init<const Pos3d &,const Dir3d &>())
  .def(init<const Pos3d &,const Pos3d &>())
  .def("getI",&SisCooRect1d3d::GetI)
  ;

typedef Ref<SisCooRect2d2d> ref_SisCooRect2d2d;
const ref_SisCooRect2d2d::PGlobal &(ref_SisCooRect2d2d::*getOrg2d2d)(void) const= &ref_SisCooRect2d2d::Org;
const SisCooRect2d2d &(ref_SisCooRect2d2d::*getCoordTransformation2d2d)(void) const= &ref_SisCooRect2d2d::Trf;
class_<ref_SisCooRect2d2d, bases<ProtoGeom>, boost::noncopyable >("ref_SisCooRect2d2d", no_init)
  .def("getVDirEje",&ref_SisCooRect2d2d::GetVDirEje)
  .def("getPosGlobal",&ref_SisCooRect2d2d::GetPosGlobal)
  .def("getCooGlobales",&ref_SisCooRect2d2d::GetCooGlobales)
  .def("getPosLocal",&ref_SisCooRect2d2d::GetPosLocal)
  .def("getCooLocales",&ref_SisCooRect2d2d::GetCooLocales)
  .def("getOrg",make_function(getOrg2d2d,return_internal_reference<>()))
  .def("getCoordTransformation",make_function(getCoordTransformation2d2d,return_internal_reference<>()))
  ;

class_<Ref2d2d , bases<ref_SisCooRect2d2d> >("Ref2d2d")
  .def(init<const Pos2d &>())
  .def(init<const Pos2d &,const Vector2d &>())
  .def(init<const Pos2d &,const Dir2d &>())
  .def(init<const Pos2d &,const Pos2d &>())
  .def("getI",&SisCooRect2d2d::GetI)
  .def("getJ",&SisCooRect2d2d::GetJ)
  ;

typedef Ref<SisCooRect2d3d> ref_SisCooRect2d3d;
const ref_SisCooRect2d3d::PGlobal &(ref_SisCooRect2d3d::*getOrg2d3d)(void) const= &ref_SisCooRect2d3d::Org;
const SisCooRect2d3d &(ref_SisCooRect2d3d::*getCoordTransformation2d3d)(void) const= &ref_SisCooRect2d3d::Trf;
class_<ref_SisCooRect2d3d, bases<ProtoGeom>, boost::noncopyable >("ref_SisCooRect2d3d", no_init)
  .def("getVDirEje",&ref_SisCooRect2d3d::GetVDirEje)
  .def("getPosGlobal",&ref_SisCooRect2d3d::GetPosGlobal)
  .def("getCooGlobales",&ref_SisCooRect2d3d::GetCooGlobales)
  .def("getPosLocal",&ref_SisCooRect2d3d::GetPosLocal)
  .def("getCooLocales",&ref_SisCooRect2d3d::GetCooLocales)
  .def("getOrg",make_function(getOrg2d3d,return_internal_reference<>()))
  .def("getCoordTransformation",make_function(getCoordTransformation2d3d,return_internal_reference<>()))
  ;

class_<Ref2d3d , bases<ref_SisCooRect2d3d> >("Ref2d3d")
  .def(init<const Pos3d &>())
  .def(init<const Pos3d &,const Pos3d &,const Pos3d &>())
  .def(init<const Pos3d &,const Vector3d &>())
  .def(init<const Pos3d &,const Vector3d &,const Vector3d &>())
  .def("getI",&SisCooRect2d3d::GetI)
  .def("getJ",&SisCooRect2d3d::GetJ)
  ;

typedef Ref<SisCooRect3d3d> ref_SisCooRect3d3d;
const ref_SisCooRect3d3d::PGlobal &(ref_SisCooRect3d3d::*getOrg3d3d)(void) const= &ref_SisCooRect3d3d::Org;
const SisCooRect3d3d &(ref_SisCooRect3d3d::*getCoordTransformation3d3d)(void) const= &ref_SisCooRect3d3d::Trf;
class_<ref_SisCooRect3d3d, bases<ProtoGeom>, boost::noncopyable >("ref_SisCooRect3d3d", no_init)
  .def("getVDirEje",&ref_SisCooRect3d3d::GetVDirEje)
  .def("getPosGlobal",&ref_SisCooRect3d3d::GetPosGlobal)
  .def("getCooGlobales",&ref_SisCooRect3d3d::GetCooGlobales)
  .def("getPosLocal",&ref_SisCooRect3d3d::GetPosLocal)
  .def("getCooLocales",&ref_SisCooRect3d3d::GetCooLocales)
  .def("getOrg",make_function(getOrg3d3d,return_internal_reference<>()))
  .def("getCoordTransformation",make_function(getCoordTransformation3d3d,return_internal_reference<>()))
  ;

class_<Ref3d3d , bases<ref_SisCooRect3d3d> >("Ref3d3d")
  .def(init<const Pos3d &>())
  .def(init<const Pos3d &,const Pos3d &>())
  .def(init<const Pos3d &,const Pos3d &,const Pos3d &>())
  .def(init<const Pos3d &,const Vector3d &,const Vector3d &>())
  .def(init<const Pos3d &,const Vector3d &,const Vector3d &,const Vector3d &>())
  .def(init<const Recta3d &,const Pos3d &>())
  .def("getI",&SisCooRect3d3d::GetI)
  .def("getJ",&SisCooRect3d3d::GetJ)
  .def("getK",&SisCooRect3d3d::GetK)
 ;


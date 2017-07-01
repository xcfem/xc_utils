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
class_<SisCoo, bases<ProtoGeom>, boost::noncopyable >("CooSys", no_init)
  .add_property("NumEjes",&SisCoo::NumEjes)
  .add_property("EsNormal",&SisCoo::EsNormal)
  .add_property("EsOrtogonal",&SisCoo::EsOrtogonal)
  .add_property("EsOrtonormal",&SisCoo::EsOrtonormal)
  .add_property("EsDextrogiro",&SisCoo::EsDextrogiro)
  ;

class_<SisCooXd2d, bases<SisCoo>, boost::noncopyable >("CooSysXd2d", no_init)
  .def("getVDirEje",&SisCooXd2d::GetVDirEje)
  .def("getDirEje",&SisCooXd2d::GetDirEje)
  ;

class_<SisCooXd3d, bases<SisCoo>, boost::noncopyable >("CooSysXd3d", no_init)
  .def("getVDirEje",&SisCooXd3d::GetVDirEje)
  .def("getDirEje",&SisCooXd3d::GetDirEje)
  ;

class_<SisCooRect1d2d, bases<SisCooXd2d>, boost::noncopyable >("CooSysRect1d2d", no_init)
  .def(init<const Pos2d &,const Pos2d &>())
  .def(init<const Vector2d &>())
  .def("getI",&SisCooRect1d2d::GetI)
  .def("getCooGlobales",&SisCooRect1d2d::GetCooGlobales)
  .def("getCooLocales",&SisCooRect1d2d::GetCooLocales)
  ;

class_<SisCooRect1d3d, bases<SisCooXd3d> >("CooSysRect1d3d")
  .def(init<const Pos3d &,const Pos3d &>())
  .def(init<const Vector3d &>())
  .def("getI",&SisCooRect1d3d::GetI)
  .def("getCooGlobales",&SisCooRect1d2d::GetCooGlobales)
  .def("getCooLocales",&SisCooRect1d3d::GetCooLocales)
  ;

class_<SisCooRect2d2d, bases<SisCooXd2d> >("CooSysRect2d2d")
  .def(init<const Pos2d &,const Pos2d &>())
  .def(init<const Vector2d &>())
  .def("getI",&SisCooRect2d2d::GetI)
  .def("getJ",&SisCooRect2d2d::GetJ)
  .def("getCooGlobales",&SisCooRect2d2d::GetCooGlobales)
  .def("getCooLocales",&SisCooRect2d2d::GetCooLocales)
  ;

class_<SisCooRect2d3d, bases<SisCooXd3d> >("CooSysRect2d3d")
  .def(init<const Pos3d &,const Pos3d &, const Pos3d &>())
  .def(init<const Vector3d &>())
  .def(init<const Vector3d &,const Vector3d &>())
  .def("getI",&SisCooRect2d3d::GetI)
  .def("getJ",&SisCooRect2d3d::GetJ)
  .def("getCooGlobales",&SisCooRect2d3d::GetCooGlobales)
  .def("getCooLocales",&SisCooRect2d3d::GetCooLocales)
  ;

class_<SisCooRect3d3d, bases<SisCooXd3d> >("CooSysRect3d3d")
  .def(init<const Pos3d &,const Pos3d &>())
  .def(init<const Pos3d &,const Pos3d &, const Pos3d &>())
  .def(init<const Vector3d &,const Vector3d &>())
  .def(init<const Vector3d &,const Vector3d &,const Vector3d &>())
  .def("getI",&SisCooRect3d3d::GetI)
  .def("getJ",&SisCooRect3d3d::GetJ)
  .def("getK",&SisCooRect3d3d::GetK)
  .def("getCooGlobales",&SisCooRect3d3d::GetCooGlobales)
  .def("getCooLocales",&SisCooRect3d3d::GetCooLocales)
  ;



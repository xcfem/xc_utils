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
class_<CooSys, bases<ProtoGeom>, boost::noncopyable >("CooSys", no_init)
  .add_property("numberOfAxis",&CooSys::numberOfAxis)
  .add_property("EsNormal",&CooSys::EsNormal)
  .add_property("EsOrtogonal",&CooSys::EsOrtogonal)
  .add_property("EsOrtonormal",&CooSys::EsOrtonormal)
  .add_property("EsDextrogiro",&CooSys::EsDextrogiro)
  ;

class_<Xd2dCooSys, bases<CooSys>, boost::noncopyable >("CooSysXd2d", no_init)
  .def("getAxisVDir",&Xd2dCooSys::getAxisVDir)
  .def("getAxisDir",&Xd2dCooSys::getAxisDir)
  ;

class_<Xd3dCooSys, bases<CooSys>, boost::noncopyable >("CooSysXd3d", no_init)
  .def("getAxisVDir",&Xd3dCooSys::getAxisVDir)
  .def("getAxisDir",&Xd3dCooSys::getAxisDir)
  ;

class_<Rect1d2dCooSys, bases<Xd2dCooSys>, boost::noncopyable >("CooSysRect1d2d", no_init)
  .def(init<const Pos2d &,const Pos2d &>())
  .def(init<const Vector2d &>())
  .def("getI",&Rect1d2dCooSys::GetI)
  .def("getCooGlobales",&Rect1d2dCooSys::GetCooGlobales)
  .def("getCooLocales",&Rect1d2dCooSys::GetCooLocales)
  ;

class_<Rect1d3dCooSys, bases<Xd3dCooSys> >("CooSysRect1d3d")
  .def(init<const Pos3d &,const Pos3d &>())
  .def(init<const Vector3d &>())
  .def("getI",&Rect1d3dCooSys::GetI)
  .def("getCooGlobales",&Rect1d2dCooSys::GetCooGlobales)
  .def("getCooLocales",&Rect1d3dCooSys::GetCooLocales)
  ;

class_<Rect2d2dCooSys, bases<Xd2dCooSys> >("CooSysRect2d2d")
  .def(init<const Pos2d &,const Pos2d &>())
  .def(init<const Vector2d &>())
  .def("getI",&Rect2d2dCooSys::GetI)
  .def("getJ",&Rect2d2dCooSys::GetJ)
  .def("getCooGlobales",&Rect2d2dCooSys::GetCooGlobales)
  .def("getCooLocales",&Rect2d2dCooSys::GetCooLocales)
  ;

class_<Rect2d3dCooSys, bases<Xd3dCooSys> >("CooSysRect2d3d")
  .def(init<const Pos3d &,const Pos3d &, const Pos3d &>())
  .def(init<const Vector3d &>())
  .def(init<const Vector3d &,const Vector3d &>())
  .def("getI",&Rect2d3dCooSys::GetI)
  .def("getJ",&Rect2d3dCooSys::GetJ)
  .def("getCooGlobales",&Rect2d3dCooSys::GetCooGlobales)
  .def("getCooLocales",&Rect2d3dCooSys::GetCooLocales)
  ;

class_<Rect3d3dCooSys, bases<Xd3dCooSys> >("CooSysRect3d3d")
  .def(init<const Pos3d &,const Pos3d &>())
  .def(init<const Pos3d &,const Pos3d &, const Pos3d &>())
  .def(init<const Vector3d &,const Vector3d &>())
  .def(init<const Vector3d &,const Vector3d &,const Vector3d &>())
  .def("getI",&Rect3d3dCooSys::GetI)
  .def("getJ",&Rect3d3dCooSys::GetJ)
  .def("getK",&Rect3d3dCooSys::GetK)
  .def("getCooGlobales",&Rect3d3dCooSys::GetCooGlobales)
  .def("getCooLocales",&Rect3d3dCooSys::GetCooLocales)
  ;



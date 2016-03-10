//----------------------------------------------------------------------------
//  programa XC; cálculo mediante el método de los elementos finitos orientado
//  a la solución de problemas estructurales.
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
//python_interface.tcc

class_<RelAcciones, bases<EntCmd> >("RelAcciones")
  .add_property("no_determinante", &RelAcciones::NoDeterminante, &RelAcciones::setNoDeterminante)
  .def("agregaIncompatible", &RelAcciones::AgregaIncompatible)
  .def("nombresIncompatibles", &RelAcciones::nombresIncompatibles)
  .def("agregaMaestra", &RelAcciones::AgregaMaestra)
  .def("nombresMaestras", &RelAcciones::nombresMaestras);

class_<Accion, bases<EntConNmb> >("Accion")
  .def(init<std::string, std::string>())
  .add_property("descripcion", make_function( &Accion::GetDescripcion, return_value_policy<copy_const_reference>() ), &Accion::SetDescripcion)
  .add_property("getRelaciones", make_function( &Accion::getRelaciones, return_internal_reference<>() ))
  .add_property("weightingFactor", &Accion::getWeightingFactor, &Accion::setWeightingFactor)
  .def("getNombreExpandido", &Accion::GetNombreExpandido)
  .def("getCoeficientes", &Accion::getCoeficientes)
  .def("getDescomp", &Accion::getDescomp);

class_<VRAccion, bases<Accion>, boost::noncopyable >("VRAccion", no_init)
  ;

class_<ListaVRAccion, bases<EntCmd> >("ListaVRAcciones")
  .def("getValue",&ListaVRAccion::GetValor,"Returns action's i value.")
  ;

class_<FamiliaAcciones, bases<EntConNmb> >("FamiliaAcciones")
  .def(init<std::string, GammaF>())
  .add_property("gammaF", make_function( &FamiliaAcciones::getGammaF, return_internal_reference<>() ), &FamiliaAcciones::setGammaF)
  .def("getNumAcciones", &FamiliaAcciones::getNumAcciones)
  .def("insert", make_function(&FamiliaAcciones::inserta,return_internal_reference<>()))
  ;

class_<MapFamiliasAcc, bases<EntConNmb>, boost::noncopyable >("MapFamiliasAcc", no_init)
  ;

class_<AccionesClasificadas, bases<EntCmd> >("AccionesClasificadas")
  .def(init<MapCoefsPsi>())
  .add_property("permanentActions", make_function( &AccionesClasificadas::getAccionesPermanentes, return_internal_reference<>() ), &AccionesClasificadas::setAccionesPermanentes)
  .add_property("ncPermanentActions", make_function( &AccionesClasificadas::getAccionesPermanentesNC, return_internal_reference<>() ), &AccionesClasificadas::setAccionesPermanentesNC)
  .add_property("variableActions", make_function( &AccionesClasificadas::getAccionesVariables, return_internal_reference<>() ), &AccionesClasificadas::setAccionesVariables)
  .add_property("accidentalActions", make_function( &AccionesClasificadas::getAccionesAccidentales, return_internal_reference<>() ), &AccionesClasificadas::setAccionesAccidentales)
  .add_property("seismicActions", make_function( &AccionesClasificadas::getAccionesSismicas, return_internal_reference<>() ), &AccionesClasificadas::setAccionesSismicas)
  .def("getCoefsPsi", &AccionesClasificadas::getCoefsPsi, return_value_policy<copy_const_reference>())
.def("insert", make_function(&AccionesClasificadas::inserta,return_internal_reference<>()))
  ;

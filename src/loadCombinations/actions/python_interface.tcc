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

class_<ActionRelationships, bases<EntCmd> >("ActionRelationships")
  .add_property("no_determinante", &ActionRelationships::NoDeterminante, &ActionRelationships::setNoDeterminante)
  .def("agregaIncompatible", &ActionRelationships::AgregaIncompatible)
  .def("nombresIncompatibles", &ActionRelationships::nombresIncompatibles)
  .def("agregaMaestra", &ActionRelationships::AgregaMaestra)
  .def("nombresMaestras", &ActionRelationships::nombresMaestras);

class_<Action, bases<EntConNmb> >("Action")
  .def(init<std::string, std::string>())
  .add_property("descripcion", make_function( &Action::GetDescripcion, return_value_policy<copy_const_reference>() ), &Action::SetDescripcion)
  .add_property("getRelaciones", make_function( &Action::getRelaciones, return_internal_reference<>() ))
  .add_property("weightingFactor", &Action::getWeightingFactor, &Action::setWeightingFactor)
  .def("getNombreExpandido", &Action::GetNombreExpandido)
  .def("getCoeficientes", &Action::getCoeficientes)
  .def("getDescomp", &Action::getDescomp);

class_<ActionRValue, bases<Action>, boost::noncopyable >("ActionRValue", no_init)
  ;

class_<ActionRValueList, bases<EntCmd> >("ActionRValueListes")
  .def("getValue",&ActionRValueList::GetValor,"Returns action's i value.")
  ;

class_<ActionsFamily, bases<EntConNmb> >("ActionsFamily")
  .def(init<std::string, GammaF>())
  .add_property("gammaF", make_function( &ActionsFamily::getGammaF, return_internal_reference<>() ), &ActionsFamily::setGammaF)
  .def("getNumActions", &ActionsFamily::getNumActions)
  .def("insert", make_function(&ActionsFamily::inserta,return_internal_reference<>()))
  ;

class_<ActionsFamiliesMap, bases<EntConNmb>, boost::noncopyable >("ActionsFamiliesMap", no_init)
  ;

class_<ActionContainer, bases<EntCmd> >("ActionContainer")
  .def(init<PsiCoeffsMap>())
  .add_property("permanentActions", make_function( &ActionContainer::getPermanentActions, return_internal_reference<>() ), &ActionContainer::setPermanentActions)
  .add_property("ncPermanentActions", make_function( &ActionContainer::getPermanentActionsNC, return_internal_reference<>() ), &ActionContainer::setPermanentActionsNC)
  .add_property("variableActions", make_function( &ActionContainer::getVariableActions, return_internal_reference<>() ), &ActionContainer::setVariableActions)
  .add_property("accidentalActions", make_function( &ActionContainer::getAccidentalActions, return_internal_reference<>() ), &ActionContainer::setAccidentalActions)
  .add_property("seismicActions", make_function( &ActionContainer::getSeismicActions, return_internal_reference<>() ), &ActionContainer::setSeismicActions)
  .def("getPsiCoeffs", &ActionContainer::getPsiCoeffs, return_value_policy<copy_const_reference>())
.def("insert", make_function(&ActionContainer::inserta,return_internal_reference<>()))
  ;
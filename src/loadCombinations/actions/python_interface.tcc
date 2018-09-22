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

class_<ActionRelationships, bases<CommandEntity> >("ActionRelationships")
  .add_property("no_determinante", &ActionRelationships::NoDeterminante, &ActionRelationships::setNoDeterminante)
  .def("agregaIncompatible", &ActionRelationships::AgregaIncompatible)
  .def("nombresIncompatibles", &ActionRelationships::nombresIncompatibles)
  .def("agregaMaestra", &ActionRelationships::AgregaMaestra)
  .def("nombresMaestras", &ActionRelationships::nombresMaestras);

class_<Action, bases<NamedEntity> >("Action")
  .def(init<std::string, std::string>())
  .add_property("descripcion", make_function( &Action::GetDescripcion, return_value_policy<copy_const_reference>() ), &Action::SetDescripcion)
  .add_property("getRelaciones", make_function( &Action::getRelaciones, return_internal_reference<>() ))
  .add_property("weightingFactor", &Action::getWeightingFactor, &Action::setWeightingFactor)
  .def("getNombreExpandido", &Action::GetNombreExpandido)
  .def("getCoeficientes", &Action::getCoeficientes)
  .def("getDescomp", &Action::getDescomp)
  .def(self_ns::str(self_ns::self))
  ;

class_<ActionRValue, bases<Action>, boost::noncopyable >("ActionRValue", no_init)
  .def("getPartialSafetyFactors", make_function( &ActionRValue::getPartialSafetyFactors, return_internal_reference<>() ), "Return the partial safety factors for this action.")
  .def("setPartialSafetyFactors", &ActionRValue::setPartialSafetyFactors, "Set the partial safety factors for this action.")
  ;

typedef std::deque<ActionRValue> dq_action_r_value;
class_<dq_action_r_value >("dq_action_r_values")
  .def(vector_indexing_suite<dq_action_r_value>())
  ;

class_<ActionRValueList, bases<dq_action_r_value,CommandEntity> >("ActionRValueLists")
  .def(self_ns::str(self_ns::self))
  ;

const ActionRValueList &(ActionsFamily::*getFamilyActions)(void) const= &ActionsFamily::getActions;
class_<ActionsFamily, bases<NamedEntity> >("ActionsFamily")
  .def(init<std::string>())
  .add_property("actions", make_function( getFamilyActions, return_internal_reference<>() ), &ActionsFamily::setActions)
  .def("insert", make_function(&ActionsFamily::insert,return_internal_reference<>()))
  ;

class_<ActionContainer, bases<CommandEntity> >("ActionContainer")
  .add_property("permanentActions", make_function( &ActionContainer::getPermanentActions, return_internal_reference<>() ), &ActionContainer::setPermanentActions)
  .add_property("ncPermanentActions", make_function( &ActionContainer::getPermanentActionsNC, return_internal_reference<>() ), &ActionContainer::setPermanentActionsNC,"return a reference to the families of non-constant permanent actions container.")
  .add_property("variableActions", make_function( &ActionContainer::getVariableActions, return_internal_reference<>() ), &ActionContainer::setVariableActions,"return a reference to the families of variable actions container.")
  .add_property("accidentalActions", make_function( &ActionContainer::getAccidentalActions, return_internal_reference<>() ), &ActionContainer::setAccidentalActions)
  .add_property("seismicActions", make_function( &ActionContainer::getSeismicActions, return_internal_reference<>() ), &ActionContainer::setSeismicActions)
  .def("insert", make_function(&ActionContainer::insert,return_internal_reference<>()))
  ;

class_<ActionsAndFactors, bases<ActionContainer> >("ActionsAndFactors")
  .def(init<Factors>())
  .def("getFactors", &ActionsAndFactors::getFactors, return_internal_reference<>())
  ;

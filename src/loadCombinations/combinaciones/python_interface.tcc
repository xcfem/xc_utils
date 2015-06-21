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

typedef std::vector<Accion> v_accion;
class_<v_accion >("v_accion")
  .def(vector_indexing_suite<v_accion >())
 ;

class_<VectorCombinaciones, bases<v_accion,EntCmd> >("LoadCombContainer")
  ;

class_<Combinaciones, bases<EntCmd> >("Combinations")
  .add_property("getULSTransientCombinations", &Combinaciones::getULSTransientCombinations)
  .add_property("getULSAccidentalCombinations", &Combinaciones::getULSAccidentalCombinations)
  .add_property("getULSSeismicCombinations", &Combinaciones::getULSSeismicCombinations)

  .add_property("getSLSCharacteristicCombinations", &Combinaciones::getSLSCharacteristicCombinations)
  .add_property("getSLSFrequentCombinations", &Combinaciones::getSLSFrequentCombinations)
  .add_property("getSLSQuasiPermanentCombinations", &Combinaciones::getSLSQuasiPermanentCombinations)
;


class_<GeneradorCombinaciones, bases<EntCmd> >("LoadCombGenerator")
  .add_property("pondAcciones", make_function( &GeneradorCombinaciones::getPondAcciones, return_internal_reference<>() ), &GeneradorCombinaciones::setPondAcciones)
  .def("defPonderacion", make_function(&GeneradorCombinaciones::defPonderacion,return_internal_reference<>()))
  .def("insert", make_function(&GeneradorCombinaciones::inserta,return_internal_reference<>()))
  .def("genera", &GeneradorCombinaciones::genera)
  .add_property("getLoadCombinations", make_function(&GeneradorCombinaciones::getLoadCombinations,return_internal_reference<>()))
  ;

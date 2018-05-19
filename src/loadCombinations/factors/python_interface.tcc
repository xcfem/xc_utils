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

class_<cmb_acc::SLSPartialSafetyFactors, bases<EntCmd> >("SLSPartialSafetyFactors")
  .def(init<float, float>())
  .add_property("favorable", &cmb_acc::SLSPartialSafetyFactors::getFavorable, &cmb_acc::SLSPartialSafetyFactors::setFavorable)
  .add_property("desfavorable", &cmb_acc::SLSPartialSafetyFactors::getDesfavorable, &cmb_acc::SLSPartialSafetyFactors::setDesfavorable)
  .def(self_ns::str(self_ns::self))
  ;

class_<ULSPartialSafetyFactors, bases<SLSPartialSafetyFactors> >("ULSPartialSafetyFactors")
  .def(init<float, float,float,float>())
  .add_property("favorableAccidental", &ULSPartialSafetyFactors::getFavorableAccidental, &ULSPartialSafetyFactors::setFavorableAccidental)
  .add_property("desfavorableAccidental", &ULSPartialSafetyFactors::getDesfavorableAccidental, &ULSPartialSafetyFactors::setDesfavorableAccidental);

class_<PartialSafetyFactors, bases<EntCmd> >("PartialSafetyFactors")
  .def(init<ULSPartialSafetyFactors, SLSPartialSafetyFactors>())
  .add_property("getULSPartialSafetyFactors", make_function( &PartialSafetyFactors::getULSPartialSafetyFactors, return_internal_reference<>() ))
  .add_property("getSLSPartialSafetyFactors", make_function( &PartialSafetyFactors::getSLSPartialSafetyFactors, return_internal_reference<>() ))
  .def(self_ns::str(self_ns::self))
  ;

class_<PartialSafetyFactorsMap, bases<EntCmd> >("PartialSafetyFactorsDict")
  .def("get", &PartialSafetyFactorsMap::BuscaCoefs, return_value_policy<copy_const_reference>())
  .def("insert", &PartialSafetyFactorsMap::insert);


class_<CombinationFactors, bases<EntCmd> >("CombinationFactors")
  .def(init<double, double, double>())
.def("getCombinationFactor", &CombinationFactors::getCombinationFactor, return_value_policy<copy_const_reference>(),"Return the r-th combination factor.");

class_<CombinationFactorsMap, bases<EntCmd> >("CombinationFactorsDict")
  .def("get", &CombinationFactorsMap::BuscaCoefs, return_value_policy<copy_const_reference>())
  .def("insert", &CombinationFactorsMap::insert);

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

class_<cmb_acc::GammaFSLS, bases<EntCmd> >("GammaFSLS")
  .def(init<float, float>())
  .add_property("favorable", &cmb_acc::GammaFSLS::getFavorable, &cmb_acc::GammaFSLS::setFavorable)
  .add_property("desfavorable", &cmb_acc::GammaFSLS::getDesfavorable, &cmb_acc::GammaFSLS::setDesfavorable)
  .def(self_ns::str(self_ns::self))
  ;

class_<GammaFULS, bases<GammaFSLS> >("GammaFULS")
  .def(init<float, float,float,float>())
  .add_property("favorableAccidental", &GammaFULS::getFavorableAccidental, &GammaFULS::setFavorableAccidental)
  .add_property("desfavorableAccidental", &GammaFULS::getDesfavorableAccidental, &GammaFULS::setDesfavorableAccidental);

class_<GammaF, bases<EntCmd> >("GammaF")
  .def(init<GammaFULS, GammaFSLS>())
  .add_property("getGammaFULS", make_function( &GammaF::getGammaFULS, return_internal_reference<>() ))
  .add_property("getGammaFSLS", make_function( &GammaF::getGammaFSLS, return_internal_reference<>() ))
  .def(self_ns::str(self_ns::self))
  ;

class_<CombinationFactors, bases<EntCmd> >("CombinationFactors")
  .def(init<double, double, double>())
.def("getCombinationFactor", &CombinationFactors::getCombinationFactor, return_value_policy<copy_const_reference>(),"Return the r-th combination factor.");

class_<CombinationFactorsMap, bases<EntCmd> >("CombinationFactorsDict")
  .def("get", &CombinationFactorsMap::BuscaCoefs, return_value_policy<copy_const_reference>())
  .def("insert", &CombinationFactorsMap::insert);

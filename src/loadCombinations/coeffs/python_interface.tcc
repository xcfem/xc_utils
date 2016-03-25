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

class_<cmb_acc::GammaFELS, bases<EntCmd> >("GammaFELS")
  .def(init<float, float>())
  .add_property("favorable", &cmb_acc::GammaFELS::getFavorable, &cmb_acc::GammaFELS::setFavorable)
  .add_property("desfavorable", &cmb_acc::GammaFELS::getDesfavorable, &cmb_acc::GammaFELS::setDesfavorable);

class_<GammaFELU, bases<GammaFELS> >("GammaFELU")
  .def(init<float, float,float,float>())
  .add_property("favorableAccidental", &GammaFELU::getFavorableAccidental, &GammaFELU::setFavorableAccidental)
  .add_property("desfavorableAccidental", &GammaFELU::getDesfavorableAccidental, &GammaFELU::setDesfavorableAccidental);

class_<GammaF, bases<EntCmd> >("GammaF")
  .def(init<GammaFELU, GammaFELS>())
  .add_property("getGammaFELU", make_function( &GammaF::getGammaFELU, return_internal_reference<>() ))
  .add_property("getGammaFELS", make_function( &GammaF::getGammaFELS, return_internal_reference<>() ));

class_<PsiCoeffs, bases<EntCmd> >("PsiCoeffs")
  .def(init<double, double, double>())
  .def("getPsi", &PsiCoeffs::getPsi, return_value_policy<copy_const_reference>());

class_<PsiCoeffsMap, bases<EntCmd> >("PsiCoeffsDict")
  .def("get", &PsiCoeffsMap::BuscaCoefs, return_value_policy<copy_const_reference>())
  .def("insert", &PsiCoeffsMap::insert);

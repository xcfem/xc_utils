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

class_<FuncPorPuntosR_R >("FunctionGraph1D")
  .def("__call__", &FuncPorPuntosR_R::Valor)
  .def("size", &FuncPorPuntosR_R::size)
  .def("empty", &FuncPorPuntosR_R::empty)
  .def("append", &FuncPorPuntosR_R::Inserta)
  .def("clear", &FuncPorPuntosR_R::clear)
  .def("Max", &FuncPorPuntosR_R::Max)
  .def("AbcisaMax", &FuncPorPuntosR_R::AbcisaMax)
  .def("Min", &FuncPorPuntosR_R::Min)
  .def("AbcisaMin", &FuncPorPuntosR_R::AbcisaMin)
  .def("Area", &FuncPorPuntosR_R::Area)
  .def("firstX", &FuncPorPuntosR_R::firstX)
  .def("firstY", &FuncPorPuntosR_R::firstY)
  .def("lastX", &FuncPorPuntosR_R::lastX)
  .def("lastY", &FuncPorPuntosR_R::lastY)
  .def("sub", &FuncPorPuntosR_R::sub)
  .def("getNeg", &FuncPorPuntosR_R::getNeg)
  .def(self * double())
  .def(double() * self)
  .def(self / double())
  .def(self + self)
  .def(self - self)
  .def(self *= self)
  .def(self += double())
  .def(self += self)
  .def(self -= double())
  .def(self -= self)
  .def(self *= double())
  .def(self /= double())
  .def(self /= self)
  .def("integra", &FuncPorPuntosR_R::integra)
  ;

class_<FuncPorPuntosR2_R >("FunctionGraph2D")
  ;

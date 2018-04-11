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

class_<FunctionFromPointsR_R >("FunctionGraph1D")
  .def("__call__", &FunctionFromPointsR_R::Valor)
  .def("size", &FunctionFromPointsR_R::size)
  .def("empty", &FunctionFromPointsR_R::empty)
  .def("append", &FunctionFromPointsR_R::insert)
  .def("clear", &FunctionFromPointsR_R::clear)
  .def("Max", &FunctionFromPointsR_R::Max)
  .def("AbcisaMax", &FunctionFromPointsR_R::AbcisaMax)
  .def("Min", &FunctionFromPointsR_R::Min)
  .def("AbcisaMin", &FunctionFromPointsR_R::AbcisaMin)
  .def("Area", &FunctionFromPointsR_R::Area)
  .def("firstX", &FunctionFromPointsR_R::firstX)
  .def("firstY", &FunctionFromPointsR_R::firstY)
  .def("lastX", &FunctionFromPointsR_R::lastX)
  .def("lastY", &FunctionFromPointsR_R::lastY)
  .def("sub", &FunctionFromPointsR_R::sub)
  .def("getNeg", &FunctionFromPointsR_R::getNeg)
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
  .def("integra", &FunctionFromPointsR_R::integra)
  ;

class_<FunctionFromPointsR2_R >("FunctionGraph2D")
  ;

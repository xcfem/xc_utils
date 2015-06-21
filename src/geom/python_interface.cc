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

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/docstring_options.hpp>
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos3d.h"
#include "xc_utils/src/geom/pos_vec/TritrizPos2d.h"
#include "xc_utils/src/geom/pos_vec/TritrizPos3d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d1/func_por_puntos/FuncPorPuntosR_R.h"
#include "xc_utils/src/geom/d1/func_por_puntos/FuncPorPuntosR2_R.h"
#include "xc_utils/src/geom/d2/Superficie2d.h"
#include "xc_utils/src/geom/d2/Semiplano2d.h"
#include "xc_utils/src/geom/d2/Circulo2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/SupPoligonal2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Triangulo2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Cuadrado2d.h"
#include "xc_utils/src/geom/d1/Polilinea2d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/PoligonoConAgujeros2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/bool_op_poligono2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/geom/pos_vec/VDesliz2d.h"
#include "xc_utils/src/geom/pos_vec/VDesliz3d.h"
#include "xc_utils/src/geom/d1/SemiRecta2d.h"
#include "xc_utils/src/geom/d1/SemiRecta3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos3d.h"
#include "xc_utils/src/geom/d1/Polilinea3d.h"
//#include "xc_utils/src/geom/d3/Solido3d.h"
#include "xc_utils/src/geom/d2/Superficie3d.h"
#include "xc_utils/src/geom/d2/EcuacionGeneralPlano3d.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Cuadrilatero2d.h"
#include "xc_utils/src/geom/d2/Rejilla2d.h"
#include "xc_utils/src/geom/pos_vec/SVD2d.h"
#include "xc_utils/src/geom/pos_vec/SVD3d.h"
#include "xc_utils/src/geom/sis_ref/EjesPrincInercia2d.h"
#include "xc_utils/src/geom/sis_ref/Ref1d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref1d2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/sis_ref/Ref3d3d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/geom/trf/Escalado2d.h"
#include "xc_utils/src/geom/trf/Escalado3d.h"
#include "xc_utils/src/geom/trf/Identidad2d.h"
#include "xc_utils/src/geom/trf/Identidad3d.h"
#include "xc_utils/src/geom/trf/Reflexion2d.h"
#include "xc_utils/src/geom/trf/Reflexion3d.h"
#include "xc_utils/src/geom/trf/Revolucion3d.h"
#include "xc_utils/src/geom/trf/Rotacion2d.h"
#include "xc_utils/src/geom/trf/Rotacion3d.h"
#include "xc_utils/src/geom/trf/Traslacion2d.h"
#include "xc_utils/src/geom/trf/Traslacion3d.h"

std::list<Poligono2d> from_python_list(boost::python::list &l)
  {
    std::list<Poligono2d> retval;
    const size_t sz= len(l);
    for(size_t i= 0;i<sz;++i)
      retval.push_back(boost::python::extract<Poligono2d>(l[i]));
    return retval;
  }

boost::python::list to_python_list(const std::list<Poligono2d> &l)
  {
    boost::python::list retval;
    BOOST_FOREACH(const Poligono2d& p, l) retval.append(p);
    return retval;
  }

//! @brief Devuelve el resultado de repartir el área común entre los 
//! polígonos de la lista mediante la técnica de Voronoi.
boost::python::list python_particiona(boost::python::list &l)
  {
    std::list<Poligono2d> areas= from_python_list(l);
    particiona(areas);
    return to_python_list(areas);
  }

//! @brief Devuelve el resultado de recortar los 
//! polígonos de la lista mediante la técnica de Voronoi.
boost::python::list python_recorta(boost::python::list &l, const Poligono2d &plg)
  {
    std::list<Poligono2d> areas= from_python_list(l);
    areas= recorta(areas,plg);
    return to_python_list(areas);
  }

BOOST_PYTHON_MODULE(geom)
  {
    using namespace boost::python;
    docstring_options doc_options;

    class_<std::vector<double> >("StdVectorDouble")
      .def(vector_indexing_suite<std::vector<double> >() );

    class_<ProtoGeom, bases<EntCmd> >("ProtoGeom");

    class_<GeomObj, bases<ProtoGeom>, boost::noncopyable >("GeomObj", no_init)
      .def("getLongitud", pure_virtual(&GeomObj::Longitud))
      .def("getArea", pure_virtual(&GeomObj::Area))
      .def("getVolumen", pure_virtual(&GeomObj::Volumen))
      .def("getDimension", pure_virtual(&GeomObj::Dimension))
      .def(self_ns::str(self_ns::self));

    class_<GeomObj2d, bases<GeomObj>, boost::noncopyable >("GeomObj2d", no_init)
      .def("getIx", pure_virtual(&GeomObj2d::Ix))
      .def("getIy", pure_virtual(&GeomObj2d::Iy))
      .def("getIz", &GeomObj2d::Iz)
      .def("getPxy", pure_virtual(&GeomObj2d::Pxy))
      .def("mueve",&GeomObj2d::Mueve)
      .def("In",&GeomObj2d::In)
      ;

    class_<GeomObj3d, bases<GeomObj>, boost::noncopyable >("GeomObj3d", no_init)
      .def("getIx", pure_virtual(&GeomObj3d::Ix))
      .def("getIy", pure_virtual(&GeomObj3d::Iy))
      .def("getIz", &GeomObj3d::Iz)
      .def("getPxy", pure_virtual(&GeomObj3d::Pxy)) 
      .def("getPxz", pure_virtual(&GeomObj3d::Pxz)) 
      .def("getPyz", pure_virtual(&GeomObj3d::Pyz));

    #include "listas/python_interface.tcc"
    #include "pos_vec/python_interface.tcc"
    #include "d1/python_interface.tcc"



    double (SemiEspacio3d::*AnguloConSemiEspacio3d)(const SemiEspacio3d &) const= &SemiEspacio3d::getAngulo;
    double (SemiEspacio3d::*AnguloConPlano3d)(const Plano3d &) const= &SemiEspacio3d::getAngulo;
    double (SemiEspacio3d::*AnguloConVector3d)(const Vector3d &) const= &SemiEspacio3d::getAngulo;

    class_<SemiEspacio3d, bases<GeomObj3d> >("SemiEspacio3d")
      .def(init<Plano3d>())
      .def(init<SemiEspacio3d>())
      .def("anguloConSemiEspacio3d", AnguloConSemiEspacio3d)
      .def("anguloConPlano3d", AnguloConPlano3d)
      .def("anguloConVector3d", AnguloConVector3d)
      .def("getLima", &SemiEspacio3d::getLima)
      .def("getNormalExterior", &SemiEspacio3d::NormalExterior)
      .def("getNormalInterior", &SemiEspacio3d::NormalInterior)
      .def("getPlanoLimite", &SemiEspacio3d::getPlanoLimite,return_internal_reference<>() );

#include "d2/python_interface.tcc"
#include "trf/python_interface.tcc"
#include "sis_coo/python_interface.tcc"
#include "sis_ref/python_interface.tcc"

}


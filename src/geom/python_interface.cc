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

#include "python_interface.h"

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

void export_d1_entities(void);
void export_d2_entities(void);
void export_sys_trf(void);

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
      .def("getMax",&GeomObj2d::GetMax)
      .def("getMin",&GeomObj2d::GetMin)
      .add_property("getXMax",&GeomObj2d::GetXMax, "Returns maximum value for x coordinate.")
      .add_property("getYMax",&GeomObj2d::GetYMax, "Returns maximum value for y coordinate.")
      .add_property("getXMin",&GeomObj2d::GetXMin, "Returns minimum value for x coordinate.")
      .add_property("getYMin",&GeomObj2d::GetYMin, "Returns minimum value for y coordinate.")
      .def("getIx", pure_virtual(&GeomObj2d::Ix))
      .def("getIy", pure_virtual(&GeomObj2d::Iy))
      .def("getIz", &GeomObj2d::Iz)
      .def("getPxy", pure_virtual(&GeomObj2d::Pxy))
      .def("mueve",&GeomObj2d::Mueve)
      .def("In",&GeomObj2d::In)
      ;

    class_<GeomObj3d, bases<GeomObj>, boost::noncopyable >("GeomObj3d", no_init)
      .def("getMax",&GeomObj3d::GetMax)
      .def("getMin",&GeomObj3d::GetMin)
      .def("getIx", pure_virtual(&GeomObj3d::Ix))
      .def("getIy", pure_virtual(&GeomObj3d::Iy))
      .def("getIz", &GeomObj3d::Iz)
      .def("getPxy", pure_virtual(&GeomObj3d::Pxy)) 
      .def("getPxz", pure_virtual(&GeomObj3d::Pxz)) 
      .def("getPyz", pure_virtual(&GeomObj3d::Pyz));

    #include "listas/python_interface.tcc"
    #include "pos_vec/python_interface.tcc"

    export_d1_entities();
    export_d2_entities();


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

    export_sys_trf();
  }


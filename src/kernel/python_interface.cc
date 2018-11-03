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

#include "python_utils.h"
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include "xc_utils/src/kernel/CommandEntity.h"
#include "xc_utils/src/kernel/NamedEntity.h"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "xc_utils/src/matrices/ProtoMatrix.h"

BOOST_PYTHON_MODULE(xc_base)
  {
    using namespace boost::python;
    docstring_options doc_options;

    typedef std::vector<int> std_vector_int;
    class_<std_vector_int>("std_vector_int")
      .def(vector_indexing_suite<std_vector_int>() );

    typedef std::vector<std::string> std_vector_string;
    class_<std_vector_string>("std_vector_string")
      .def(vector_indexing_suite<std_vector_string>() );

    def("vector_int_to_py_list",vector_int_to_py_list);
    def("vector_double_to_py_list",vector_double_to_py_list);
    def("vector_string_from_py_list",vector_string_from_py_list);

    def("mseImages",mseImages);
    def("psnrImagenes",psnrImagenes);
    def("compare_images",compare_images);

    typedef std::set<int> set_ints;
    class_<set_ints>("setInts")
      .def("__iter__", iterator<set_ints>())
      .add_property("size", &set_ints::size)
      .def("__len__", &set_ints::size)
      .def("empty", &set_ints::empty)
      // .def("__contains__", &set_ints::contains)
      // .def("count", &set_ints::count)
       ;

    const EntityWithProperties *(EntityWithProperties::*getOwner)(void) const= &EntityWithProperties::Owner;
    class_<EntityWithProperties,EntityWithProperties *, boost::noncopyable  >("EntityWithProperties", no_init)
      .add_property("owner", make_function( getOwner, return_internal_reference<>() ), "returns object's owner (container).")
      .def("setVerbosityLevel", &EntityWithProperties::setVerbosityLevel,"Set verbosity level.")
        .staticmethod("setVerbosityLevel")
      // .def("getVerbosityLevel", make_function(&EntityWithProperties::getVerbosityLevel, return_internal_reference<>() ),"Get verbosity level.")
      //   .staticmethod("getVerbosityLevel")
      ;

    class_<CommandEntity, bases<EntityWithProperties> >("CommandEntity")
      .add_property("logFileName", make_function( &CommandEntity::getLogFileName, return_internal_reference<>() ), &CommandEntity::setLogFileName)
      .add_property("errFileName", make_function( &CommandEntity::getErrFileName, return_internal_reference<>() ), &CommandEntity::setErrFileName)
      .def("hasProp", &CommandEntity::hasPyProp,"True if property exists.")
      .def("getProp", &CommandEntity::getPyProp,"Return a user defined property.")
      .def("setProp", &CommandEntity::setPyProp,"Sets the value of a user defined property.")
      .def("evalPy", &CommandEntity_eval,"Evaluates expresion.")
      .def("execPy", &CommandEntity_exec,"Executes code block.")
      .def("execFilePy", &CommandEntity_exec_file,"Executes code block.")
      .def("tipo", &CommandEntity::getClassName,"DEPRECATED Return the class name.")
      .def("type", &CommandEntity::getClassName,"Returns class name.")
  ;

    class_<NamedEntity, bases<CommandEntity> >("NamedEntity")
      .add_property("nombre", make_function( &NamedEntity::getName, return_value_policy<copy_const_reference>()), &NamedEntity::setName,"DEPRECATED returns object name.")
      .add_property("name", make_function( &NamedEntity::getName, return_value_policy<copy_const_reference>()), &NamedEntity::setName,"returns object name.")
      ;

    class_<ProtoMatrix, boost::noncopyable>("ProtoMatrix", no_init)
      .add_property("nRow",&ProtoMatrix::getNumberOfRows,"returns number of rows.")
      .add_property("nCol",&ProtoMatrix::getNumberOfColumns,"returns number of columns.")
      ;
  }


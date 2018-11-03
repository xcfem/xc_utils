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
//CommandEntity.cxx

#include "CommandEntity.h"
#include <boost/tokenizer.hpp>
#include "xc_utils/src/matrices/RangoIndice.h"
#include <typeinfo>
#include <stack>
#include <map>
#include <cmath>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <limits>
#include <cstdlib>

//Variables estáticas de CommandEntity.
ErrLogFiles CommandEntity::err_log_files; //!< Streams para errores y avisos.

//! @brief Default constructor.
CommandEntity::CommandEntity(CommandEntity *owr)
  : EntityWithProperties(owr) {}

//! @brief Return un puntero al objeto propietario de ESTE.
CommandEntity *CommandEntity::Owner(void)
  {
    CommandEntity *retval= nullptr;
    EntityWithProperties *tmp= EntityWithProperties::Owner();
    if(tmp)
      retval= dynamic_cast<CommandEntity *>(tmp);
    return retval;
  }

//! @brief Return un puntero al objeto propietario de ESTE.
const CommandEntity *CommandEntity::Owner(void) const
  {
    const CommandEntity *retval= nullptr;
    const EntityWithProperties *tmp= EntityWithProperties::Owner();
    if(tmp)
      retval= dynamic_cast<const CommandEntity *>(tmp);
    return retval;
  }

//! @brief Returns log file name.
const std::string &CommandEntity::getLogFileName(void) const
  { return err_log_files.getLogFileName(); }

//! @brief Sets log file name.
void CommandEntity::setLogFileName(const std::string &fname)
  {
    if(fname != "")
      err_log_files.setLogFileName(fname);
  }

//! @brief Returns err file name.
const std::string &CommandEntity::getErrFileName(void) const
  { return err_log_files.getErrFileName(); }

//! @brief Sets log file name.
void CommandEntity::setErrFileName(const std::string &fname)
  {
    if(fname != "")
      err_log_files.setErrFileName(fname);
  }

//! @brief Clear python properties map.
void CommandEntity::clearPyProps(void)
  { python_dict.clear(); }

//! @brief Returns true if property exists.
bool CommandEntity::hasPyProp(const std::string &str)
  { return (python_dict.find(str) != python_dict.end()); }

//! @brief Return el objeto de Python cuyo nombre se pasa como parámetro.
boost::python::object CommandEntity::getPyProp(const std::string &str)
   {
     // Python checks the class attributes before it calls __getattr__
     // so we don't have to do anything special here.
     if(python_dict.find(str) == python_dict.end())
       {
         std::cerr << getClassName() << "::" << __FUNCTION__
	           << "; property: '" << str << "' not found."
		   << std::endl;
         PyErr_SetString(PyExc_AttributeError, str.c_str());
         throw boost::python::error_already_set();
       }
     return python_dict[str];
   }

//! @brief Sets/appends a value tho the Python object's dictionary.
// However, with __setattr__, python doesn't do anything with the class attributes first,
// it just calls __setattr__.
// Which means anything that's been defined as a class attribute won't be modified
// here - including things set with
//add_property(), def_readwrite(), etc.
void CommandEntity::setPyProp(std::string str, boost::python::object val)
  {
    python_dict[str] = val;
  }

//! @brief Return the Python object that results from evaluating the argument.
boost::python::object CommandEntity::evalPy(boost::python::object dict,const std::string &str)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::eval(str.c_str(),main_namespace,dict);
   }


//! @brief Return the Python objects that results from executing the code in the string argument.
boost::python::object CommandEntity::execPy(boost::python::object dict,const std::string &block)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::exec(block.c_str(),main_namespace,dict);
   }

//! @brief Return the Python object that results from executing the code in the file.
boost::python::object CommandEntity::execFilePy(boost::python::object dict,const std::string &fName)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::exec_file(fName.c_str(),main_namespace,dict);
   }

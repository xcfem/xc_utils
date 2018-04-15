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
//EntCmd.cxx

#include "EntCmd.h"
#include <boost/tokenizer.hpp>
#include "xc_basic/src/matrices/RangoIndice.h"
#include <typeinfo>
#include <stack>
#include <map>
#include <cmath>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <limits>
#include <cstdlib>

//Variables estáticas de EntCmd.
ErrLogFiles EntCmd::err_log_files; //!< Streams para errores y avisos.

//! @brief Constructor por defecto.
EntCmd::EntCmd(EntCmd *owr)
  : EntProp(owr) {}

//! @brief Return un puntero al objeto propietario de ESTE.
EntCmd *EntCmd::Owner(void)
  {
    EntCmd *retval= nullptr;
    EntProp *tmp= EntProp::Owner();
    if(tmp)
      retval= dynamic_cast<EntCmd *>(tmp);
    return retval;
  }

//! @brief Return un puntero al objeto propietario de ESTE.
const EntCmd *EntCmd::Owner(void) const
  {
    const EntCmd *retval= nullptr;
    const EntProp *tmp= EntProp::Owner();
    if(tmp)
      retval= dynamic_cast<const EntCmd *>(tmp);
    return retval;
  }

//! @brief Returns log file name.
const std::string &EntCmd::getLogFileName(void) const
  { return err_log_files.getLogFileName(); }

//! @brief Sets log file name.
void EntCmd::setLogFileName(const std::string &fname)
  {
    if(fname != "")
      err_log_files.setLogFileName(fname);
  }

//! @brief Returns err file name.
const std::string &EntCmd::getErrFileName(void) const
  { return err_log_files.getErrFileName(); }

//! @brief Sets log file name.
void EntCmd::setErrFileName(const std::string &fname)
  {
    if(fname != "")
      err_log_files.setErrFileName(fname);
  }

//! @brief Clear python properties map.
void EntCmd::clearPyProps(void)
  { python_dict.clear(); }

//! @brief Returns true if property exists.
bool EntCmd::hasPyProp(const std::string &str)
  { return (python_dict.find(str) != python_dict.end()); }

//! @brief Return el objeto de Python cuyo nombre se pasa como parámetro.
//Python checks the class attributes before it calls __getattr__ so we don't have to do anything special here.
boost::python::object EntCmd::getPyProp(const std::string &str)
   {
     if(python_dict.find(str) == python_dict.end())
       {
         std::cerr << "No se encontró la propiedad: '" << str << "'" << std::endl;
         PyErr_SetString(PyExc_AttributeError, str.c_str());
         throw boost::python::error_already_set();
       }
     return python_dict[str];
   }

//! @brief Asigna al objeto de Python cuyo nombre se pasa como parámetro el valor «val».
//However, with __setattr__, python doesn't do anything with the class attributes first, it just calls __setattr__.
//Which means anything that's been defined as a class attribute won't be modified here - including things set with
//add_property(), def_readwrite(), etc.
void EntCmd::setPyProp(std::string str, boost::python::object val)
  {
    python_dict[str] = val;
  }

//! @brief Return el objeto de Python que resulta de evaluar la expresión.
boost::python::object EntCmd::evalPy(boost::python::object dict,const std::string &str)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::eval(str.c_str(),main_namespace,dict);
   }


//! @brief Return el objeto de Python que resulta de evaluar el bloque de código.
boost::python::object EntCmd::execPy(boost::python::object dict,const std::string &block)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::exec(block.c_str(),main_namespace,dict);
   }

//! @brief Return el objeto de Python que resulta de evaluar el bloque de código.
boost::python::object EntCmd::execFilePy(boost::python::object dict,const std::string &fName)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::exec_file(fName.c_str(),main_namespace,dict);
   }

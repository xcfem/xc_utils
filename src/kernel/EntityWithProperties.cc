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
//EntityWithProperties.cc

#include "EntityWithProperties.h"
#include <fstream>
#include <iostream>
#include "xc_basic/src/util/memoria.h"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "boost/algorithm/string.hpp"
#include <cxxabi.h>
#include <sys/stat.h>

#include <cctype>
#include "CImg.h"

//Variables estáticas de EntityWithProperties.
int EntityWithProperties::verbosity= 1;

//! @brief Default constructor.
EntityWithProperties::EntityWithProperties(EntityWithProperties *owr)
  : owner(owr)
  {
    if(this == owner)
      std::cerr << getClassName() << "::" << __FUNCTION__
                << "; ¡ojo!, object is owner of itself." << std::endl;
  }

//! @brief Copy constructor
EntityWithProperties::EntityWithProperties(const EntityWithProperties &other)
  : owner(other.owner)
  {
    if(this == owner)
      std::cerr << getClassName() << "::" << __FUNCTION__
                << "; ¡ojo!, object is owner of itself." << std::endl;
  }

//! @brief Assignment operator.
EntityWithProperties &EntityWithProperties::operator=(const EntityWithProperties &other)
  {
    owner= other.owner;
    if(this == owner)
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; ¡ojo!, objeto of class: '"
		  << getClassName() 
                  << "', owns itself." << std::endl;
        owner= nullptr;
      }
    return *this;
  }

//! @brief Returns demangled class name.
std::string EntityWithProperties::getClassName(void) const
  {
    std::string tmp= typeid(*this).name();
    std::bad_exception  e;
    int status;
    char *realname= abi::__cxa_demangle(tmp.c_str(), 0, 0, &status);
    if(realname)
      tmp= std::string(realname);
    free(realname);
    return tmp;
  }

//! @brief Get the value of the verbosity level.
const int &EntityWithProperties::getVerbosityLevel(void)
  { return verbosity; }

//! @brief Set the value of the verbosity level.
void EntityWithProperties::setVerbosityLevel(const int &vl)
  { verbosity= vl; }

//! @brief Asigna el propietario del objeto.
void EntityWithProperties::set_owner(EntityWithProperties *owr)
  { owner= owr; }


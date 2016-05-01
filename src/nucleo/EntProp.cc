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
//EntProp.cc

#include "EntProp.h"
#include <fstream>
#include <iostream>
#include "xc_basic/src/util/memoria.h"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "boost/algorithm/string.hpp"
#include <cxxabi.h>
#include <sys/stat.h>
#include "boost/regex.hpp"

#include <cctype>
#include "CImg.h"

//Variables estáticas de EntProp.
int EntProp::verborrea= 0;

//! @brief Constructor por defecto.
EntProp::EntProp(EntProp *owr)
  : owner(owr)
  {
    if(this == owner)
      std::cerr << "EntProp constructor por defecto; ¡ojo!, objeto de clase: '" 
                << nombre_clase() << "', propietario de sí mismo." << std::endl;
  }

//! @brief Constructor de copia.
EntProp::EntProp(const EntProp &otro)
  : owner(otro.owner)
  {
    if(this == owner)
      std::cerr << "EntProp constructor de copia; ¡ojo!, objeto de clase: '"
                << nombre_clase() << "', propietario de sí mismo." << std::endl;
  }

//! @brief Operador asignación.
EntProp &EntProp::operator=(const EntProp &otro)
  {
    owner= otro.owner;
    if(this == owner)
      {
        std::cerr << "EntProp operador asignación; ¡ojo!, objeto de clase: '" << nombre_clase() 
                  << "', propietario de sí mismo." << std::endl;
        owner= nullptr;
      }
    return *this;
  }

//! @brief Devuelve el nombre de la clase.
std::string EntProp::nombre_clase(void) const
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

//! @brief Devuelve el nivel de verborrea.
const int &EntProp::GetNivelVerborrea(void)
  { return verborrea; }

//! @brief Asigna el propietario del objeto.
void EntProp::set_owner(EntProp *owr)
  { owner= owr; }


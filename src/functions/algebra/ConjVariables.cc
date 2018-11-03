//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//ConjVariables.cc

#include "ConjVariables.h"
#include <iostream>

//! @brief Devuelve verdadero si la variable pertenece al conjunto.
bool ConjVariables::In(const Variable *var) const
  {
    return (find(var)!=end());
  }
//! @brief Devuelve verdadero si la variable pertenece al conjunto.
bool ConjVariables::In(const Variable &var) const
  {
    return (find(&var)!=end());
  }

//! @brief Devuelve los nombres de las variables.
std::vector<std::string> ConjVariables::getNombres(void) const
  {
    std::vector<std::string> retval(size());
    size_t conta= 0;
    for(const_iterator i= begin();i!=end();i++,conta++)
      retval[conta]= (*i)->getName();
    return retval;
  }

std::ostream &operator<<(std::ostream &stream,const ConjVariables &cv)
  { return stream << "operador salida ConjVariables no implementado." << std::endl; }


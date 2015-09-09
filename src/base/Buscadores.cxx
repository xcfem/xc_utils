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
//Buscadores.cxx

#include "Buscadores.hxx"
#include <iostream>

PtrBuscador &Buscadores::operator[](const std::string &str)
  { return std::map<std::string,PtrBuscador>::operator[](str); }

const PtrBuscador &Buscadores::operator[](const std::string &str) const
  {
    if(empty()) return nulo;
    const_iterator i= find(str);
    if(i == end()) return nulo;
    return (*i).second;
  }

Buscadores::Buscadores(void)
  : nulo(NULL) {}

void Buscadores::Print(std::ostream &os) const
  {
    for(const_iterator i=begin();i!=end();i++)
      os << (*i).first << " " << (*i).second << std::endl;
  }


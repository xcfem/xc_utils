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
//Operando.cc

#include "Operando.h"
#include "Rama.h"
#include "Lexico.h"
#include "boost/lexical_cast.hpp"
#include <sstream>

Rama Operando::Diferencia(const Variable &,const Rama &r) const
  {
    std::cerr << "Operando::Diferencia no implementada." << std::endl;
    return Rama();
//     r->Put(Lex().NuevoLiteral(0.0),r->GetIzdo(),r->GetDcho());
//     return r;
  }

//! @brief Simplifica la expresión.
Rama *Operando::Simplifica(Rama *r) const
  { return r; }

//! @brief En su caso, aplica la propiedad distributiva.
Rama *Operando::Distrib(Rama *r) const
  { return r; }

//! @brief Devuelve el nombre del operando.
const std::string &Operando::getName(void) const
  { return GetFullString(); }

//! @brief Devuelve la cadena de caracteres correspondiente al valor
//! con toda la precisión posible.
const std::string &Operando::GetFullString(void) const
  {
    static std::string strNombre= "";
    strNombre= boost::lexical_cast<std::string>(valor);
    return strNombre;
  }


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
//Segnal.cc

#include "Segnal.h"
#include <iostream>

std::ostream &Segnal::Imprime(std::ostream &os) const
  {
    os << getName();
    return os;
  }

const std::string &Segnal::StrClase(void) const
  {
    static std::string s= "";
    switch(GetClase())
      {
        case fin_exp:
          s= "fin_exp";
          break;
        case parent_izdo:
          s= "parent_izdo";
          break;
        case parent_dcho:
          s= "parent_dcho";
          break;
        case operando:
          s= "operando";
          break;
	    case op_unitario:
          s= "op_unitario";
          break;
        case op_binario:
          s= "op_binario";
          break;
	    default:
          s= "desconocida";
      }
    return s;
  }

std::ostream &operator<<(std::ostream &stream, const Segnal &s)
  { return s.Imprime(stream); }

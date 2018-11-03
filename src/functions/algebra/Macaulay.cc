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
//Macaulay.cc
#include "Macaulay.h"
#include "Lexico.h"
#include "boost/lexical_cast.hpp"
#include <cmath>

double OpMacaulay0::get_val(const double &x,const double &a) const
  {
    if(x<=a)
      return 0.0;
    else
      return 1.0;
  }

const Operando &OpMacaulay0::Opera(const Operando *v1,const Operando *v2) const
  {
    const double &x= v1->GetValor();
    const double &a= v2->GetValor();
    return *Lex().NuevoLiteral(get_val(x,a));
  }


OpMacaulayN::OpMacaulayN(size_t n)
  : OpMacaulay0(), N(n), nmbOpMacaulayN("Fmac"+boost::lexical_cast<std::string>(N)) {}

double OpMacaulayN::get_val(const double &x,const double &a) const
  {
    const double v0= OpMacaulay0::get_val(x,a);
    if(x<=a)
      return v0;
    else
      return pow(x-a,N)*v0;
  }

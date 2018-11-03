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
//OpBooleano.cc
#include "OpBooleano.h"
#include "Lexico.h"

const Operando &OpAnd::Opera(const Operando *v1,const Operando *v2) const
  {
    if((v1->GetValor()==1.0) && (v2->GetValor()==1.0))
      return *Lex().NuevoLiteral(1.0);
    else
      return *Lex().NuevoLiteral(0.0);
  }

const Operando &OpOr::Opera(const Operando *v1,const Operando *v2) const
  {
    if((v1->GetValor()==1.0) || (v2->GetValor()==1.0))
      return *Lex().NuevoLiteral(1.0);
    else
      return *Lex().NuevoLiteral(0.0);
  }

const Operando &OpNot::Opera(const Operando *,const Operando *v2) const
  {
    if(v2->GetValor()==1.0)
      return *Lex().NuevoLiteral(0.0);
    else
      return *Lex().NuevoLiteral(1.0);
  }

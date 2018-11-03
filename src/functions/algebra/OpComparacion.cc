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
//OpComparacion.cc

#include "OpComparacion.h"
#include "Lexico.h"

const Operando &OpMenor::Opera(const Operando *v1,const Operando *v2) const
  {
    if(v1->GetValor()<v2->GetValor())
      return *Lex().NuevoLiteral(1.0);
    else
      return *Lex().NuevoLiteral(0.0);
  }

const Operando &OpMenorIgual::Opera(const Operando *v1,const Operando *v2) const
  {
    if(v1->GetValor()<=v2->GetValor())
      return *Lex().NuevoLiteral(1.0);
    else
      return *Lex().NuevoLiteral(0.0);
  }

const Operando &OpIgual::Opera(const Operando *v1,const Operando *v2) const
  {
    if(v1->GetValor()==v2->GetValor())
      return *Lex().NuevoLiteral(1.0);
    else
      return *Lex().NuevoLiteral(0.0);
  }

const Operando &OpMayor::Opera(const Operando *v1,const Operando *v2) const
  {
    if(v1->GetValor()>v2->GetValor())
      return *Lex().NuevoLiteral(1.0);
    else
      return *Lex().NuevoLiteral(0.0);
  }

const Operando &OpMayorIgual::Opera(const Operando *v1,const Operando *v2) const
  {
    if(v1->GetValor()>=v2->GetValor())
      return *Lex().NuevoLiteral(1.0);
    else
      return *Lex().NuevoLiteral(0.0);
  }

const Operando &OpDistinto::Opera(const Operando *v1,const Operando *v2) const
  {
    if(v1->GetValor()!=v2->GetValor())
      return *Lex().NuevoLiteral(1.0);
    else
      return *Lex().NuevoLiteral(0.0);
  }

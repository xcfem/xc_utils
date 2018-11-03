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
//OpUnario.cc
#include "OpUnario.h"
#include "Operando.h"
#include "Literal.h"
#include "OpBinario.h"
#include "Lexico.h"
#include "ArbolExpr.h"
#include "Rama.h"
#include "xc_utils/src/utils/misc_utils/matem.h"

Rama *OpUnario::operator()(Rama *r) const
  { return new Rama(this,NULL,r); }

const Operando &OpNeg::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(-v2->GetValor()); }
Rama OpNeg::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpNeg::Diferencia no implementada." << std::endl;
    return Rama();
//     r->PutDcho(diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpInv::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(1.0/v2->GetValor()); }
Rama OpInv::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpInv::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().neg(Lex().inv(Lex().sqr(Copia(r->GetDcho()))));
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpSign::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(sgn(v2->GetValor())); }
Rama OpSign::Diferencia(const Variable &,const Rama &) const
  { std::cerr<< "OpSign::Diferencia no implementada" << std::endl; return Rama(); }


const Operando &OpAbs::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(fabs(v2->GetValor())); }
Rama OpAbs::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpAbs::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().sign(Copia(r->GetDcho()));
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpSqr::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(v2->GetValor()*v2->GetValor()); }
Rama OpSqr::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpSqr::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *r2= Lex().prodt(new Rama(2.0),Copia(r->GetDcho()));
//     r=Lex().prodt(r2,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpSqrt::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(sqrt(v2->GetValor())); }
Rama OpSqrt::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpSqrt::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().inv(Lex().prodt(new Rama(2.0),Copia(r)));
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpExp::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(exp(v2->GetValor())); }
Rama OpExp::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpExp::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Copia(r);
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpLn::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(log(v2->GetValor())); }
Rama OpLn::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpLn::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().inv(Copia(r->GetDcho()));
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpLg::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(log10(v2->GetValor())); }
Rama OpLg::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpLg::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().inv(Lex().prodt(new Rama(log(10.0)),Copia(r->GetDcho())));
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpRound::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(rint(v2->GetValor())); }

const Operando &OpTrunc::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(floor(v2->GetValor())); }

const Operando &OpToNum::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(v2->GetValor()); }

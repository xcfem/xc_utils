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
//OpTrigonometricas.cc

#include "OpTrigonometricas.h"
#include "Literal.h"
#include "OpBinario.h"
#include "Rama.h"
#include "Lexico.h"
#include "xc_utils/src/utils/misc_utils/matem.h"


const Operando &OpPi::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(M_PI); }

const Operando &OpSin::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(sin(v2->GetValor())); }
Rama OpSin::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpSin::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().cose(Copia(r->GetDcho())); //coseno
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpCos::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(cos(v2->GetValor())); }
Rama OpCos::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpCos::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().neg(Lex().seno(Copia(r->GetDcho()))); //-seno
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpTan::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(tan(v2->GetValor())); }
Rama OpTan::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpTan::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().suma(new Rama(1.0),Lex().sqr(Copia(r)));
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpAtan::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(atan(v2->GetValor())); }
Rama OpAtan::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpAtan::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ri= Lex().inv(Lex().suma(new Rama(1.0),Lex().sqr(Copia(r->GetDcho()))));
//     r=Lex().prodt(ri,diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpSec::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(1/cos(v2->GetValor())); }

const Operando &OpCosec::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(1/sin(v2->GetValor())); }

const Operando &OpCotg::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(1/tan(v2->GetValor())); }

const Operando &OpDeg2Rad::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(DegToRad(v2->GetValor())); }
Rama OpDeg2Rad::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpDeg2Rad::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *c= Lex().divn(new Rama(M_PI),new Rama(180));
//     Rama *bp= diferencia(Copia(r->GetDcho()),v);
//     r= Lex().prodt(c,bp);
//     return r;
  }

const Operando &OpRad2Deg::Opera(const Operando *,const Operando *v2) const
  { return *Lex().NuevoLiteral(RadToDeg(v2->GetValor())); }
Rama OpRad2Deg::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpRad2Deg::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *c= Lex().divn(new Rama(180),new Rama(M_PI));
//     Rama *bp= diferencia(Copia(r->GetDcho()),v);
//     r= Lex().prodt(c,bp);
//     return r;
  }

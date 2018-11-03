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
//OpBinario.cc
#include "OpBinario.h"
#include "Rama.h"
#include "Lexico.h"
#include "Literal.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include <cstdlib>

Rama *OpBinario::operator()(Rama *r1,Rama *r2) const
  { return new Rama(this,r1,r2); }

Rama OpSuma::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpSuma::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama retval(r.GetData());
//     if(r.GetIzdo())
//       retval.PutIzdo(diferencia(*r.GetIzdo(),v));
//     if(r.GetDcho())
//       retval.PutDcho(diferencia(*r.GetDcho(),v));
//    return retval;
  }
Rama *OpSuma::Simplifica(Rama *r) const
  {
    if(*(r->GetIzdo()) == 0.0) r= ContraeIzdo(r);
    if(*(r->GetDcho()) == 0.0) r= ContraeDcho(r);
    return r;
  }
const Operando &OpSuma::Opera(const Operando *v1,const Operando *v2) const
  { return *Lex().NuevoLiteral(v1->GetValor() + v2->GetValor()); }

Rama OpResta::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpResta::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama retval(r.GetData());
//     retval.PutIzdo(diferencia(r->GetIzdo(),v));
//     retval.PutDcho(diferencia(r->GetDcho(),v));
//     return r;
  }

const Operando &OpResta::Opera(const Operando *v1,const Operando *v2) const
  { return *Lex().NuevoLiteral(v1->GetValor() - v2->GetValor()); }

Rama OpProd::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpProd::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *ap= diferencia(Copia(r->GetIzdo()),v);
//     Rama *bp= diferencia(Copia(r->GetDcho()),v);
//     Rama *sum1= Lex().prodt(ap,r->GetDcho());
//     Rama *sum2= Lex().prodt(r->GetIzdo(),bp);
//     r= Lex().suma(sum1,sum2);
//     return r;
  }
Rama *OpProd::Simplifica(Rama *r) const
  {
    if(*(r->GetIzdo()) == 1.0)
      r= ContraeIzdo(r);
    else
      if(*(r->GetDcho()) == 1.0)
        r= ContraeDcho(r);
      else
        if(*(r->GetIzdo()) == 0.0)
          r= ContraeDcho(r);
        else
          if(*(r->GetDcho()) == 0.0)
            r= ContraeIzdo(r);
    return r;
  }

//! @brief Aplica la propiedad distributiva del producto respecto a la suma cuando
//! la suma está a la derecha.
Rama *OpProd::DistribDcha(Rama *raiz) const
  {
    Rama *ri= raiz->GetIzdo(); //Factor que multiplica a la suma.
    Rama *rd= raiz->GetDcho(); //Suma.
    Rama *si= new Rama(&(Lex().prodt),ri->getCopy(),rd->GetIzdo()->getCopy());
    Rama *sd= new Rama(&(Lex().prodt),ri->getCopy(),rd->GetDcho()->getCopy());
    delete raiz;
    raiz= new Rama(&(Lex().suma),si,sd);
    return raiz;
  }

//! @brief Aplica la propiedad distributiva del producto respecto a la suma cuando
//! la suma está a la derecha.
Rama *OpProd::DistribIzda(Rama *raiz) const
  {
    Rama *ri= raiz->GetIzdo(); //Suma.
    Rama *rd= raiz->GetDcho(); //Factor que multiplica a la suma.
    Rama *si= new Rama(&(Lex().prodt),ri->GetIzdo()->getCopy(),rd->getCopy());
    Rama *sd= new Rama(&(Lex().prodt),ri->GetDcho()->getCopy(),rd->getCopy());
    delete raiz;
    raiz= new Rama(&(Lex().suma),si,sd);
    return raiz;
  }

//! @brief Aplica la propiedad distributiva del producto respecto a la suma.
Rama *OpProd::Distrib(Rama *r) const
  {
    const Operando *data= r->DatoDcho();
    if(data)
      {
        const std::string nmbD= data->getName();
        if((nmbD=="+") || (nmbD=="-")) //Hay suma a la derecha.
          r= DistribDcha(r);
      }
    data= r->DatoIzdo();
    if(data)
      {
        const std::string nmbI= data->getName();
        if((nmbI=="+") || (nmbI=="-")) //Hay suma a la izquierda.
          r= DistribIzda(r);
      }
    return r;
  }

const Operando &OpProd::Opera(const Operando *v1,const Operando *v2) const
  { return *Lex().NuevoLiteral(v1->GetValor() * v2->GetValor()); }

Rama OpDiv::Diferencia(const Variable &v,const Rama &r) const
  {
    std::cerr << "OpDiv::Diferencia no implementada." << std::endl;
    return Rama();
//     Rama *up= diferencia(Copia(r->GetIzdo()),v);
//     Rama *vp= diferencia(Copia(r->GetDcho()),v);
//     Rama *sum1= Lex().prodt(r->GetDcho(),up);
//     Rama *sum2= Lex().prodt(r->GetIzdo(),vp);
//     r= Lex().divn(Lex().resta(sum1,sum2),Lex().sqr(Copia(r->GetDcho())));
//     return r;
  }
const Operando &OpDiv::Opera(const Operando *v1,const Operando *v2) const
  { return *Lex().NuevoLiteral(v1->GetValor() / v2->GetValor()); }

const Operando &OpDivEnt::Opera(const Operando *v1,const Operando *v2) const
  { 
    ldiv_t dt= ldiv((long)v1->GetValor(),(long)v2->GetValor());
    return *Lex().NuevoLiteral(dt.quot);
  }

const Operando &OpMod::Opera(const Operando *v1,const Operando *v2) const
  { return *Lex().NuevoLiteral(long(v1->GetValor()) % long(v2->GetValor())); }

const Operando &OpPot::Opera(const Operando *v1,const Operando *v2) const
  { return *Lex().NuevoLiteral(pow(v1->GetValor(),v2->GetValor())); }

const Operando &OpMax::Opera(const Operando *v1,const Operando *v2) const
  {
    const double &vv1= v1->GetValor();
    const double &vv2= v2->GetValor();
    if(vv1>=vv2)
      return *Lex().NuevoLiteral(vv1);
    else
      return *Lex().NuevoLiteral(vv2);
  }

const Operando &OpMin::Opera(const Operando *v1,const Operando *v2) const
  {
    const double &vv1= v1->GetValor();
    const double &vv2= v2->GetValor();
    if(vv1<=vv2)
      return *Lex().NuevoLiteral(vv1);
    else
      return *Lex().NuevoLiteral(vv2);
  }

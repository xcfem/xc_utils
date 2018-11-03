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
//VarExpr.h

#ifndef VAREXPR_H
#define VAREXPR_H

#include "ExprAlgebra.h"

class VarExpr : public Variable
  {
    ExprAlgebra expr;
  public:
    VarExpr(void) : Variable() {}
    VarExpr(const std::string &nmb): Variable(nmb) {}
    VarExpr(const VarExpr &otra): Variable(otra) {}
    VarExpr &operator=(const VarExpr &otra)
      {
        Variable::operator =(otra);
        expr= otra.expr;
        return *this;
      }
    inline ExprAlgebra GetExpr(void) const
      { return expr; }
    inline virtual void Asigna(const double &d)
      {
        Variable::Asigna(d);
        expr= ExprAlgebra(d);
      }
    inline virtual void AsignaExpr(const ExprAlgebra &ex)
      {
        Variable::Asigna(0.0);
        expr= ex;
      }
    virtual bool Evaluable(void) const
      { return ((Variable::Evaluable()) && (expr.Evaluable())); }
    inline virtual const Operando &Opera(const Operando *, const Operando *) const
      {
        if(Evaluable())
          return *Lex().NuevoLiteral(expr.ToNum());
        else
          return *this;
      }
    inline virtual const double &GetValor(const double &v1=0.0, const double &v2=0.0) const
      { return expr.ToNum(); }
  };

#endif

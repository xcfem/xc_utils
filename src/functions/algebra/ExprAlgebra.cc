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
//ExprAlgeblra.cc
#include "ExprAlgebra.h"
#include "TablaVariables.h"
#include "LexAlgebra.h"
#include "ConjVariables.h"
#include "integ_num.h"
#include <cmath>
#include "MapValores.h"

//! @brief Constructor.
ExprAlgebra::ExprAlgebra(void)
  : ArbolExpr("") {}
//! @brief Constructor.
ExprAlgebra::ExprAlgebra(const std::string &str)
  : ArbolExpr(str) {}
//! @brief Constructor.
ExprAlgebra::ExprAlgebra(const ExprAlgebra &otra)
  : ArbolExpr(otra) {}
//! @brief Constructor.
ExprAlgebra::ExprAlgebra(const double &d)
  : ArbolExpr(d) {}

void ExprAlgebra::expand(void)
  {
    ConjVariables cv= Variables();
    for(register ConjVariables::const_iterator i=cv.begin();i!=cv.end();i++)
      {
        const std::string &nmb_var= (*i)->getName();
        if(LexA().EsExpresion(nmb_var))
          {
            ExprAlgebra e= LexA().GetExpresion(nmb_var);
            eval(nmb_var.c_str(),e);
          }
      }
    Distrib();
  }

//! @brief Evalúa la expresión a partir de los valores que se pasan como parámetro.
void ExprAlgebra::eval(const MapValores &mv)
  {
    for(MapValores::const_iterator i= mv.begin();i!=mv.end();i++)
      Asigna((*i).first,(*i).second);
    Opera();
  }

ExprAlgebra ExprAlgebra::Eval(const std::string &valores) const
  {
    ExprAlgebra retval(*this);
    retval.eval(MapValores(valores));
    return retval;
  }

//! @brief Devuelve la raiz de la expresion aproximandola por Newton.
double ExprAlgebra::RaizNewton(const double &tol,size_t max_iter,const std::string &var,const double &d,double &err)
  {
    if(this->NumVariables() > 1)
      {
        std::cerr << "Functions: " << *this << " has more than one variable." << std::endl;
        return NAN;
      }
    const ExprAlgebra dif= (*this)/(this->Diferencia(var)).Colct();
    double D,x= d;
    register size_t iter= 0;
    do
      {
        D= dif(var,x).ToNum();
        x-=D;
        iter++;
      }
    while((iter<max_iter) && (fabs(D)>tol));
    err= fabs(D);
    return x;
  }

//! @brief Devuelve el valor absoluto del argumento.
ExprAlgebra abs(const ExprAlgebra &otro)
  {
    ExprAlgebra retval(otro);
    retval.Abs();
    return retval;
  }

//! @brief Devuelve la raía cuadrada del argumento.
ExprAlgebra sqrt(const ExprAlgebra &otro)
  {
    ExprAlgebra retval(otro);
    retval.Sqrt();
    return retval;
  }

//! @brief Devuelve a^b.
ExprAlgebra pow(const ExprAlgebra &a,const ExprAlgebra &b)
  {
    ExprAlgebra retval(a);
    retval.pow(b);
    return retval;
  }
//! @brief Devuelve a^b.
ExprAlgebra pow(const ExprAlgebra &a,const double &b)
  {
    ExprAlgebra retval(a);
    retval.pow(ExprAlgebra(b));
    return retval;
  }
//! @brief Devuelve a^b.
ExprAlgebra pow(const double &a,const ExprAlgebra &b)
  {
    ExprAlgebra retval(a);
    retval.pow(b);
    return retval;
  }

ExprAlgebra expand(const ExprAlgebra &a)
  {
    ExprAlgebra retval(a);
    retval.expand();
    return retval;
  }

ExprAlgebra colct(const ExprAlgebra &a)
  {
    ExprAlgebra retval(a);
    retval.Colct();
    return retval;
  }

//! @brief Integra la expresión mediante la regla del trapecio.
//! @param i: Intervalo de integración.
ExprAlgebra ExprAlgebra::IntegTrapecio(const Intervalo1D &i) const
  { return integ_trapecio(*this,i); }

//! @brief Integra la expresión mediante la regla de simpson.
//! @param i: Intervalo de integración.
ExprAlgebra ExprAlgebra::IntegSimpson(const Intervalo1D &i) const
  { return integ_simpson(*this,i); }



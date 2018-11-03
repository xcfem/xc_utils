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
//ExprAlgebra.h

#ifndef EXPRALGEBRA_H
#define EXPRALGEBRA_H


#include "ArbolExpr.h"

class Intervalo1D;

//! @brief Expresión algebraica.
class ExprAlgebra : public ArbolExpr
  {
    friend class ExpressionMatrix;
    inline void eval(void)
      {
        expand();
        Opera();
      }
    inline void eval(const std::string &palabra,const ExprAlgebra &a)
      {
        Asigna(palabra,a);
        Opera();
      }
    void eval(const MapValores &);
    inline void eval(const std::string &palabra,const double &d)
      {
        Asigna(palabra,d);
        Opera();
      }
    void expand(void);

  public:
    ExprAlgebra(void);
    explicit ExprAlgebra(const std::string &);
    ExprAlgebra(const ExprAlgebra &);
    explicit ExprAlgebra(const double &);
    ExprAlgebra &operator=(const ExprAlgebra &otra)
      {
        ArbolExpr::operator=(otra);
        return *this;
      }
    ExprAlgebra &operator+=(const ExprAlgebra &a2)
      {
        ArbolExpr::operator+=(a2);
        return *this;
      }
    ExprAlgebra &operator-=(const ExprAlgebra &a2)
      {
        ArbolExpr::operator-=(a2);
        return *this;
      }
    ExprAlgebra &operator*=(const ExprAlgebra &a2)
      {
        ArbolExpr::operator*=(a2);
        return *this;
      }
    ExprAlgebra &operator/=(const ExprAlgebra &a2)
      {
        ArbolExpr::operator/=(a2);
        return *this;
      }
    inline ExprAlgebra operator-(void)
      {
        ExprAlgebra retval(*this);
        retval.Neg();
        return retval;
      }
    inline ExprAlgebra Eval(void) const
      {
        ExprAlgebra retval(*this);
        retval.eval();
        return retval;
      }
    inline ExprAlgebra Eval(const std::string &palabra,const ExprAlgebra &a) const
      {
        ExprAlgebra retval(*this);
        retval.eval(palabra,a);
        return retval;
      }
    inline ExprAlgebra Eval(const std::string &palabra,const double &d) const
      {
        ExprAlgebra retval(*this);
        retval.eval(palabra,d);
        return retval;
      }
    ExprAlgebra Eval(const std::string &valores) const;
    inline ExprAlgebra Diferencia(const std::string &var) const
      {
        ExprAlgebra retval(*this);
        retval.Dif(var);
        return retval;
      }
    inline ExprAlgebra Colct(void) const
      {
        ExprAlgebra retval(*this);
        retval.Simplifica();
        return retval;
      }
    double RaizNewton(const double &tol,size_t max_iter,const std::string &var,const double &d,double &err);
    inline ExprAlgebra operator()(const std::string &p,const ExprAlgebra &a) const
      { return Eval(p,a); }
    inline ExprAlgebra operator()(const std::string &p,const double &d) const
      { return Eval(p,d); }
    ExprAlgebra IntegTrapecio(const Intervalo1D &i) const;
    ExprAlgebra IntegSimpson(const Intervalo1D &i) const;
    friend ExprAlgebra operator+(const ExprAlgebra &a1,const ExprAlgebra &a2)
      {
        ExprAlgebra retval(a1);
        return retval+=a2;
      }
    friend ExprAlgebra operator+(const ExprAlgebra &a1,const double &a2)
      {
        ExprAlgebra retval(a1);
        return retval+= ExprAlgebra(a2);
      }
    friend ExprAlgebra operator+(const double &a1,const ExprAlgebra &a2)
      {
        ExprAlgebra retval(a1);
        return retval+=a2;
      }
    friend ExprAlgebra operator-(const ExprAlgebra &a1,const ExprAlgebra &a2)
      {
        ExprAlgebra retval(a1);
        return retval-=a2;
      }
    friend ExprAlgebra operator-(const ExprAlgebra &a1,const double &a2)
      {
        ExprAlgebra retval(a1);
        return retval-= ExprAlgebra(a2);
      }
    friend ExprAlgebra operator-(const double &a1,const ExprAlgebra &a2)
      {
        ExprAlgebra retval(a1);
        return retval-=a2;
      }
    friend ExprAlgebra operator*(const ExprAlgebra &a1,const ExprAlgebra &a2)
      {
        ExprAlgebra retval(a1);
        return retval*=a2;
      }
    friend ExprAlgebra operator*(const ExprAlgebra &a1,const double &a2)
      {
        ExprAlgebra retval(a1);
        return retval*= ExprAlgebra(a2);
      }
    friend ExprAlgebra operator*(const double &a1,const ExprAlgebra &a2)
      {
        ExprAlgebra retval(a1);
        return retval*=a2;
      }
    friend ExprAlgebra operator/(const ExprAlgebra &a1,const ExprAlgebra &a2)
      {
        ExprAlgebra retval(a1);
        return retval/=a2;
      }
    friend ExprAlgebra operator/(const ExprAlgebra &a1,const double &a2)
      {
        ExprAlgebra retval(a1);
        return retval/= ExprAlgebra(a2);
      }
    friend ExprAlgebra operator/(const double &a1,const ExprAlgebra &a2)
      {
        ExprAlgebra retval(a1);
        return retval/=a2;
      }
    friend ExprAlgebra expand(const ExprAlgebra &);
    friend ExprAlgebra abs(const ExprAlgebra &);
    friend ExprAlgebra sqrt(const ExprAlgebra &);
    friend ExprAlgebra pow(const ExprAlgebra &a,const ExprAlgebra &b);
    friend ExprAlgebra pow(const ExprAlgebra &a,const double &b);
    friend ExprAlgebra pow(const double &a,const ExprAlgebra &b);
  };

ExprAlgebra expand(const ExprAlgebra &);
ExprAlgebra colct(const ExprAlgebra &);

#endif







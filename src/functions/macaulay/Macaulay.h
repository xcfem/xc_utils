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
//Macaulay.h
#ifndef MACAULAY_H
#define MACAULAY_H

#include "../polinomios/function.h"

typedef vectorZ<double> vZ_double;

class Macaulay : public Function
  {
  protected:
    int n;
    double a;
    double coef;
  public:
    Macaulay(void): Function()
      { n= 0; a= 0.0; coef= 1.0;}
    Macaulay(const NmbVars &vars, const int n= 0, const double a= 0.0): Function(vars)
      { this->n= n; this->a= a; coef= 1; }
    Macaulay(const char *vars, const int n= 0, const double a= 0.0): Function(vars)
      { this->n= n; this->a= a; coef= 1; }
    Macaulay(const Macaulay &otro): Function(otro)
      { n= otro.n; a= otro.a; coef= otro.coef; }
    Macaulay &operator=(const Macaulay &m)
      {
        Function::operator=(m);
        n= m.n; a= m.a; coef= m.coef;
        return *this;
      }
    int Grado(void) const
      { return n; }
    double GetA(void) const
      { return a; }
    double Eval(const double &x) const;
    double operator()(const double &x) const
    //Evalua el Macaulay en el punto x.
      { return Eval(x); }
    Macaulay &operator*=(const Macaulay &m);
    friend Macaulay operator *(const Macaulay &m1,const Macaulay &m2);
    friend bool operator ==(const Macaulay &p1,const Macaulay &p2);
    friend std::ostream &operator <<(std::ostream &stream,const Macaulay &p);
    Macaulay Primitiva(void) const;
    Macaulay Diferencial(void) const;
    double Integral(const double &a, const double &b) const;
    double Derivada(const double &x) const;
    friend double dot(const Macaulay &m1,const Macaulay &m2, const double &a, const double &b);
  };

#endif









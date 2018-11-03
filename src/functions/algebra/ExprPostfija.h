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
//ExprPostFija.h

#ifndef EXPRPOSTFIJA_H
#define EXPRPOSTFIJA_H

#include <iostream>
#include "ExprInfija.h"
#include <stack>
#include "PilaPunteros.h"
#include "Operando.h"


class ExprPostfija: public Expresion
  {
  protected:
    typedef PilaPunteros<const Segnal> Pila;

    void TrataParentDcho(Pila &pila,const Segnal *t);
    void TrataOpBinario(Pila &pila,const Segnal *t);
    void TrataFinExpr(Pila &pila);
    void Traduce(const ExprInfija &infija);
    void Traduce(std::istream &is);
  public:
    ExprPostfija(void)
      : Expresion() {}
    ExprPostfija(const std::string &str): Expresion()
      { Expresion::operator=(str); }
    ExprPostfija(const ExprPostfija &otra): Expresion(otra) {}
    ExprPostfija &operator=(const ExprPostfija &otra)
      {
        Expresion::operator =(otra);
        return *this;
      }
    ExprPostfija(const ExprInfija &otra): Expresion(otra)
      { Traduce(otra); }
    ExprPostfija &operator=(const ExprInfija &otra)
      {
        Traduce(otra);
        return *this;
      }
    ExprPostfija &operator=(const std::string &str)
      {
        Expresion::operator=(str);
        return *this;
      }
  };

#endif






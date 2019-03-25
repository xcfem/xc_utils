//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.  
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
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






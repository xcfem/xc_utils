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
//ExprPostfija.cc

#include "ExprPostfija.h"

void ExprPostfija::TrataParentDcho(Pila &pila,const Segnal *t)
  {
    t= pila.Pop();
    while(t->GetClase() != parent_izdo)
      {
        PonerSegnal(t);
        t= pila.Pop();
      }
  }
void ExprPostfija::TrataOpBinario(Pila &pila,const Segnal *t)
  {
    register bool fin_derecha= false;
    do
      {
        if (pila.empty()) 
          fin_derecha= true;
        else
          if((*pila.top()).GetClase() == parent_izdo)
            fin_derecha= true;
          else
            if((*pila.top()).GetPrioridad() < t->GetPrioridad())
              fin_derecha= true;
            else
              {
                fin_derecha= false;
                PonerSegnal(pila.Pop());
              }
      }
    while(!fin_derecha);
    pila.push(t);
  }
void ExprPostfija::TrataFinExpr(Pila &pila)
  {
    while(pila.size()>0)
      { PonerSegnal(pila.Pop()); }
  }

void ExprPostfija::Traduce(const ExprInfija &infija)
  {
    borra_lista();//erase(begin(),end());
    if (infija.Vacia()) return;
    Pila pila;
    register ExprInfija::const_iterator_segnales i= infija.Begin();
    while(i!= infija.End())
      {
        switch((*i)->GetClase())
          {
          case operando:
            PonerSegnal(*i);
            break;
          case parent_izdo:
            pila.push(*i);
            break;
          case parent_dcho:
            TrataParentDcho(pila,*i);
            break;
          case op_unitario:
          case op_binario:
            TrataOpBinario(pila,*i);
            break;
          case fin_exp:
            break;
          }
        i++;
      }
    TrataFinExpr(pila);
  }

//! @brief Traduce la expresión que se lee desde el istream.
void ExprPostfija::Traduce(std::istream &is)
  {
    ExprInfija infja;
    is >> infja;
    if(infja.ErrorTraduccion())
      {
        std::cerr << "ExprPostfija::Traduce; se produjo un error al interpretar la expresión." << std::endl;
        err_traduc= true;
      }
    else
      Traduce(infja);
  }

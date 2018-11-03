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
//TablaLiterales.cc

#include "TablaLiterales.h"
#include "Rama.h"
#include <iostream>
#include <cassert>


//! @brief Constructor.
TablaLiterales::Literal::Literal(const double &d)
  : Operando(d) {}

// TablaLiterales::Literal &TablaLiterales::Literal::operator=(const Literal &otro)
//   {
//     std::cerr << "Literal; no se debe llamar al operador asignación." << std::endl;
//     Operando::operator=(otro);
//     return *this;
//   }

Rama TablaLiterales::Literal::Diferencia(const Variable &,const Rama &r) const
  { return Rama(0.0); }

std::ostream &TablaLiterales::Literal::Imprime(std::ostream &os) const
  {
    os << valor;
    return os;
  }

//! @brief Constructor.
TablaLiterales::TablaLiterales(void)
  {}

//! @brief Nueva referencia a un literal.
void TablaLiterales::NuevaRef(const Literal &l)
  {
    iterator i= literales.find(l);
    if(i!=literales.end()) //Ya existe.
      (*i).second++;
    else
      std::cerr << "TablaLiterales::NuevaRef; no se encontró el literal: " << l.GetValor() << std::endl;
  }

//! @brief Nueva referencia a un literal.
void TablaLiterales::NuevaRef(const double &d)
  {
    const Literal l(d);
    NuevaRef(l);
  }

//! @brief Quita el literal de la tabla si efectivamente el puntero corresponde a un literal.
void TablaLiterales::NuevaRef(const Segnal *s)
  {
    const Literal *ptr= dynamic_cast<const Literal *>(s);
    if(ptr)
      NuevaRef(*ptr);
  }

//! @brief Añade el literal a la tabla.
const TablaLiterales::Literal *TablaLiterales::Nuevo(const Literal &l)
  { 
    const TablaLiterales::Literal *retval= NULL;

    //Nos aseguramos de que no ha ocurrido
    //el «static initialization order fiasco»
    //cuando declaramos una ExprAlgebra como estática.
    assert(ProtoExpresion::TieneLexico());
  
    iterator i= literales.find(l);
    if(i==literales.end()) //Nuevo.
      {
        value_type tmp(l,1);
        i= (literales.insert(tmp)).first;
      }
    else //Ya existe.
      { (*i).second++; }
    retval= &((*i).first);
    return retval;
  }

//! @brief Quita el literal de la tabla.
void TablaLiterales::Borra(const Literal &l)
  {
    iterator i= literales.find(l);
    if(i!=literales.end()) //existe.
      {
        (*i).second--;
        if((*i).second == 0)
          literales.erase(i);
      }
    else
      std::cerr << "TablaLiterales::Borra; no se encontró el literal: " << l.GetValor() << std::endl;
  }

//! @brief Quita el literal de la tabla.
void TablaLiterales::Borra(const double &d)
  {
    const Literal l(d);
    Borra(l);
  }

//! @brief Quita el literal de la tabla si efectivamente el puntero corresponde a un literal.
void TablaLiterales::BorraSiLiteral(const Segnal *s)
  {
    const Literal *ptr= dynamic_cast<const Literal *>(s);
    if(ptr)
      Borra(*ptr);
  }

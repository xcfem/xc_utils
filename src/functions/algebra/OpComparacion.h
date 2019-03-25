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
//OpComparacion.h

#ifndef OPCOMPARACION_H
#define OPCOMPARACION_H

#include "OpBinario.h"
#include "nombres_operadores.h"

//! @brief Clase base para operadores de comparación.
class OpComparacion: public OpBinario
  {
  public:
    OpComparacion(void) : OpBinario() {}
    inline virtual int GetPrioridad(void) const
      { return 3; }
  };

//! @brief Operador menor que.
//! Devuelve 1 si el valor izquierdo es menor que el derecho
//! y 0 en caso contrario.
class OpMenor : public OpComparacion
  {
    
  public:
    OpMenor(void) : OpComparacion() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpMenor; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

//! @brief Operador menor o igual que.
//! Devuelve 1 si el valor izquierdo es menor o igual que el derecho
//! y 0 en caso contrario.
class OpMenorIgual : public OpComparacion
  {
    
  public:
    OpMenorIgual(void) : OpComparacion() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpMenorIgual; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

//! @brief Operador igualdad
//! Devuelve 1 si el valor izquierdo es igual que el derecho
//! y 0 en caso contrario.
class OpIgual : public OpComparacion
  {
    
  public:
    OpIgual(void) : OpComparacion() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpIgual; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

//! @brief Operador mayor que.
//! Devuelve 1 si el valor izquierdo es mayor que el derecho
//! y 0 en caso contrario.
class OpMayor : public OpComparacion
  {
    
  public:
    OpMayor(void) : OpComparacion() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpMayor; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

//! @brief Operador mayor o igual que.
//! Devuelve 1 si el valor izquierdo es mayor o igual que el derecho
//! y 0 en caso contrario.
class OpMayorIgual : public OpComparacion
  {
    
  public:
    OpMayorIgual(void) : OpComparacion() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpMayorIgual; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

//! @brief Operador distinto.
//! Devuelve 1 si el valor izquierdo es distinto del derecho
//! y 0 en caso contrario.
class OpDistinto : public OpComparacion
  {
    
  public:
    OpDistinto(void) : OpComparacion() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpDistinto; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

#endif

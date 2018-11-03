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

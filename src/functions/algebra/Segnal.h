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
//Segnal.h

#ifndef SEGNAL_H
#define SEGNAL_H

#include <string>

//! @brief Clase de una señal
//!
//! La clase de una expresión puede ser:
//! -fin_exp: Señala el final de la expresión.
//! -parent_izdo: Paréntesis izquierdo.
//! -parent_dcho: Paréntesis derecho.
//! -operando: Objeto sobre el que actúa un operador.
//! -op_unitario: Operador unitario, que opera sobre un sólo operando (factorial, trigonometric functions, negación,...).
//! -op_binario: Operador binario, que opera sobre dos operandos (suma, resta, multiplicación,...).
//!
enum Clase { fin_exp,
             parent_izdo, parent_dcho,
             operando,
             op_unitario, op_binario};

class Variable;
class Lexico;


//! @brief Componente elemental de una expresión.
//!
//! Componente elemental de una expresión.
//! La prioridad de un operador es:
//!
//! 6: Todos los operadores aritméticos unitarios, elevado a (^).
//! 5: Producto, división, mod, div.
//! 4: Suma, resta,
//! 3: Operadores de comparación (igualdad, desigualdad, menor que, mayor que,...).
//! 3: No (booleano).
//! 2: y,o (booleanos).
//! 1: asignación.
//! -1: Paréntesis.
class Segnal
  {
  public:
    inline Segnal(void) {}
    inline virtual ~Segnal(void) {}
    virtual const std::string &getName(void) const= 0;
    virtual Clase GetClase(void) const= 0;
    virtual const double &GetValor(const double &v1= 0.0, const double &v2= 0.0) const= 0;
    inline virtual int GetPrioridad(void) const
      { return -1; }
    const std::string &StrClase(void) const;
    virtual std::ostream &Imprime(std::ostream &os) const;
    inline virtual bool IgualA(const double &) const
      { return false; }
    friend int operator<(const Segnal &s1,const Segnal &s2)
      { return (s1.getName() < s2.getName()); }
    friend int operator==(const Segnal &s,const double &d)
      { return s.IgualA(d); }
    friend int operator==(const double &d,const Segnal &s)
      { return (s == d); }
  };

std::ostream &operator<<(std::ostream &, const Segnal &);


#endif



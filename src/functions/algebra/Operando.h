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
//Operando.h

#ifndef OPERANDO_H
#define OPERANDO_H

#include "Segnal.h"
#include "ProtoExpr.h"
#include "string"

//! @brief Posición de un operador
//!
//! La posición de un operador puede ser:
//! - prefija: Cuando se escribe antes que los operandos: sin(a), -1.0,not(b),...
//! - infija: Cuando se escribe entre los operandos: +,-,*,/...
//! - sufija: Cuando se escribe detrás de los operandos: factorial.
enum Posicion{prefija,infija,sufija};

class Rama;
class ConjVariables;

//! @brief Operando.
class Operando: public Segnal, public ProtoExpresion
  {
  protected:
    double valor;
  public:
    inline explicit Operando(const double &d= 0.0)
      : valor(d) {}
    void Put(const double &v)
      { valor= v; }
    virtual const std::string &getName(void) const;
    virtual const std::string &GetFullString(void) const;
    inline virtual Clase GetClase(void) const
      { return operando; }
    inline virtual Posicion GetPosicion(void) const
      { return infija; }
    virtual bool Evaluable(void) const
      { return false; }
    inline virtual const Operando &Opera(const Operando *, const Operando *) const
      { return *this; }
    virtual Rama Diferencia(const Variable &,const Rama &) const;
    virtual Rama *Simplifica(Rama *) const;
    virtual Rama *Distrib(Rama *) const;
    inline virtual void GetVariables(ConjVariables &) const {}
    inline virtual const double &GetValor(const double &v1=0.0, const double &v2=0.0) const
      { return valor; }
  };

#endif

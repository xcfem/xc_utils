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
//OpBooleano.h

#ifndef OPBOOLEANO_H
#define OPBOOLEANO_H

#include "OpBinario.h"
#include "OpUnario.h"

//! @brief Clase base para operadores de comparación.
class OpBooleano: public OpBinario
  {
  public:
    OpBooleano(void) : OpBinario() {}
    inline virtual int GetPrioridad(void) const
      { return 3; }
  };

//! @brief Operador AND.
//! Devuelve 1 si son verdaderas ambas condiciones y 0 en caso contrario.
class OpAnd : public OpBooleano
  {
    
  public:
    OpAnd(void) : OpBooleano() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpAnd; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

//! @brief Operador OR.
//! Devuelve 1 si alguna de las condiciones es verdadera y 0 en caso contrario.
class OpOr : public OpBooleano
  {
    
  public:
    OpOr(void) : OpBooleano() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpOr; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

class OpNot : public OpUnario
  {
    
  public:
    OpNot(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpNot; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
  };

#endif

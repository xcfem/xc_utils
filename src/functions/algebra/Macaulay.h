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

#include "OpBinario.h"
#include "nombres_operadores.h"

class Rama;

//! @brief Función de Macaulay F0 (Ver Mecánica de materiales Gere-Timoshenko apdo. 7.9).
//! se define como:
//! <x-a>= 0 si x<=a.
//! <x-a>= 1 si x>=a.
class OpMacaulay0: public OpBinario
  {
  protected:
    virtual double get_val(const double &x,const double &a) const;
  public:
    OpMacaulay0(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpMacaulay0; }
    virtual int GetPrioridad(void) const
      { return 4; }
    inline virtual Posicion GetPosicion(void) const
      { return prefija; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };


//! @brief Función de Macaulay Fn (Ver Mecánica de materiales Gere-Timoshenko apdo. 7.9).
//! se define como:
//! <x-a>= 0 si x<=a.
//! <x-a>= (x-a)^n si x>=a.
class OpMacaulayN: public OpMacaulay0
  {
    size_t N;
    std::string nmbOpMacaulayN;
  protected:
    virtual double get_val(const double &x,const double &a) const;
  public:
    OpMacaulayN(size_t n=1);
    inline virtual const std::string &getName(void) const
      { return nmbOpMacaulayN; }
    virtual ~OpMacaulayN(void)
      {}
  };

#endif

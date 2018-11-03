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
//OpBinario.h

#ifndef OPBINARIO_H
#define OPBINARIO_H

#include "Operador.h"
#include "nombres_operadores.h"

class Rama;

//! @brief Operador binario.
class OpBinario : public Operador
  {
  public:
    OpBinario(void) : Operador() {}
    OpBinario(const int &p): Operador(p) {}
    OpBinario(const OpBinario &otro): Operador(otro) {}
    OpBinario &operator=(const OpBinario &otro)
      {
        Operador::operator =(otro);
        return *this;
      }
    inline virtual Clase GetClase(void) const
      { return op_binario; }
    inline virtual Posicion GetPosicion(void) const
      { return infija; }
    Rama *operator()(Rama *r1,Rama *r2) const;
  };

class OpSuma : public OpBinario
  {
    
  public:
    OpSuma(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpSuma; }
    virtual int GetPrioridad(void) const
      { return 4; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
    virtual Rama *Simplifica(Rama *r) const;
  };

class OpResta : public OpBinario
  {
    
  public:
    OpResta(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpResta; }
    virtual int GetPrioridad(void) const
      { return 4; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpProd : public OpBinario
  {
    
  public:
    OpProd(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpProd; }
    virtual int GetPrioridad(void) const
      { return 5; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
    virtual Rama *Simplifica(Rama *r) const;
    Rama *DistribDcha(Rama *raiz) const;
    Rama *DistribIzda(Rama *raiz) const;
    Rama *Distrib(Rama *r) const;
  };

class OpDiv : public OpBinario
  {
    
  public:
    OpDiv(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpDiv; }
    virtual int GetPrioridad(void) const
      { return 5; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpDivEnt : public OpBinario
  {
    
  public:
    OpDivEnt(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpDivEnt; }
    virtual int GetPrioridad(void) const
      { return 5; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

class OpMod : public OpBinario
  {
    
  public:
    OpMod(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpMod; }
    virtual int GetPrioridad(void) const
      { return 5; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

class OpPot : public OpBinario
  {
    
  public:
    OpPot(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpPot; }
    virtual int GetPrioridad(void) const
      { return 6; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

//! @brief Operador max.
//! Devuelve el máximo de los valores izquierdo y derecho
class OpMax : public OpBinario
  {
    
  public:
    OpMax(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpMax; }
    virtual int GetPrioridad(void) const
      { return 4; }
    inline virtual Posicion GetPosicion(void) const
      { return prefija; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

//! @brief Operador min.
//! Devuelve el mínimo de los valores izquierdo y derecho
class OpMin : public OpBinario
  {
    
  public:
    OpMin(void) : OpBinario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpMin; }
    virtual int GetPrioridad(void) const
      { return 4; }
    inline virtual Posicion GetPosicion(void) const
      { return prefija; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

#endif

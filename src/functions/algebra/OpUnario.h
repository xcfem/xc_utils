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
//OpUnario.h

#ifndef OPUNARIO_H
#define OPUNARIO_H

#include "Operador.h"
#include "nombres_operadores.h"

class OpUnario: public Operador
  {
  public:
    OpUnario(void) : Operador() {}
    OpUnario(const int &p): Operador(p) {}
    OpUnario(const OpUnario &otro): Operador(otro) {}
    OpUnario &operator=(const OpUnario &otro)
      {
        Operador::operator =(otro);
        return *this;
      }
    inline virtual Clase GetClase(void) const
      { return op_unitario; }
    inline virtual Posicion GetPosicion(void) const
      { return prefija; }
    virtual int GetPrioridad(void) const
      { return 6; }
    Rama *operator()(Rama *r) const;
  };

class OpNeg : public OpUnario
  {
    
  public:
    OpNeg(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpNeg; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpInv : public OpUnario
  {
    
  public:
    OpInv(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpInv; }
    virtual const Operando &Opera(const Operando *,const Operando *v2=NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpSign : public OpUnario
  {
    
  public:
    OpSign(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpSign; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &) const;
  };

class OpAbs : public OpUnario
  {
    
  public:
    OpAbs(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpAbs; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &) const;
  };

class OpSqr : public OpUnario
  {
    
  public:
    friend class Lexico;
    OpSqr(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpSqr; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpSqrt : public OpUnario
  {
    
  public:
    OpSqrt(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpSqrt; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpExp : public OpUnario
  {
    
  public:
    OpExp(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpExp; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

//! @brief Logaritmo neperiano.
class OpLn : public OpUnario
  {
    
  public:
    OpLn(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpLn; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpLg : public OpUnario
  {
    
  public:
    OpLg(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpLg; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpRound : public OpUnario
  {
    
  public:
    OpRound(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpRound; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
  };

class OpTrunc : public OpUnario
  {
    
  public:
    OpTrunc(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpTrunc; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
  };

class OpToNum : public OpUnario
  {
    
  public:
    OpToNum(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpToNum; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
  };
#endif











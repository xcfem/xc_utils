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
//Operador.h

#ifndef OPERADOR_H
#define OPERADOR_H

#include "Operando.h"
#include "nombres_operadores.h"

//! @brief Clase base de los operadores unarios y binarios.
class Operador : public Operando
  {
  protected:
    int prioridad;
  public:
    friend class Lexico;
    Operador(void) : Operando()
      { Put(-1); }
    Operador(const int &p)
      : Operando(), prioridad(p) {}
    Operador(const Operador &otro)
      : Operando(otro), prioridad(otro.prioridad) {}
    Operador &operator=(const Operador &otro);
    void Put(const int &pv)
      {
        Operando::Put(0.0);
        prioridad= pv;
      }
    virtual int GetPrioridad(void) const
      { return prioridad; }
    virtual const std::string &GetFullString(void) const;
  };

class ParentIzdo : public Operador
  {
  public:
    ParentIzdo(void) : Operador(-1) {}
    inline virtual Clase GetClase(void) const
      { return parent_izdo; }
    inline virtual const std::string &getName(void) const
      { return nmbParentIzdo; }
  };

class ParentDcho : public Operador
  {
  public:
    ParentDcho(void) : Operador(-1) {}
    inline virtual Clase GetClase(void) const
      { return parent_dcho; }
    inline virtual const std::string &getName(void) const
      { return nmbParentDcho; }
  };


#endif




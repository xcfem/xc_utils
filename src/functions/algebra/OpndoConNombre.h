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
//OpdoConNombre.h

#ifndef OPNDOCONNOMBRE_H
#define OPNDOCONNOMBRE_H

#include "Operando.h"

class OpndoConNombre : public Operando
  {
  protected:
    std::string nombre;
  public:
    OpndoConNombre(void) : Operando(), nombre() {}
    OpndoConNombre(const std::string &nmb,const double &d=0.0): Operando(d), nombre(nmb) {}
    OpndoConNombre(const OpndoConNombre &otro): Operando(otro), nombre(otro.nombre) {}
    OpndoConNombre &operator=(const OpndoConNombre &otro)
      {
        Operando::operator =(otro);
        nombre= otro.nombre;
        return *this;
      }
    void Put(const std::string &nmb, const double &v)
      {
	Operando::Put(v);
        nombre= nmb;
      }
    inline virtual const std::string &getName(void) const
      { return nombre; }
    inline virtual const std::string &GetFullString(void) const
      { return nombre; }
    friend std::istream &operator >>(std::istream &is, OpndoConNombre &s);
    virtual int GetPrioridad(void) const
      { return 8; }
    virtual ~OpndoConNombre(void)
      {}
  };


#endif

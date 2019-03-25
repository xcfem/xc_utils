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

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
//Variable.h

#ifndef VARIABLE_H
#define VARIABLE_H

#include "OpndoConNombre.h"


class ExprAlgebra;

class Variable : public OpndoConNombre
  {
    bool asignada;
  public:
    Variable(void) : OpndoConNombre(), asignada(false) {}
    Variable(const std::string &nmb): OpndoConNombre(nmb), asignada(false) {}
    Variable(const Variable &otra): OpndoConNombre(otra), asignada(otra.asignada) {}
    Variable &operator=(const Variable &otra)
      {
        OpndoConNombre::operator =(otra);
        asignada= otra.asignada;
        return *this;
      }
    inline virtual bool Evaluable(void) const
      { return asignada; }
    inline virtual void Asigna(const double &d)
      {
        asignada= true;
        valor= d;
      }
    inline virtual void AsignaExpr(const double &d) {}
    inline void DesAsigna(void)
      { asignada= false; }
    virtual const Operando &Opera(const Operando *, const Operando *) const;
    virtual Rama Diferencia(const Variable &v,const Rama &) const;
    virtual void GetVariables(ConjVariables &cv) const;
  };

#endif

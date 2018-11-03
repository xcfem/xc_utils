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
//Constante.h

#ifndef CONSTANTE_H
#define CONSTANTE_H

#include "Literal.h"
#include "OpndoConNombre.h"

class Constante : public virtual OpndoConNombre, public virtual Literal
  {
  public:
    Constante(void) : OpndoConNombre() {}
    Constante(const std::string &nmb,const double &d): OpndoConNombre(nmb,d) {}
    Constante(const Constante &otro): OpndoConNombre(otro) {}
    Constante &operator=(const Constante &otro)
      {
        OpndoConNombre::operator =(otro);
        return *this;
      }
    virtual bool Evaluable(void) const
      { return Literal::Evaluable(); }
    friend int operator <(const Constante &c1,const Constante &c2)
      { return ((const Literal &)c1 < (const Literal &)c2); }
    virtual Rama Diferencia(const Variable &v,const Rama &) const;
  };

#endif

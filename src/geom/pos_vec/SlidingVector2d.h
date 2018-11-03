//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
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
//SlidingVector2d.h

#ifndef VDESLIZ2D_H
#define VDESLIZ2D_H


#include "Pos2d.h"
#include "Vector2d.h"
#include "xc_utils/src/utils/misc_utils/mchne_eps.h"


//! @ingroup GEOM
//
//! @brief sliding vector en dos dimensiones.
class SlidingVector2d : public Vector2d
  {
    Pos2d org; //Point that fixes the line of action.
  public:
    SlidingVector2d(const Pos2d &o= Pos2d(),const Vector2d &v= Vector2d())
      : Vector2d(v), org(o) {}
    SlidingVector2d(const Pos2d &o,const Pos2d &p);
    SlidingVector2d(const SlidingVector2d &other)
      : Vector2d(other), org(other.org) {}
    SlidingVector2d &operator=(const SlidingVector2d &other)
      {
        Vector2d::operator=(other);
        org= other.org;
        return *this;
      }
    GEOM_FT getMoment(const Pos2d &o) const;
    const Pos2d &getOrg(void) const
      { return org; }
    const Pos2d getDest(void) const
      { return org+(const Vector2d &)(*this); }
    const Vector2d &getVector(void) const
      { return *this; }
    friend SlidingVector2d operator*(const SlidingVector2d &m,const GEOM_FT &p)
      { return SlidingVector2d(m.getOrg(),m.getVector()*p); }
    friend SlidingVector2d operator*(const GEOM_FT &p,const SlidingVector2d &m)
      { return m*p; }
    friend SlidingVector2d operator/(const SlidingVector2d &m,const GEOM_FT &p);
    friend std::ostream &operator<<(std::ostream &os,const SlidingVector2d &v)
      {
        os << (const Vector2d &) v;
        os << " (O=" << v.org << ')';
        return os;
      }
  };

SlidingVector2d operator-(const SlidingVector2d &v);

inline GEOM_FT Abs(const SlidingVector2d &v)
  { return v.GetModulus(); }

#endif

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
//VDesliz2d.h

#ifndef VDESLIZ2D_H
#define VDESLIZ2D_H


#include "Pos2d.h"
#include "Vector2d.h"
#include "xc_basic/src/util/mchne_eps.h"


//! @ingroup GEOM
//
//! @brief Vector deslizante en dos dimensiones.
class VDesliz2d : public Vector2d
  {
    Pos2d org; //Punto que determina la línea de accion.
  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    VDesliz2d(const Pos2d &o= Pos2d(),const Vector2d &v= Vector2d())
      : Vector2d(v), org(o) {}
    VDesliz2d(const Pos2d &o,const Pos2d &p);
    VDesliz2d(const VDesliz2d &otro)
      : Vector2d(otro), org(otro.org) {}
    VDesliz2d &operator=(const VDesliz2d &otro)
      {
        Vector2d::operator=(otro);
        org= otro.org;
        return *this;
      }
    GEOM_FT Momento(const Pos2d &o) const;
      //Momento de un vector deslizante respecto a un punto.
    const Pos2d &getOrg(void) const
      { return org; }
    const Pos2d getDest(void) const
      { return org+(const Vector2d &)(*this); }
    const Vector2d &getVector(void) const
      { return *this; }
    virtual any_const_ptr GetProp(const std::string &cod) const;
    friend VDesliz2d operator*(const VDesliz2d &m,const GEOM_FT &p)
      { return VDesliz2d(m.getOrg(),m.getVector()*p); }
    friend VDesliz2d operator*(const GEOM_FT &p,const VDesliz2d &m)
      { return m*p; }
    friend VDesliz2d operator/(const VDesliz2d &m,const GEOM_FT &p);
    friend std::ostream &operator<<(std::ostream &os,const VDesliz2d &v)
      {
        os << (const Vector2d &) v;
        os << " (O=" << v.org << ')';
        return os;
      }
  };

VDesliz2d operator-(const VDesliz2d &v);

inline GEOM_FT Abs(const VDesliz2d &v)
  { return v.GetModulus(); }

#endif

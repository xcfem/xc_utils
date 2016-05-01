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
//VDesliz3d.h

#ifndef VDESLIZ3D_H
#define VDESLIZ3D_H


#include "Pos3d.h"
#include "Vector3d.h"
#include "xc_basic/src/util/mchne_eps.h"

class Recta3d;

//! @ingroup GEOM
//
//! @brief Vector deslizante en tres dimensiones.
class VDesliz3d : public Vector3d
  {
  protected:
    Pos3d org; //!< Punto que determina la línea de accion.
  public:
    VDesliz3d(const Pos3d &o= Pos3d(),const Vector3d &v= Vector3d());
    VDesliz3d(const Pos3d &o,const Pos3d &p);
    VDesliz3d getMomento(const Pos3d &o) const;
    GEOM_FT getMomento(const Recta3d &e) const;
    const Pos3d &getOrg(void) const;
    const Pos3d getDest(void) const;
    const Vector3d &getVector(void) const;
    VDesliz3d &operator*=(const GEOM_FT &);
    friend VDesliz3d operator*(const VDesliz3d &m,const GEOM_FT &p);
    friend VDesliz3d operator*(const GEOM_FT &p,const VDesliz3d &m);
    friend VDesliz3d operator/(const VDesliz3d &m,const GEOM_FT &p);
    friend std::ostream &operator<<(std::ostream &os,const VDesliz3d &v);
  };

VDesliz3d operator*(const VDesliz3d &m,const GEOM_FT &p);
VDesliz3d operator*(const GEOM_FT &p,const VDesliz3d &m);
VDesliz3d operator/(const VDesliz3d &m,const GEOM_FT &p);
std::ostream &operator<<(std::ostream &os,const VDesliz3d &v);
VDesliz3d operator-(const VDesliz3d &v);

inline GEOM_FT Abs(const VDesliz3d &v)
  { return v.GetModulus(); }

#endif

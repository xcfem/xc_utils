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
//SlidingVector3d.h

#ifndef VDESLIZ3D_H
#define VDESLIZ3D_H


#include "Pos3d.h"
#include "Vector3d.h"
#include "xc_basic/src/util/mchne_eps.h"

class Line3d;

//! @ingroup GEOM
//
//! @brief sliding vector en tres dimensiones.
class SlidingVector3d : public Vector3d
  {
  protected:
    Pos3d org; //!< Point that fix the line of action.
  public:
    SlidingVector3d(const Pos3d &o= Pos3d(),const Vector3d &v= Vector3d());
    SlidingVector3d(const Pos3d &o,const Pos3d &p);
    SlidingVector3d getMoment(const Pos3d &o) const;
    GEOM_FT getMoment(const Line3d &e) const;
    const Pos3d &getOrg(void) const;
    const Pos3d getDest(void) const;
    const Vector3d &getVector(void) const;
    SlidingVector3d &operator*=(const GEOM_FT &);
    friend SlidingVector3d operator*(const SlidingVector3d &m,const GEOM_FT &p);
    friend SlidingVector3d operator*(const GEOM_FT &p,const SlidingVector3d &m);
    friend SlidingVector3d operator/(const SlidingVector3d &m,const GEOM_FT &p);
    friend std::ostream &operator<<(std::ostream &os,const SlidingVector3d &v);
  };

SlidingVector3d operator*(const SlidingVector3d &m,const GEOM_FT &p);
SlidingVector3d operator*(const GEOM_FT &p,const SlidingVector3d &m);
SlidingVector3d operator/(const SlidingVector3d &m,const GEOM_FT &p);
std::ostream &operator<<(std::ostream &os,const SlidingVector3d &v);
SlidingVector3d operator-(const SlidingVector3d &v);

inline GEOM_FT Abs(const SlidingVector3d &v)
  { return v.GetModulus(); }

#endif

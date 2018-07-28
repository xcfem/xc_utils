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
//HalfSpace3d.h

#ifndef HALFSPACE3D_H
#define HALFSPACE3D_H


#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_basic/src/stl/TripletMap.h"



//! @ingroup GEOM
//
//! @brief The points of the half space are those that line
//! at the back of the plane, this being understood as those that
//! return a zero or negative value when evaluating on them the
//! general equation of the plane, i. e.:
//!
//! A*x_i+B*y_i+C*z_i+D <= 0
//!
//! with the point coordinates: (x_i,y_i,z_i).
class HalfSpace3d : public GeomObj3d
  {
    Plane lim; 
  public:
    HalfSpace3d(const Plane &p= Plane());
    const Plane &getBoundaryPlane(void) const;
    void setBoundaryPlane(const Plane &);
    
    virtual GeomObj *clon(void) const
      { return new HalfSpace3d(*this); }
    inline void Swap(void)
      { lim.Swap(); }
    HalfSpace3d GetSwap(void) const
      {
        HalfSpace3d retval(*this);
        retval.Swap();
        return retval;
      }
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }
    Vector3d NormalExterior(void) const;
    Vector3d NormalInterior(void) const;
    inline const Plane &getPlane(void) const
      { return lim; }

    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;
    GEOM_FT distSigno(const Pos3d &) const;
    GEOM_FT distSigno2(const Pos3d &p) const;
    virtual GEOM_FT dist(const Pos3d &p) const;
    virtual GEOM_FT dist2(const Pos3d &p) const;

    GEOM_FT getAngle(const HalfSpace3d &) const;
    GEOM_FT getAngle(const Plane &) const;
    GEOM_FT getAngle(const Vector3d &) const;

    Recta3d getLima(const HalfSpace3d &) const;

    virtual unsigned short int Dimension(void) const;
    virtual GEOM_FT getLength(void) const;
    virtual GEOM_FT getArea(void) const;
    virtual GEOM_FT getVolume(void) const;
    virtual Pos3d getCenterOfMass(void) const;
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;
    friend bool operator==(const HalfSpace3d &r1,const HalfSpace3d &r2);
    void Print(std::ostream &os) const;
  };

bool operator==(const HalfSpace3d &r1,const HalfSpace3d &r2);

inline GEOM_FT dist(const Pos3d &p,const HalfSpace3d &r)
  { return r.dist(p); }
inline GEOM_FT dist(const HalfSpace3d &r,const Pos3d &p)
  { return dist(p,r); }
inline bool operator!=(const HalfSpace3d &r1,const HalfSpace3d &r2)
  { return !(r1==r2); }

TripletMap<Pos3d> intersection_points(const std::deque<HalfSpace3d> &);
TripletMap<Pos3d> vertices_poliedro(const std::deque<HalfSpace3d> &, const double &tol= 1e-10);
std::deque<Recta3d> rectas_intersection(const std::deque<HalfSpace3d> &);
std::deque<Vector3d> vectores_normales(const std::deque<HalfSpace3d> &);

GEOM_FT angle(const HalfSpace3d &,const HalfSpace3d &);
GEOM_FT angle(const Vector3d &,const HalfSpace3d &);
GEOM_FT angle(const HalfSpace3d &,const Vector3d &);

#endif

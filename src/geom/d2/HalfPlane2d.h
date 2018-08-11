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
//HalfPlane2d.h

#ifndef HALFPLANE2D_H
#define HALFPLANE2D_H


#include "xc_utils/src/geom/d1/Line2d.h"
#include "xc_utils/src/geom/d2/Surface2d.h"

class GeomGroup2d;
class Ray2d;
class Segment2d;


//! @ingroup GEOM
//
//! @brief Half plane in a two-dimensional space.
class HalfPlane2d : public Surface2d
  {
    Line2d lim; //The points of the half-plane are those we lie to the right of the line.
  public:
    HalfPlane2d(void);
    explicit HalfPlane2d(const Line2d &r);
    HalfPlane2d(const Line2d &r, const Pos2d &p);
    HalfPlane2d(const Pos2d &p1,const Pos2d &p2);
    HalfPlane2d(const HalfPlane2d &sp);
    HalfPlane2d &operator=(const HalfPlane2d &sp);
    virtual GeomObj *clon(void) const;
    inline void Swap(void);
    HalfPlane2d GetSwap(void) const;

    //! @brief Return the value of a that corresponds to the
    //! equation of the line: a*x + b*y + c= 0
    inline GEOM_RT a(void) const
      { return lim.a(); }
    //! @brief Return the value of b that corresponds to the
    //! equation of the line: a*x + b*y + c= 0
    inline GEOM_RT b(void) const
      { return lim.b(); }
    //! @brief Return the value of c that corresponds to the
    //! equation of the line: a*x + b*y + c= 0
    inline GEOM_RT c(void) const
      { return lim.c(); } 
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }
    inline bool EsDegenerado(void) const
      { return lim.EsDegenerada(); }
    inline const Line2d &getBorde(void) const
      { return lim; }
    //! @brief Return true if the point is inside the half-plane.
    //! The points of the edge line belong to the half-plane.
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const
      { 
        if(lim.In(p,tol)) return true;
        if(lim.LadoDerecho(p)) return true;
        return false;
      }
    //! @brief Return the signed distance from the point to the half-plane.
    GEOM_FT DistSigno(const Pos2d &p) const
      {
        GEOM_FT retval= lim.dist(p);
        if(In(p)) retval= -retval;
        return retval;
      }
    //! @brief Return the distance from the point to the half-plane.
    inline virtual GEOM_FT Dist(const Pos2d &p) const
      { return fabs(DistSigno(p)); }

    HalfPlane2d getNormalizado(void) const;

    inline bool intersects(const HalfPlane2d &r2) const
      { return lim.intersects(r2.lim); }
    inline bool intersects(const Line2d &r) const
      { return lim.intersects(r); }
    bool intersects(const Ray2d &sr) const;
    bool intersects(const Segment2d &sg) const;
    GeomGroup2d getIntersection(const Line2d &r) const;
    GeomGroup2d getIntersection(const Ray2d &sr) const;
    GeomGroup2d getIntersection(const Segment2d &sg) const;

    //! @brief Return the length of the object.
    inline virtual GEOM_FT getLength(void) const
      { return NAN; }
    inline virtual Pos2d getCenterOfMass(void) const
      { return lim.getCenterOfMass(); }
    //Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Ix(void) const
      { return NAN; }
    //Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //product of inertia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }

    void Transforma(const Trf2d &trf2d);

    inline friend bool operator==(const HalfPlane2d &r1,const HalfPlane2d &r2)
      {
        if(&r1.lim==&r2.lim) return true;
        else
          return (r1.lim==r2.lim); 
      }
    inline void Print(std::ostream &os) const
      { os << lim; }
  };

inline GEOM_FT dist(const Pos2d &p,const HalfPlane2d &r)
  { return r.Dist(p); }
inline GEOM_FT dist(const HalfPlane2d &r,const Pos2d &p)
  { return dist(p,r); }
inline bool operator!=(const HalfPlane2d &r1,const HalfPlane2d &r2)
  { return !(r1==r2); }

inline bool intersecan(const HalfPlane2d &sp1,const HalfPlane2d &sp2)
  { return sp1.intersects(sp2); }
inline bool intersecan(const HalfPlane2d &sp,const Line2d &r)
  { return sp.intersects(r); }
inline bool intersecan(const HalfPlane2d &sp,const Ray2d &sr)
  { return sp.intersects(sr); }
inline bool intersecan(const HalfPlane2d &sp,const Segment2d &sg)
  { return sp.intersects(sg); }
inline bool intersecan(const Line2d &r,const HalfPlane2d &sp)
  { return sp.intersects(r); }
inline bool intersecan(const Ray2d &sr,const HalfPlane2d &sp)
  { return sp.intersects(sr); }
inline bool intersecan(const Segment2d &sg,const HalfPlane2d &sp)
  { return sp.intersects(sg); }

GeomGroup2d intersection(const HalfPlane2d &sp,const Line2d &r);
GeomGroup2d intersection(const HalfPlane2d &sp,const Ray2d &sr);
GeomGroup2d intersection(const HalfPlane2d &sp,const Segment2d &sg);
GeomGroup2d intersection(const Line2d &r,const HalfPlane2d &sp);
GeomGroup2d intersection(const Ray2d &sr,const HalfPlane2d &sp);
GeomGroup2d intersection(const Segment2d &sg,const HalfPlane2d &sp);

#endif

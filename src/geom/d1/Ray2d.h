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
//Ray2d.h

#ifndef RAY2D_H
#define RAY2D_H

#include "Linear2d.h"
#include "Line2d.h"
#include "../pos_vec/Pos2d.h"

class Dir2d;

//! @ingroup GEOM
//
//! @brief Ray in a two-dimensional space.
class Ray2d : public Linear2d
  {
    CGRay_2 cgsr;

    friend class Segment2d;
  public:
    Ray2d(void): Linear2d(),cgsr(CGPoint_2(0,0),CGPoint_2(1,0)) {}
    Ray2d(const CGRay_2 &r)
      : Linear2d(), cgsr(r) {}
    Ray2d(const Pos2d &p1,const Pos2d &p2);
    Ray2d(const Pos2d &p1,const Vector2d &vdir);
    Ray2d(const Ray2d &r)
      : Linear2d(),cgsr(r.cgsr) {}
    Ray2d &operator=(const Ray2d &r)
      {
	Linear2d::operator=(r);
        cgsr= r.cgsr;
        return *this;
      }
    const CGRay_2 &ToCGAL(void) const
      { return cgsr; }
    virtual GeomObj *clon(void) const
      { return new Ray2d(*this); }
    void TwoPoints(const Pos2d &p1,const Pos2d &p2);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }
    Line2d getSupportLine(void) const
      { return Line2d(cgsr.supporting_line()); }
    Pos2d Origen(void) const
      { return Pos2d(cgsr.source()); }
    inline GEOM_FT getSlope(void) const
      { return getSupportLine().getSlope(); }
    const Pos2d Point(const int &i) const
      { return Pos2d(cgsr.point(i)); }
    //@brief Return a point of the line at a distance lambda from its origin.
    Pos2d PtoParametricas(const GEOM_FT &lambda) const
      { return Point(0)+lambda*VDir(); }
    inline bool EsVertical(void) const
      { return cgsr.is_vertical(); }
    inline bool EsDegenerada(void) const
      { return cgsr.is_degenerate(); }
    //@brief Return true if the points is on the ray.
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const
      { return cgsr.has_on(p.ToCGAL()); }
    GEOM_FT dist2(const Pos2d &p) const;
    GEOM_FT dist(const Pos2d &p) const;
    //! @brief Set the points that define the ray.
    void Put(const Pos2d &p1,const Pos2d &p2)
      { TwoPoints(p1,p2); }

    //! @brief Returns the points ordered by the value of the 
    //! parameter of its projection onto the line from lowest
    //! to highest. Origin is at Line2d::Point(0).
    GeomObj::list_Pos2d Ordena(const GeomObj::list_Pos2d &ptos) const
      { return getSupportLine().Ordena(ptos); }

    bool intersects(const Ray2d &sr2) const
      { return do_intersect(cgsr,sr2.cgsr); }
    bool intersects(const Line2d &sr) const;
    GeomObj2d::list_Pos2d getIntersection(unsigned short int, const double &) const;
    GeomObj2d::list_Pos2d getIntersection(const Line2d &r) const;
    GeomObj2d::list_Pos2d getIntersection(const Ray2d &sr) const;

    bool Paralela(const Line2d &r) const
      { return paralelas(getSupportLine(),r); }
    bool Paralela(const Ray2d &sr) const
      { return Paralela(sr.getSupportLine()); }

    //! @brief Return the length of the object.
    inline virtual GEOM_FT getLength(void) const
      { return NAN; }
    inline virtual Pos2d getCenterOfMass(void) const
      { return Pos2d(NAN,NAN); }
    Dir2d GetDir(void) const;
    Vector2d VDir(void) const;
    inline GEOM_FT getAngle(const Vector2d &v) const
      { return angle(VDir(),v); }
    inline friend GEOM_FT angle(const Ray2d &r,const Vector2d &v)
      { return r.getAngle(v); }
    //Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Ix(void) const
      { return 0.0; }
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

    inline friend bool operator==(const Ray2d &r1,const Ray2d &r2)
      { return (r1.cgsr==r2.cgsr); }
    void Print(std::ostream &os) const;
    void Plot(Plotter &psos) const;
  };

inline GEOM_FT dist2(const Pos2d &p,const Ray2d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const Ray2d &r,const Pos2d &p)
  { return dist2(p,r); }
inline GEOM_FT dist(const Pos2d &p,const Ray2d &r)
  { return r.dist(p); }
inline GEOM_FT dist(const Ray2d &r,const Pos2d &p)
  { return dist(p,r); }

inline bool paralelas(const Ray2d &sr,const Line2d &r)
  { return sr.Paralela(r); }
inline bool paralelas(const Line2d &r,const Ray2d &sr)
  { return paralelas(sr,r); }
inline bool paralelas(const Ray2d &r1,const Ray2d &r2)
  { return r1.Paralela(r2); }

inline bool intersecan(const Ray2d &sr1,const Ray2d &sr2)
  { return sr1.intersects(sr2); }
inline bool intersecan(const Ray2d &sr,const Line2d &r)
  { return sr.intersects(r); }
inline bool intersecan(const Line2d &r,const Ray2d &sr)
  { return sr.intersects(r); }
inline GeomObj2d::list_Pos2d intersection(const Ray2d &sr,const Line2d &r)
  { return sr.getIntersection(r); }
inline GeomObj2d::list_Pos2d intersection(const Line2d &r, const Ray2d &sr)
  { return sr.getIntersection(r); }

//! @brief Return the intersection point of both lines, if it does not exists
//! return an empty list.
inline GeomObj2d::list_Pos2d intersection(const Ray2d &sr1,const Ray2d &sr2)
  { return sr1.getIntersection(sr2); }


inline bool colineales(const Ray2d &sr,const Line2d &r)
  { return colineales(sr.getSupportLine(),r); }
inline bool colineales(const Line2d &r,const Ray2d &sr)
  { return colineales(sr,r); }
inline bool colineales(const Ray2d &sr1,const Ray2d &sr2)
  { return colineales(sr1,sr2.getSupportLine()); }


#endif

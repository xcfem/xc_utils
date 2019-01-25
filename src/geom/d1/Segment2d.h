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
//Segment2d.h

#ifndef SEGMENT2D_H
#define SEGMENT2D_H

#include "Linear2d.h"
#include "Line2d.h"
#include "Ray2d.h"
#include "../pos_vec/Pos2d.h"

class Dir2d;
class VectorPos2d;

//! @ingroup GEOM
//
//! @brief Segment in a two-dimensional space.
class Segment2d : public Linear2d
  {
    CGSegment_2 cgseg;
  public:
    Segment2d(void): Linear2d(),cgseg(CGPoint_2(0,0),CGPoint_2(1,0)) {}
    Segment2d(const CGSegment_2 &r)
      : Linear2d(), cgseg(r) {}
    Segment2d(const Pos2d &p1,const Pos2d &p2);
    Segment2d(const Segment2d &r)
      : Linear2d(),cgseg(r.cgseg) {}
    Segment2d &operator=(const Segment2d &r)
      {
	Linear2d::operator=(r);
        cgseg= r.cgseg;
        return *this;
      }
    const CGSegment_2 &ToCGAL(void) const
      { return cgseg; }
    virtual GeomObj *clon(void) const;
    void TwoPoints(const Pos2d &p1,const Pos2d &p2);
    virtual GEOM_FT GetMax(unsigned short int i) const
      { return std::max(getFromPoint()(i),getToPoint()(i)); }
    virtual GEOM_FT GetMin(unsigned short int i) const
      { return std::min(getFromPoint()(i),getToPoint()(i)); }
    Line2d getSupportLine(void) const
      { return Line2d(cgseg.supporting_line()); }
    Pos2d getFromPoint(void) const
      { return Pos2d(cgseg.source()); }
    Pos2d getToPoint(void) const
      { return Pos2d(cgseg.target()); }
    inline GEOM_FT getSlope(void) const
      { return getSupportLine().getSlope(); }
    const Pos2d Point(const int &i) const
      { return Pos2d(cgseg.point(i)); }
    Pos2d PtoParametricas(const GEOM_FT &) const;
    double getParamCooNatural(const GEOM_FT &) const;
    Pos2d PtoCooNatural(const GEOM_FT &) const;
    inline bool EsVertical(void) const
      { return cgseg.is_vertical(); }
    inline bool EsDegenerada(void) const
      { return cgseg.is_degenerate(); }
    virtual bool In(const Pos2d &, const double &tol= 0.0) const;
    virtual GEOM_FT dist2(const Pos2d &p) const;
    GEOM_FT dist(const Pos2d &p) const;
    //! @brief Set the points that define the segment.
    void Put(const Pos2d &p1,const Pos2d &p2)
      { TwoPoints(p1,p2); }

    //! @brief Returns the points ordered by the value of the 
    //! parameter of its projection onto the line from lowest
    //! to highest. Origin is at Line2d::Point(0).
    GeomObj::list_Pos2d Ordena(const GeomObj::list_Pos2d &ptos) const
      { return getSupportLine().Ordena(ptos); }

    Segment2d Offset(const Vector2d &v) const;
    Segment2d Offset(const GEOM_FT &d) const;

    inline bool intersects(const Segment2d &r2) const
      { return do_intersect(cgseg,r2.cgseg); }
    bool intersects(const Line2d &r) const;
    bool intersects(const Ray2d &sr) const;
    GeomObj2d::list_Pos2d getIntersection(unsigned short int, const double &) const;
    GeomObj2d::list_Pos2d getIntersection(const Line2d &r) const;
    GeomObj2d::list_Pos2d getIntersection(const Ray2d &sr) const;
    GeomObj2d::list_Pos2d getIntersection(const Segment2d &sg2) const;

    Line2d Perpendicular(const Pos2d &p) const;
    Line2d Paralela(const Pos2d &v) const;
    Line2d getPerpendicularBisector(void) const;

    bool Paralelo(const Line2d &r) const
      { return paralelas(getSupportLine(),r); }
    bool Paralelo(const Ray2d &sr) const
      { return paralelas(getSupportLine(),sr); }
    bool Paralelo(const Segment2d &r) const
      { return paralelas(getSupportLine(),r.getSupportLine()); }

    virtual GEOM_FT getLength(void) const;
    virtual Pos2d getCenterOfMass(void) const;
    Dir2d GetDir(void) const;
    Vector2d VDir(void) const;
    Vector2d Normal(void) const;
    Vector2d GetVector(void) const;
    GEOM_FT getAngle(const Vector2d &v) const;
    GEOM_FT getSignedAngle(const Vector2d &v) const;
    GEOM_FT getAngle(const Segment2d &v) const;
    GEOM_FT getSignedAngle(const Segment2d &v) const;
    GEOM_FT XAxisAngle(void) const;
    GEOM_FT YAxisAngle(void) const;
    inline GEOM_FT Azimuth(void) const
      { return getSupportLine().Azimuth(); }

    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Ix(void) const
      { return 0.0; }
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //! @brief Product of inertia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }
    VectorPos2d Divide(int num_partes) const;

    void Transform(const Trf2d &trf2d);

    inline friend bool operator==(const Segment2d &r1,const Segment2d &r2)
      { return (r1.cgseg==r2.cgseg); }
    void Print(std::ostream &os) const;
    void Plot(Plotter &) const;
  };

inline GEOM_FT dist2(const Pos2d &p,const Segment2d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const Segment2d &r,const Pos2d &p)
  { return dist2(p,r); }
GEOM_FT dist(const Pos2d &p,const Segment2d &r);
inline GEOM_FT dist(const Segment2d &r,const Pos2d &p)
  { return dist(p,r); }

GEOM_FT angle(const Segment2d &,const Vector2d &);
GEOM_FT angle(const Vector2d &,const Segment2d &);

inline bool paralelas(const Segment2d &sg,const Line2d &r)
  { return sg.Paralelo(r); }
inline bool paralelas(const Line2d &r, const Segment2d &sg)
  { return paralelas(sg,r); }
inline bool paralelas(const Segment2d &sg,const Ray2d &sr)
  { return sg.Paralelo(sr); }
inline bool paralelas(const Ray2d &sr, const Segment2d &sg)
  { return paralelas(sg,sr); }
inline bool paralelas(const Segment2d &r1,const Segment2d &r2)
  { return r1.Paralelo(r2); }

inline bool intersecan(const Segment2d &sg,const Line2d &r)
  { return sg.intersects(r); }
inline bool intersecan(const Line2d &r,const Segment2d &sg)
  { return sg.intersects(r); }
inline bool intersecan(const Segment2d &sg,const Ray2d &sr)
  { return sg.intersects(sr); }
inline bool intersecan(const Ray2d &sr,const Segment2d &sg)
  { return sg.intersects(sr); }
inline bool intersecan(const Segment2d &r1,const Segment2d &r2)
  { return r1.intersects(r2); }
inline GeomObj2d::list_Pos2d intersection(const Segment2d &sg,const Line2d &r)
  { return sg.getIntersection(r); }
inline GeomObj2d::list_Pos2d intersection(const Line2d &r,const Segment2d &sg)
  { return sg.getIntersection(r); }
inline GeomObj2d::list_Pos2d intersection(const Segment2d &sg,const Ray2d &sr)
  { return sg.getIntersection(sr); }
inline GeomObj2d::list_Pos2d intersection(const Ray2d &sr,const Segment2d &sg)
  { return sg.getIntersection(sr); }
inline GeomObj2d::list_Pos2d intersection(const Segment2d &sg1,const Segment2d &sg2)
  { return sg1.getIntersection(sg2); }

inline bool colineales(const Segment2d &sg,const Line2d &r)
  { return colineales(sg.getSupportLine(),r); }
inline bool colineales(const Line2d &r,const Segment2d &sg)
  { return colineales(sg,r); }
inline bool colineales(const Segment2d &sg,const Ray2d &sr)
  { return colineales(sg.getSupportLine(),sr); }
inline bool colineales(const Ray2d &sr,const Segment2d &sg)
  { return colineales(sg,sr); }
inline bool colineales(const Segment2d &sg1,const Segment2d &sg2)
  { return colineales(sg1,sg2.getSupportLine()); }

Pos2d intersection_point(const Segment2d &, const Line2d &);
Pos2d intersection_point(const Line2d &, const Segment2d &);
Pos2d intersection_point(const Segment2d &, const Segment2d &);

inline Line2d perpendicular_bisector(const Segment2d &sg)
  { return sg.getPerpendicularBisector(); }

std::list<Segment2d> sin_degenerados(const std::list<Segment2d> &);


#endif

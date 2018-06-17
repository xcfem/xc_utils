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

#include "Linea2d.h"
#include "Recta2d.h"
#include "SemiRecta2d.h"
#include "../pos_vec/Pos2d.h"

class Dir2d;
class VectorPos2d;

//! @ingroup GEOM
//
//! @brief Segment in a two-dimensional space.
class Segment2d : public Linea2d
  {
    CGSegment_2 cgseg;
  public:
    Segment2d(void): Linea2d(),cgseg(CGPoint_2(0,0),CGPoint_2(1,0)) {}
    Segment2d(const CGSegment_2 &r)
      : Linea2d(), cgseg(r) {}
    Segment2d(const Pos2d &p1,const Pos2d &p2);
    Segment2d(const Segment2d &r)
      : Linea2d(),cgseg(r.cgseg) {}
    Segment2d &operator=(const Segment2d &r)
      {
	Linea2d::operator=(r);
        cgseg= r.cgseg;
        return *this;
      }
    const CGSegment_2 &ToCGAL(void) const
      { return cgseg; }
    virtual GeomObj *clon(void) const;
    void TwoPoints(const Pos2d &p1,const Pos2d &p2);
    virtual GEOM_FT GetMax(unsigned short int i) const
      { return std::max(Origen()(i),Destino()(i)); }
    virtual GEOM_FT GetMin(unsigned short int i) const
      { return std::min(Origen()(i),Destino()(i)); }
    Recta2d RectaSoporte(void) const
      { return Recta2d(cgseg.supporting_line()); }
    Pos2d Origen(void) const
      { return Pos2d(cgseg.source()); }
    Pos2d Destino(void) const
      { return Pos2d(cgseg.target()); }
    inline GEOM_FT getSlope(void) const
      { return RectaSoporte().getSlope(); }
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
    //! to highest. Origin is at Recta2d::Point(0).
    GeomObj::list_Pos2d Ordena(const GeomObj::list_Pos2d &ptos) const
      { return RectaSoporte().Ordena(ptos); }

    Segment2d Offset(const Vector2d &v) const;
    Segment2d Offset(const GEOM_FT &d) const;

    inline bool intersects(const Segment2d &r2) const
      { return do_intersect(cgseg,r2.cgseg); }
    bool intersects(const Recta2d &r) const;
    bool intersects(const SemiRecta2d &sr) const;
    GeomObj2d::list_Pos2d getIntersection(unsigned short int, const double &) const;
    GeomObj2d::list_Pos2d getIntersection(const Recta2d &r) const;
    GeomObj2d::list_Pos2d getIntersection(const SemiRecta2d &sr) const;
    GeomObj2d::list_Pos2d getIntersection(const Segment2d &sg2) const;

    Recta2d Perpendicular(const Pos2d &p) const;
    Recta2d Paralela(const Pos2d &v) const;
    Recta2d Mediatriz(void) const;

    bool Paralelo(const Recta2d &r) const
      { return paralelas(RectaSoporte(),r); }
    bool Paralelo(const SemiRecta2d &sr) const
      { return paralelas(RectaSoporte(),sr); }
    bool Paralelo(const Segment2d &r) const
      { return paralelas(RectaSoporte(),r.RectaSoporte()); }

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
      { return RectaSoporte().Azimuth(); }

    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Ix(void) const
      { return 0.0; }
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //Producto de inercia.
    inline virtual GEOM_FT Pxy(void) const
      { return NAN; }
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }
    VectorPos2d Divide(int num_partes) const;

    void Transforma(const Trf2d &trf2d);

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

inline bool paralelas(const Segment2d &sg,const Recta2d &r)
  { return sg.Paralelo(r); }
inline bool paralelas(const Recta2d &r, const Segment2d &sg)
  { return paralelas(sg,r); }
inline bool paralelas(const Segment2d &sg,const SemiRecta2d &sr)
  { return sg.Paralelo(sr); }
inline bool paralelas(const SemiRecta2d &sr, const Segment2d &sg)
  { return paralelas(sg,sr); }
inline bool paralelas(const Segment2d &r1,const Segment2d &r2)
  { return r1.Paralelo(r2); }

inline bool intersecan(const Segment2d &sg,const Recta2d &r)
  { return sg.intersects(r); }
inline bool intersecan(const Recta2d &r,const Segment2d &sg)
  { return sg.intersects(r); }
inline bool intersecan(const Segment2d &sg,const SemiRecta2d &sr)
  { return sg.intersects(sr); }
inline bool intersecan(const SemiRecta2d &sr,const Segment2d &sg)
  { return sg.intersects(sr); }
inline bool intersecan(const Segment2d &r1,const Segment2d &r2)
  { return r1.intersects(r2); }
inline GeomObj2d::list_Pos2d intersection(const Segment2d &sg,const Recta2d &r)
  { return sg.getIntersection(r); }
inline GeomObj2d::list_Pos2d intersection(const Recta2d &r,const Segment2d &sg)
  { return sg.getIntersection(r); }
inline GeomObj2d::list_Pos2d intersection(const Segment2d &sg,const SemiRecta2d &sr)
  { return sg.getIntersection(sr); }
inline GeomObj2d::list_Pos2d intersection(const SemiRecta2d &sr,const Segment2d &sg)
  { return sg.getIntersection(sr); }
inline GeomObj2d::list_Pos2d intersection(const Segment2d &sg1,const Segment2d &sg2)
  { return sg1.getIntersection(sg2); }

inline bool colineales(const Segment2d &sg,const Recta2d &r)
  { return colineales(sg.RectaSoporte(),r); }
inline bool colineales(const Recta2d &r,const Segment2d &sg)
  { return colineales(sg,r); }
inline bool colineales(const Segment2d &sg,const SemiRecta2d &sr)
  { return colineales(sg.RectaSoporte(),sr); }
inline bool colineales(const SemiRecta2d &sr,const Segment2d &sg)
  { return colineales(sg,sr); }
inline bool colineales(const Segment2d &sg1,const Segment2d &sg2)
  { return colineales(sg1,sg2.RectaSoporte()); }

Pos2d intersection_point(const Segment2d &, const Recta2d &);
Pos2d intersection_point(const Recta2d &, const Segment2d &);
Pos2d intersection_point(const Segment2d &, const Segment2d &);

inline Recta2d mediatriz(const Segment2d &sg)
  { return sg.Mediatriz(); }

std::list<Segment2d> sin_degenerados(const std::list<Segment2d> &);


#endif

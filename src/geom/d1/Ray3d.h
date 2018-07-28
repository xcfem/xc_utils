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
//Ray3d.h

#ifndef RAY3D_H
#define RAY3D_H

#include "Linea3d.h"
#include "Recta3d.h"
#include "../pos_vec/Pos3d.h"

class Dir3d;


//! @ingroup GEOM
//
//! @brief Ray in a three-dimensional space.
class Ray3d : public Linea3d
  {
    CGRay_3 cgsr;
  public:
    Ray3d(void): Linea3d(),cgsr(CGPoint_3(0,0,0),CGPoint_3(1,0,0)) {}
    Ray3d(const CGRay_3 &r)
      : Linea3d(), cgsr(r) {}
    Ray3d(const Pos3d &p1,const Pos3d &p2);
    Ray3d(const Ray3d &r)
      : Linea3d(),cgsr(r.cgsr) {}
    Ray3d &operator=(const Ray3d &r)
      {
	Linea3d::operator=(r);
        cgsr= r.cgsr;
        return *this;
      }

    virtual GeomObj *clon(void) const
      { return new Ray3d(*this); }
    const CGRay_3 &ToCGAL(void) const
      { return cgsr; }
    void TwoPoints(const Pos3d &p1,const Pos3d &p2);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }
    Recta3d RectaSoporte(void) const
      { return Recta3d(cgsr.supporting_line()); }
    Pos3d Origen(void) const
      { return Pos3d(cgsr.source()); }
    inline GEOM_FT getSlope(void) const
      { return RectaSoporte().getSlope(); }
    const Pos3d Point(const int &i) const
      { return Pos3d(cgsr.point(i)); }
    //! @brief Return a point of the line at a distance lambda from its origin.
    Pos3d PtoParametricas(const GEOM_FT &lambda) const
      { return Point(0)+lambda*VDir(); }
    inline bool EsDegenerada(void) const
      { return cgsr.is_degenerate(); }
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const
    //Return true if the point is on the object.
      { return cgsr.has_on(p.ToCGAL()); }
    virtual GEOM_FT dist2(const Pos3d &p) const;
    GEOM_FT dist(const Pos3d &p) const;
    //! @brief Set the points that define the line.
    void Put(const Pos3d &p1,const Pos3d &p2)
      { TwoPoints(p1,p2); }

    bool Paralela(const Ray3d &r) const;
    bool Paralela(const Recta3d &r) const;

    GeomObj3d::list_Pos3d getIntersection(unsigned short int, const double &) const;
    GeomObj3d::list_Pos3d getIntersection(const Recta3d &r) const;
    GeomObj3d::list_Pos3d getIntersection(const Ray3d &sr) const;

    inline virtual GEOM_FT getLength(void) const
      { return NAN; }
    inline virtual Pos3d getCenterOfMass(void) const
      { return Pos3d(NAN,NAN,NAN); }
    Dir3d GetDir(void) const;
    Vector3d VDir(void) const;
    inline double getAngle(const Vector3d &v) const
      { return angle(VDir(),v); }
    //Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Ix(void) const
      { return 0.0; }
    //Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }
    inline friend bool operator==(const Ray3d &r1,const Ray3d &r2)
      { return (r1.cgsr==r2.cgsr); }
    inline void Print(std::ostream &os) const
      { os << PtoParametricas(0.0) << " " << PtoParametricas(100.0); }
  };

inline GEOM_FT angle(const Ray3d &r,const Vector3d &v)
  { return r.getAngle(v); }
inline GEOM_FT angle(const Ray3d &sr,const Recta3d &r)
  { return r.getAngle(sr.VDir()); }
inline GEOM_FT angle(const Recta3d &r,const Ray3d &sr)
  { return r.getAngle(sr.VDir()); }

inline GEOM_FT dist2(const Pos3d &p,const Ray3d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const Ray3d &r,const Pos3d &p)
  { return r.dist2(p); }
inline GEOM_FT dist(const Pos3d &p,const Ray3d &r)
  { return r.dist(p); }
inline GEOM_FT dist(const Ray3d &r,const Pos3d &p)
  { return r.dist(p); }

inline bool paralelas(const Ray3d &r1,const Recta3d &r2)
  { return r1.Paralela(r2); }
inline bool paralelas(const Recta3d &r1,const Ray3d &r2)
  { return paralelas(r2,r1); }
inline bool paralelas(const Ray3d &r1,const Ray3d &r2)
  { return r1.Paralela(r2); }

inline GeomObj3d::list_Pos3d intersection(const Recta3d &r1,const Ray3d &r2)
  { return r2.getIntersection(r1); }
inline GeomObj3d::list_Pos3d intersection(const Ray3d &r1,const Recta3d &r2)
  { return r1.getIntersection(r2); }
inline GeomObj3d::list_Pos3d intersection(const Ray3d &r1,const Ray3d &r2)
  { return r1.getIntersection(r2); }


inline bool colineales(const Ray3d &sr,const Recta3d &r)
  { return colineales(sr.RectaSoporte(),r); }
inline bool colineales(const Recta3d &r,const Ray3d &sr)
  { return colineales(sr,r); }
inline bool colineales(const Ray3d &sr1,const Ray3d &sr2)
  { return colineales(sr1,sr2.RectaSoporte()); }



#endif

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
//Recta3d.h

#ifndef RECTA3D_H
#define RECTA3D_H

#include <cstdlib>
#include <cmath>
#include <bits/nan.h>
#include "xc_basic/src/util/matem.h"
#include "Linea3d.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"



//! @ingroup GEOM
//
//! @brief Recta 3D en paramétricas.
class RectaParametricas3d
  {
    Pos3d org; //Origen de la recta.
    Vector3d dir; //direction vector.
  public:
    RectaParametricas3d(const Pos3d &o,const Vector3d &d)
      : org(o), dir(d) {}
    inline const Pos3d &GetOrg(void) const
      { return org; }
    inline const Vector3d &GetDir(void) const
      { return dir; }
    //! @brief Return a point at a distance lambda from its origin.
    inline Pos3d getPoint(const GEOM_FT &lambda) const
      { return org+lambda*dir; }
  };

class Recta2d;
class Plane;
class Dir3d;


//! @ingroup GEOM
//
//! @brief Recta en tres dimensiones.
class Recta3d : public Linea3d
  {
    CGRecta_3 cgr;
    static const Pos3d defaultOrg;
    static const Pos3d defaultDest;
  public:
    Recta3d(void);
    explicit Recta3d(const CGRecta_3 &r);
    Recta3d(const Pos3d &p1,const Pos3d &p2);
    Recta3d(const Pos3d &p,const Dir3d &dir);
    Recta3d(const Plane &p1,const Plane &p2);
    Recta3d(const RectaParametricas3d &param);
    virtual GeomObj *clon(void) const
      { return new Recta3d(*this); }
    void TwoPoints(const Pos3d &p1,const Pos3d &p2);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int i) const
      { return NAN; }
    const CGRecta_3 &ToCGAL(void) const
      { return cgr; }
    inline Pos3d Point(const int &i=0) const
      { return Pos3d(cgr.point(i)); }

    double getLambda(unsigned short int i,const double &d,const Vector3d &i_) const;

    Pos3d Projection(const Pos3d &) const;
    Vector3d Projection(const Vector3d &) const;
    Recta3d XY3DProjection(void) const;
    Recta3d XZ3DProjection(void) const;
    Recta3d YZ3DProjection(void) const;

    Recta2d XY2DProjection(void) const;
    Recta2d XZ2DProjection(void) const;
    Recta2d YZ2DProjection(void) const;

    GEOM_FT getSlope(void) const;
    //! @brief Returns the parametric equations of the line as:
    //!   v[0]: point in the line.
    //!   v[1]: dir vector for the line.
    RectaParametricas3d GetParametricas(void) const
      { return RectaParametricas3d(Point(0),VDir()); }
    //! @brief Return a point at a distance lambda from its origin.
    Pos3d PtoParametricas(const GEOM_FT &lambda) const
      { return Point(0)+lambda*VDir(); }
    //! @brief Defines the line from its parametric equation.
    void Parametricas(const RectaParametricas3d &param)
      { TwoPoints(param.getPoint(0.0),param.getPoint(100.0)); }
    //! @brief Return true if the point is on the line.
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const
      { return cgr.has_on(p.ToCGAL()); }
    //! @brief Return the squared distance from the point to the line.
    virtual GEOM_FT dist2(const Pos3d &p) const
      { return p.dist2(Projection(p)); }
    virtual GEOM_FT dist(const Pos3d &p) const;

    Plane Perpendicular(const Pos3d &p) const;
    //! @brief Set the points that define the line.
    void Put(const Pos3d &p1,const Pos3d &p2)
      { TwoPoints(p1,p2); }
    bool Paralela(const Recta3d &r) const;

    bool Interseca(const Recta3d &r2) const;
    GeomObj3d::list_Pos3d Interseccion(unsigned short int, const double &) const;
    GeomObj3d::list_Pos3d Interseccion(const Recta3d &r2, const double &tol= sqrt_mchne_eps_dbl) const;

    //! @brief Return the length of the object.
   inline virtual GEOM_FT getLength(void) const
      { return NAN; }
    inline virtual Pos3d getCenterOfMass(void) const
      { return Pos3d(NAN,NAN,NAN); }
    Dir3d GetDir(void) const;
    Vector3d VDir(void) const;
    inline double Angulo(const Vector3d &v) const
      { return angulo(VDir(),v); }
    inline friend double angulo(const Recta3d &r,const Vector3d &v)
      { return r.Angulo(v); }
    inline friend double angulo(const Recta3d &r1,const Recta3d &r2)
      { return r1.Angulo(r2.VDir()); }
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Ix(void) const
      { return 0.0; }
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //! @brief Moment of inertia with respect to the center of mass en local axis.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }
    void Print(std::ostream &os) const;
  };

const Recta3d XAxis3d(Pos3d(0,0,0),Pos3d(1,0,0));
const Recta3d YAxis3d(Pos3d(0,0,0),Pos3d(0,1,0));
const Recta3d ZAxis3d(Pos3d(0,0,0),Pos3d(0,0,1));


inline GEOM_FT dist2(const Pos3d &p,const Recta3d &r)
  { return r.dist2(p); }
inline GEOM_FT dist2(const Recta3d &r,const Pos3d &p)
  { return dist2(p,r); }
GEOM_FT dist(const Pos3d &p,const Recta3d &r);
inline GEOM_FT dist(const Recta3d &r,const Pos3d &p)
  { return dist(p,r); }

inline bool paralelas(const Recta3d &r1,const Recta3d &r2)
  { return r1.Paralela(r2); }
bool colineales(const Recta3d &r1,const Recta3d &r2);
bool coplanarias(const Recta3d &r1,const Recta3d &r2);

inline bool intersecan(const Recta3d &r1,const Recta3d &r2)
  { return r1.Interseca(r2); }
inline GeomObj3d::list_Pos3d interseccion(const Recta3d &r1,const Recta3d &r2)
  { return r1.Interseccion(r2); }


#endif

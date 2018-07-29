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
//Line2d.h

#ifndef LINE2D_H
#define LINE2D_H

#include "Linear2d.h"
#include "../pos_vec/Pos2d.h"
#include "../pos_vec/Vector2d.h"



//! @ingroup GEOM
//
//! @brief Line in a two-dimensional space (parametric form).
class Line2dParametricForm
  {
    Pos2d org; //!< Line origin.
    Vector2d dir; //!< direction vector.
  public:
    Line2dParametricForm(const Pos2d &o,const Vector2d &d)
      : org(o), dir(d) {}
    inline const Pos2d &GetOrg(void) const
      { return org; }
    inline const Vector2d &GetDir(void) const
      { return dir; }
    //! @brief Return a point at a distance lambda from its origin.
    inline Pos2d getPoint(const GEOM_FT &lambda) const
      { return org+lambda*dir; }
    GEOM_FT Parametro(const Pos2d &p) const;
  };


class Dir2d;
class Ray2d;
class Segment2d;


//! @ingroup GEOM
//
//! @brief Line in a two-dimensional space.
class Line2d : public Linear2d
  {
    CGLine_2 cgr;

    friend class Ray2d;
    friend class Segment2d;
  public:
    Line2d(void);
    explicit Line2d(const CGLine_2 &r);
    Line2d(const Pos2d &p1,const Pos2d &p2);
    Line2d(const Pos2d &p,const Dir2d &dir);
    Line2d(const Pos2d &p,const Vector2d &vdir);
    Line2d(const Line2d &r);
    Line2d(const Line2dParametricForm &param);
    Line2d &operator=(const Line2d &r);

    const CGLine_2 &ToCGAL(void) const;
    virtual GeomObj *clon(void) const;
    void Swap(void);

    void TwoPoints(const Pos2d &p1,const Pos2d &p2);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int) const
      { return NAN; }

    Pos2d Projection(const Pos2d &p) const;
    Vector2d Projection(const Vector2d &) const;
    GeomObj::list_Pos2d Project(const GeomObj::list_Pos2d &ptos) const;
    
    GEOM_RT a(void) const;
    GEOM_RT b(void) const;
    GEOM_RT c(void) const;
    GEOM_FT getSlope(void) const;
    GEOM_FT GetParamA(void) const; //Return the parameter a (y=a*x+b) of the line.
    GEOM_FT GetParamB(void) const; //Return the parameter a (y=a*x+b) of the line.

    GEOM_FT GetY(const GEOM_FT &x) const;
    GEOM_FT Parametro(const Pos2d &p) const;
    GeomObj::list_Pos2d Ordena(const GeomObj::list_Pos2d &ptos) const;
    Pos2d Point(const int &i=0) const;

    double getLambda(unsigned short int i,const double &d,const Vector2d &i_) const;

    Line2dParametricForm GetParametricas(void) const;
    Pos2d PtoParametricas(const GEOM_FT &lambda) const;
    void Parametricas(const Line2dParametricForm &param);
    bool EsVertical(void) const;
    bool EsDegenerada(void) const;
    bool In(const Pos2d &p, const double &tol= 0.0) const;
    bool LadoDerecho(const Pos2d &p) const;
    bool LadoIzquierdo(const Pos2d &p) const;

    GEOM_FT dist2(const Pos2d &p) const;
    virtual GEOM_FT dist(const Pos2d &p) const;

    Line2d Perpendicular(const Pos2d &p) const;
    Line2d Paralela(const Pos2d &v) const;
    Line2d Offset(const Vector2d &v) const;
    Line2d Offset(const GEOM_FT &d) const;
    void Put(const Pos2d &p1,const Pos2d &p2);

    bool intersects(const Line2d &r2) const;
    GeomObj2d::list_Pos2d getIntersection(unsigned short int i, const double &d) const;
    GeomObj2d::list_Pos2d getIntersection(const Line2d &r2) const;

    bool Paralela(const Line2d &r) const;

    virtual GEOM_FT getLength(void) const;
    virtual Pos2d getCenterOfMass(void) const;
    Dir2d GetDir(void) const;
    Vector2d VDir(void) const;
    Vector2d VersorDir(void) const;
    Line2d Bisectriz(const Line2d &r) const;
    Line2d getNormalizada(void) const;

    double getAngle(const Vector2d &v) const;
    double Azimuth(void) const;
    friend double angle(const Line2d &r,const Vector2d &v);
    friend double angle(const Line2d &r1,const Line2d &r2);

    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;

    void Transforma(const Trf2d &trf2d);

    friend bool operator==(const Line2d &r1,const Line2d &r2);

    void Print(std::ostream &os) const;
    void Plot(Plotter &psos) const;
    
  };

double angle(const Line2d &r,const Vector2d &v);
double angle(const Line2d &r1,const Line2d &r2);

bool operator==(const Line2d &r1,const Line2d &r2);

inline GEOM_FT dist2(const Pos2d &p,const Line2d &r)
  { return r.dist2(p); }
inline GEOM_FT dist(const Pos2d &p,const Line2d &r)
  { return r.dist(p); }
inline GEOM_FT dist2(const Line2d &r,const Pos2d &p)
  { return dist2(p,r); }
inline GEOM_FT dist(const Line2d &r,const Pos2d &p)
  { return dist(p,r); }
GEOM_FT dist2(const Line2d &r1,const Line2d &r2);
GEOM_FT dist(const Line2d &r1,const Line2d &r2);

inline bool paralelas(const Line2d &r1,const Line2d &r2)
  { return r1.Paralela(r2); }

bool intersecan(const Line2d &r1,const Line2d &r2);
GeomObj2d::list_Pos2d intersection(const Line2d &r1,const Line2d &r2);
Pos2d intersection_point(const Line2d &, const Line2d &);

bool colineales(const Line2d &r1,const Line2d &r2);

inline bool operator!=(const Line2d &r1,const Line2d &r2)
  { return !(r1==r2); }

inline Line2d bisectriz(const Line2d &r1,const Line2d &r2)
  { return r1.Bisectriz(r2); }
Line2d perpendicular_bisector(const Pos2d &p1,const Pos2d &p2);
 
#endif





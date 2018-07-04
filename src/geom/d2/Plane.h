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
//Plane.h

#ifndef PLANO3D_H
#define PLANO3D_H

#include <cstdlib>
#include <cmath>
#include "xc_basic/src/util/matem.h"
#include "Superficie3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "../tipos_cgal.h"
#include <list>

class Recta3d;
class SemiRecta3d;
class Segment3d;
class Polilinea3d;
class Poligono3d;
class GmGrupo3d;
class GeneralEquationOfPlane;
class SisCooRect2d3d;
class Ref2d3d;


//! @ingroup GEOM
//
//! @brief Plane in a three-dimensional space.
class Plane : public Superficie3d
  {
    CGPlane_3 cgp;
  public:

    typedef enum{DELANTE,DETRAS,DENTRO,CRUZA} clasif_poligono;

  protected:
    static clasif_poligono clfpnt2clfpol(const CGAL::Oriented_side os);
  public:
    Plane(void);
    explicit Plane(const CGPlane_3 &cgp);
    Plane(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Plane(const Pos3d &o,const Vector3d &v);
    Plane(const Pos3d &p,const Vector3d &v1,const Vector3d &v2);
    Plane(const Recta3d &r,const Pos3d &p);
    Plane(const Segment3d &s,const Vector3d &v);
    Plane(const Poligono3d &trg);
    Plane(const Plane &);
    Plane(const GeneralEquationOfPlane &eg);
    Plane(const GeomObj3d::list_Pos3d &lp);
    Plane &operator=(const Plane &);

    virtual GeomObj *clon(void) const;
    const CGPlane_3 &ToCGAL(void) const
      { return cgp; }
    void ThreePoints(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    virtual GEOM_FT GetMax(unsigned short int) const
      { return NAN; }
    virtual GEOM_FT GetMin(unsigned short int i) const
      { return NAN; }
    Pos3d Projection(const Pos3d &) const;
    Vector3d Projection(const Vector3d &) const;
    Recta3d Projection(const Recta3d &) const;
    GeomObj3d::list_Pos3d Projection(const GeomObj3d::list_Pos3d &) const;
    //Poligono3d Projection(const Poligono3d &) const;

    virtual Vector3d Normal(void) const;
    Vector3d Base1(void) const;
    Vector3d Base2(void) const;
    SisCooRect2d3d getSisCoo(void) const;
    Ref2d3d getRef(const Pos3d &) const;

    void Swap(void);
    Plane GetSwap(void) const;

    bool LadoPositivo(const Pos3d &p) const;
    bool LadoNegativo(const Pos3d &p) const;
    virtual bool In(const Pos3d &p, const GEOM_FT &tol= 0.0) const;

    CGAL::Oriented_side ClassifyPoint(const Pos3d &p) const;

    template <typename InputIterator>
    clasif_poligono ClassifyPoints(InputIterator first,InputIterator last) const;
    clasif_poligono ClasificaPoligono(const Poligono3d &pol) const;

    GEOM_FT PseudoDist(const Pos3d &p) const;
    GEOM_FT PseudoDist2(const Pos3d &p) const;
    virtual GEOM_FT dist2(const Pos3d &p) const;
    virtual GEOM_FT dist(const Pos3d &p) const;
    //! @brief Set the points that define the plane.
    void Put(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
      { ThreePoints(p1,p2,p3); }

    GeneralEquationOfPlane getGeneralEquation(void) const;
    void GeneralEquation(const GeneralEquationOfPlane &eq);
    GEOM_FT x(const Pos2d &p) const;
    GEOM_FT y(const Pos2d &p) const;
    GEOM_FT z(const Pos2d &p) const;

    virtual Pos3d getCenterOfMass(void) const;
    Pos3d Point(void) const;
    //! @brief Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Ix(void) const
      { return NAN; }
    //! @brief Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Iy(void) const
      { return NAN; }
    //! @brief Moment of inertia with respect to the center of mass in local coordinates.
    inline virtual GEOM_FT Iz(void) const
      { return NAN; }

    Recta3d XYTrace(void) const;
    Recta3d XZTrace(void) const;
    Recta3d YZTrace(void) const;
    Recta3d getMaximumSlopeLineXY(void) const;
    Recta3d getMaximumSlopeLineXZ(void) const;
    Recta3d getMaximumSlopeLineYZ(void) const;

    bool intersects(const Plane &p) const;
    Recta3d getIntersection(const Plane &p) const;
    bool intersects(const Recta3d &p) const;
    Pos3d getIntersection(const Recta3d &p) const;
    bool intersects(const SemiRecta3d &p) const;
    Pos3d getIntersection(const SemiRecta3d &p) const;
    bool intersects(const Segment3d &p) const;
    Pos3d getIntersection(const Segment3d &p) const;

    GEOM_FT getAngle(const Plane &p) const;
    GEOM_FT getAngle(const Vector3d &) const;
    GEOM_FT getSlopeAngleXY(void) const;
    GEOM_FT getSlopeAngleXZ(void) const;
    GEOM_FT getSlopeAngleYZ(void) const;

    GEOM_FT AjusteMinimosCuadrados(const GeomObj3d::list_Pos3d &lp);

    friend Plane FromCGAL(const CGPlane_3 &p);
    friend bool operator==(const Plane &p1,const Plane &p2);
    void Print(std::ostream &os) const;
  };

Plane FromCGAL(const CGPlane_3 &p);
bool operator==(const Plane &p1,const Plane &p2);

const Plane XYPlane3d(Pos3d(0,0,0),Pos3d(1,0,0),Pos3d(0,1,0));
const Plane XZPlane3d(Pos3d(0,0,0),Pos3d(1,0,0),Pos3d(0,0,1));
const Plane YZPlane3d(Pos3d(0,0,0),Pos3d(0,1,0),Pos3d(0,0,1));

GEOM_FT angle(const Recta3d &r,const Plane &p);
GEOM_FT angle(const Plane &p,const Recta3d &r);
GEOM_FT angle(const Vector3d &,const Plane &);
GEOM_FT angle(const Plane &,const Vector3d &);
GEOM_FT angle(const Plane &,const Plane &);


Plane perpendicular(const Recta3d &r, const Pos3d &p);

bool paralelos(const Plane &p, const Recta3d &r);
bool paralelos(const Plane &p1, const Plane &p2);


Recta3d intersection_line(const Plane &, const Plane &);
Pos3d intersection_point(const Plane &, const Plane &,const Plane &);
GmGrupo3d intersection(const Plane &p1, const Plane &p2);
GeomObj3d::list_Pos3d intersection(const Plane &p, const Recta3d &r);
GeomObj3d::list_Pos3d intersection(const Recta3d &r, const Plane &p);
GeomObj3d::list_Pos3d intersection(const Plane &p, const SemiRecta3d &r);
GeomObj3d::list_Pos3d intersection(const SemiRecta3d &r, const Plane &p);
GeomObj3d::list_Pos3d intersection(const Plane &p, const Segment3d &);
GeomObj3d::list_Pos3d intersection(const Segment3d &, const Plane &p);
GeomObj3d::list_Pos3d intersection(const Plane &p, const Polilinea3d &r);
GeomObj3d::list_Pos3d intersection(const Polilinea3d &r, const Plane &p);
Pos3d intersection_point(const Plane &p, const Recta3d &r);
Pos3d intersection_point(const Recta3d &r, const Plane &p);
Pos3d intersection_point(const Plane &p, const SemiRecta3d &r);
Pos3d intersection_point(const SemiRecta3d &r, const Plane &p);
Pos3d intersection_point(const Plane &p, const Segment3d &r);
Pos3d intersection_point(const Segment3d &r, const Plane &p);

GeomObj3d::list_Pos3d intersection_points(const std::deque<Plane> &);

template <typename InputIterator>
Plane::clasif_poligono Plane::ClassifyPoints(InputIterator first,InputIterator last) const
  {
    InputIterator i= first;
    CGAL::Oriented_side cf_pinic= ClassifyPoint(*i); i++;
    for(;i!=last;i++)
      {
        const CGAL::Oriented_side cf_point= ClassifyPoint(*i);
        if(cf_point!=cf_pinic)
          {
            if(cf_pinic!=CGAL::ON_ORIENTED_BOUNDARY) //Start point out of plane.
              if(cf_point!=CGAL::ON_ORIENTED_BOUNDARY) //Point *i out of plane.
                return CRUZA;
              else //Point *i inside the plane.
                continue;
            else //Start point inside the plane.
              if(cf_point!=CGAL::ON_ORIENTED_BOUNDARY) //Point *i out of plane.
                {
                  cf_pinic= cf_point;
                  continue;
                }
              else //Point *i inside the plane.
                continue;
          }
      }
    //Si llegamos hasta aquí es que todos tienen la
    //misma clasificación.
    return clfpnt2clfpol(cf_pinic);
  }


/* class SemiRecta; */

/* GeomObj3d::list_Pos3d intersection(const Plane &p, const SemiRecta3d &sr); */
/* inline GeomObj3d::list_Pos3d intersection(const SemiRecta3d &sr, const Plane &p) */
/*   { return intersection(p,sr); }  */


#endif


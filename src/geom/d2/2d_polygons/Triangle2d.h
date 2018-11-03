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
//Triangle2d.h

#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include "PolygonalSurface2d.h"
#include "xc_utils/src/geom/cgal_types.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/utils/misc_utils/matem.h"

class Segment2d;
class Polygon2d;


//! @ingroup GEOM
//
//! @brief Triangle in a two-dimensional space.
class Triangle2d : public PolygonalSurface2d
  {
    CGTriangle_2 cgtriang;
  public:
    Triangle2d(void) : PolygonalSurface2d(), cgtriang() {}
    Triangle2d(const Pos2d p1,const Pos2d &p2,const Pos2d &p3)
     : PolygonalSurface2d(), cgtriang(p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL())
      {}
    Triangle2d(const Triangle2d &other) : PolygonalSurface2d(other), cgtriang(other.cgtriang) {}
    Triangle2d &operator=(const Triangle2d &p)
      {
	PolygonalSurface2d::operator=(p);
        cgtriang= p.cgtriang;
        return *this;
      }
    virtual PolygonalSurface2d *clon(void) const
      { return new Triangle2d(*this); }
    inline virtual unsigned int GetNumVertices(void) const
      { return 3; }
    bool Degenerado(void) const
      { return cgtriang.is_degenerate(); }
    Pos2d Vertice(unsigned int i) const
      { return Vertice0(i-1); }
    Pos2d Vertice0(unsigned int j) const
      { return Pos2d(cgtriang.vertex(j)); }
    Segment2d Base(const size_t &i) const; //Return la base opuesta al vertice i.
    Segment2d Altura(const size_t &i) const; //Return la altura del vertice i.
    virtual Pos2d getCenterOfMass(void) const;
    virtual GEOM_FT getLength(void) const;
    //! @brief Return the area of the object.
    virtual GEOM_FT getArea(void) const
      { return cgtriang.area(); }
    //! @brief Return the volume of the object.
    virtual GEOM_FT getVolume(void) const
      { return 0.0; }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    //! @brief Return true if the point is inside the triangle.
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const
      { return (cgtriang.has_on_positive_side(p.ToCGAL()) || cgtriang.has_on_boundary(p.ToCGAL())); }

    Polygon2d getPolygon(void) const;

    void Transforma(const Trf2d &trf2d);

    friend int operator ==(const Triangle2d &a,const Triangle2d &b)
      { return ( a.cgtriang == b.cgtriang ); };
    inline friend bool intersecan(const Triangle2d &tr1,const Triangle2d &tr2)
      { return do_intersect(tr1.cgtriang,tr2.cgtriang); }
    
    void Print(std::ostream &os) const;
    void Plot(Plotter &) const;
  };
#endif




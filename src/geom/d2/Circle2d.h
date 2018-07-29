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
//Circle2d.h

#ifndef CIRCLE2D_H
#define CIRCLE2D_H

#include "Superficie2d.h"
#include "../cgal_types.h"
#include "xc_basic/src/util/matem.h"

class Pos2d;
class Pos2dArray;
class Poligono2d;

//! @ingroup GEOM
//
//! @brief Círculo en dos dimensiones.
class Circle2d : public Superficie2d
  {
    CGCircle_2 cgcirc;

  protected:
    void arc_points(const double &theta_inic,const double &delta_theta,Pos2dArray &ptos) const;
  public:
    Circle2d(void) : Superficie2d(), cgcirc() {}
    Circle2d(const Pos2d &centro,const GEOM_FT &rad);
    Circle2d(const GEOM_FT &rad2,const Pos2d &centro);
    Circle2d(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3);
    Circle2d(const Circle2d &other)
     : Superficie2d(other), cgcirc(other.cgcirc) {}
    Circle2d &operator=(const Circle2d &p)
      {
	Superficie2d::operator=(p);
        cgcirc= p.cgcirc;
        return *this;
      }
    virtual Superficie2d *clon(void) const
      { return new Circle2d(*this); }
    Pos2d Centro(void) const;
    virtual Pos2d getCenterOfMass(void) const;
    Pos2d Point(const double &ang) const;
    inline GEOM_FT getSquaredRadius(void) const
      { return cgcirc.squared_radius(); }
    GEOM_FT getRadius(void) const;
    inline GEOM_FT Diametro(void) const
      { return 2*getRadius(); }
    double getAngle(const Pos2d &p) const;
    virtual GEOM_FT getLength(void) const;
    //! @brief Return the perimeter of the object.
    inline GEOM_FT Perimetro(void) const
      { return getLength(); }
    virtual double getIncludedAngle(void) const;
    virtual GEOM_FT getArea(void) const;
    //! @brief Return the volume of the object.
    virtual GEOM_FT getVolume(void) const
      { return 0.0; }
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const
      { return Ix(); }
    inline virtual GEOM_FT Pxy(void) const
      { return 0.0; }
    virtual GEOM_FT Iz(void) const
      { return 2*Ix(); }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;
    Pos2dArray getPointsOnPerimeter(const size_t &n,const double &theta_inic= 0.0) const;
    Poligono2d getPoligonoInscrito(const size_t &n,const double &theta_inic= 0.0) const;

    void Transforma(const Trf2d &trf2d);

    friend int operator ==(const Circle2d &a,const Circle2d &b)
      { return ( a.cgcirc == b.cgcirc ); };
    
    void Print(std::ostream &os) const;
    void Plot(Plotter &) const;
  };

Circle2d Circle2dRTT(const GEOM_FT &,const Line2d &,const Line2d &,const bool &left,const bool &far);

#endif




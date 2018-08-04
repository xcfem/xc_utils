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

#ifndef CIRCLE3D_H
#define CIRCLE3D_H

#include "D2to3d.h"
#include "Circle2d.h"

class Pos3d;

//! @ingroup GEOM
//
//! @brief Círculo en tres dimensiones.
class Circle3d : public D2to3d
  {
    Circle2d circ;
  public:
    Circle3d(void) : D2to3d(), circ() {}
    Circle3d(const Pos3d &centro,const GEOM_FT &rad);
    Circle3d(const GEOM_FT &rad2,const Pos3d &centro);
    Circle3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Circle3d(const Circle3d &other)
      : D2to3d(other), circ(other.circ) {}
    Circle3d &operator=(const Circle3d &p)
      {
	D2to3d::operator=(p);
        circ= p.circ;
        return *this;
      }
    virtual D2to3d *clon(void) const
      { return new Circle3d(*this); }
    Pos3d Centro(void) const;
    virtual Pos3d getCenterOfMass(void) const;
    GEOM_FT getSquaredRadius(void) const;
    GEOM_FT getRadius(void) const;
    GEOM_FT getDiameter(void) const;
    double getAngle(const Pos3d &p) const;
    //! @brief Return the length of the object.
    virtual GEOM_FT getLength(void) const
      { return circ.getLength(); }
    //! @brief Return the perimeter of the object.
    inline GEOM_FT getPerimeter(void) const
      { return getLength(); }
    //! @brief Return the area of the object.
    virtual GEOM_FT getArea(void) const
      { return circ.getArea(); }
    //! @brief Return the volume of the object.
    virtual GEOM_FT getVolume(void) const
      { return 0; }
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;

    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;

    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;
    const Pos3dArray &getPointsOnPerimeter(const size_t &n,const double &theta_inic= 0.0) const;

    friend bool operator ==(const Circle3d &a,const Circle3d &b);

    
    void Print(std::ostream &os) const;
  };

Circle3d Circle3dThreepoints(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);

#endif




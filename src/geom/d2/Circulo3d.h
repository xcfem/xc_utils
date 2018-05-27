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
//Circulo2d.h

#ifndef CIRCULO3D_H
#define CIRCULO3D_H

#include "D2to3d.h"
#include "Circulo2d.h"

class Pos3d;

//! @ingroup GEOM
//
//! @brief Círculo en tres dimensiones.
class Circulo3d : public D2to3d
  {
    Circulo2d circ;
  public:
    Circulo3d(void) : D2to3d(), circ() {}
    Circulo3d(const Pos3d &centro,const GEOM_FT &rad);
    Circulo3d(const GEOM_FT &rad2,const Pos3d &centro);
    Circulo3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Circulo3d(const Circulo3d &otro)
      : D2to3d(otro), circ(otro.circ) {}
    Circulo3d &operator=(const Circulo3d &p)
      {
	D2to3d::operator=(p);
        circ= p.circ;
        return *this;
      }
    virtual D2to3d *clon(void) const
      { return new Circulo3d(*this); }
    Pos3d Centro(void) const;
    virtual Pos3d getCenterOfMass(void) const;
    GEOM_FT Radio2(void) const;
    GEOM_FT Radio(void) const;
    GEOM_FT Diametro(void) const;
    double Angulo(const Pos3d &p) const;
    //! @brief Return the length of the object.
    virtual GEOM_FT getLength(void) const
      { return circ.getLength(); }
    inline GEOM_FT Perimetro(void) const
      { return getLength(); }
    virtual GEOM_FT Area(void) const
      { return circ.Area(); }
    virtual GEOM_FT Volumen(void) const
      { return 0; }
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;

    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;

    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;
    const MatrizPos3d &getPointsOnPerimeter(const size_t &n,const double &theta_inic= 0.0) const;

    friend bool operator ==(const Circulo3d &a,const Circulo3d &b);

    
    void Print(std::ostream &os) const;
  };

Circulo3d Circulo3dThreepoints(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);

#endif




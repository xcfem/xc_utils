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
//CircularSector2d.h

#ifndef SECTORCIRCULAR3D_H
#define SECTORCIRCULAR3D_H

#include "D2to3d.h"
#include "CircularSector2d.h"

class Pos3d;

//! @ingroup GEOM
//
//! @brief Sector de círculo en tres dimensiones.
class CircularSector3d : public D2to3d
  {
    CircularSector2d sect_circ;
  public:
    CircularSector3d(void) : D2to3d(), sect_circ() {}
    CircularSector3d(const Pos3d centro,const GEOM_FT &rad,const double &th1,const double &th2);
    CircularSector3d(const GEOM_FT &rad2,const Pos3d &centro,const double &th1,const double &th2);
    CircularSector3d(const Pos3d &c,const double &r,const Vector3d &n,const Vector3d &Xaxis,const double &angIni,const double &angFin);
    CircularSector3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    CircularSector3d(const CircularSector3d &);
    CircularSector3d &operator=(const CircularSector3d &p);
    virtual D2to3d *clon(void) const;
    Pos3d Centro(void) const;
    Pos3d PInic(void) const;
    Pos3d PFin(void) const;
    Pos3d PMed(void) const;
    virtual Pos3d getCenterOfMass(void) const;
    virtual Pos3d ArcCentroid(void) const;
    GEOM_FT getSquaredRadius(void) const;
    GEOM_FT getRadius(void) const;
    GEOM_FT Diametro(void) const;
    inline double getIncludedAngle(void) const
      { return sect_circ.getIncludedAngle(); }
    double getAngle(const Pos3d &) const;
    double getLambda(const Pos3d &) const;
    virtual GEOM_FT getLength(void) const
      { return sect_circ.getLength(); }
    virtual GEOM_FT getArcLength(void) const
      { return sect_circ.getArcLength(); }
    //! @brief Return the perimeter of the object.
    inline GEOM_FT Perimetro(void) const
      { return getLength(); }
    //! @brief Return the area of the object.
    virtual GEOM_FT getArea(void) const
      { return sect_circ.getArea(); }
    //! @brief Return the volume of the object.
    virtual GEOM_FT getVolume(void) const
      { return 0; }
    inline const double &Theta1(void) const
      { return sect_circ.Theta1(); }
    inline double &Theta1(void)
      { return sect_circ.Theta1(); }
    inline const double &Theta2(void) const
      { return sect_circ.Theta2(); }
    inline double &Theta2(void)
      { return sect_circ.Theta2(); }
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;

    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;

    virtual bool In(const Pos3d &p, const double &tol= 0.0) const;
    Pos3dArray getArcPoints(const size_t &n) const;

    friend bool operator ==(const CircularSector3d &a,const CircularSector3d &b);

    
    void Print(std::ostream &os) const;
  };

#endif




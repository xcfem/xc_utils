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
//AnnulusSector2d.h

#ifndef SECTORANILLOCIRCULAR2D_H
#define SECTORANILLOCIRCULAR2D_H

#include "CircularSector2d.h"

class Pos2d;
class MatrizPos2d;
class Poligono2d;

//! @ingroup GEOM
//
//! @brief Sector de un anillo circular en dos dimensiones.
class AnnulusSector2d : public CircularSector2d
  {
    double inner_radius; //!< inner radius.
  protected:
    CircularSector2d getSector(const double &R) const;
    CircularSector2d SectorInterior(void) const;
  public:
    AnnulusSector2d(void) : CircularSector2d(), inner_radius(0.0) {}
    AnnulusSector2d(const CircularSector2d &c,const double &inner_radius);
    AnnulusSector2d(const AnnulusSector2d &otro)
      : CircularSector2d(otro), inner_radius(otro.inner_radius) {}
    AnnulusSector2d &operator=(const AnnulusSector2d &p)
      {
	CircularSector2d::operator=(p);
        inner_radius= p.inner_radius;
        return *this;
      }
    virtual Superficie2d *clon(void) const
      { return new AnnulusSector2d(*this); }
    virtual Pos2d getCenterOfMass(void) const;
    Pos2d PInicInt(void) const;
    Pos2d PInicExt(void) const;
    Pos2d PFinInt(void) const;
    Pos2d PFinExt(void) const;
    Pos2d PMedInt(void) const;
    Pos2d PMedExt(void) const;
    //! @brief Return the outer radius.
    inline double outerRadius(void) const
      { return getRadius(); }
    inline const double &innerRadius(void) const
      { return inner_radius; }
    inline double &innerRadius(void)
      { return inner_radius; }
    virtual GEOM_FT getInteriorArcLength(void) const;
    virtual GEOM_FT getExteriorArcLength(void) const;
    virtual GEOM_FT getLength(void) const;
    virtual GEOM_FT getArea(void) const;
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Pxy(void) const;
    virtual GEOM_FT Iz(void) const;
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const;
    MatrizPos2d getExtArcPoints(const size_t &n) const;
    MatrizPos2d getIntArcPoints(const size_t &n) const;
    MatrizPos2d getPointsOnPerimeter(const size_t &n) const;
    MatrizPos2d genMesh(const size_t &m,const size_t &n) const;
    Poligono2d getPoligono2d(const size_t &n) const;

    void Print(std::ostream &os) const;
  };

bool operator==(const AnnulusSector2d &a,const AnnulusSector2d &b);

#endif




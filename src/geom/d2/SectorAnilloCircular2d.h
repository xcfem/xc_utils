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
//SectorAnilloCircular2d.h

#ifndef SECTORANILLOCIRCULAR2D_H
#define SECTORANILLOCIRCULAR2D_H

#include "SectorCircular2d.h"

class Pos2d;
class MatrizPos2d;
class Poligono2d;

//! @ingroup GEOM
//
//! @brief Sector de un anillo circular en dos dimensiones.
class SectorAnilloCircular2d : public SectorCircular2d
  {
    double rint; //!< Radio interior del anillo.
  protected:
    SectorCircular2d getSector(const double &R) const;
    SectorCircular2d SectorInterior(void) const;
  public:
    SectorAnilloCircular2d(void) : SectorCircular2d(), rint(0.0) {}
    SectorAnilloCircular2d(const SectorCircular2d &c,const double &rint);
    SectorAnilloCircular2d(const SectorAnilloCircular2d &otro)
      : SectorCircular2d(otro), rint(otro.rint) {}
    SectorAnilloCircular2d &operator=(const SectorAnilloCircular2d &p)
      {
	SectorCircular2d::operator=(p);
        rint= p.rint;
        return *this;
      }
    virtual Superficie2d *clon(void) const
      { return new SectorAnilloCircular2d(*this); }
    virtual Pos2d getCenterOfMass(void) const;
    Pos2d PInicInt(void) const;
    Pos2d PInicExt(void) const;
    Pos2d PFinInt(void) const;
    Pos2d PFinExt(void) const;
    Pos2d PMedInt(void) const;
    Pos2d PMedExt(void) const;
    //! @brief Return el radio interior.
    inline const double RadioExt(void) const
      { return Radio(); }
    inline double RadioExt(void)
      { return Radio(); }
    inline const double &RadioInt(void) const
      { return rint; }
    inline double &RadioInt(void)
      { return rint; }
    virtual GEOM_FT LongitudArcoInt(void) const;
    virtual GEOM_FT LongitudArcoExt(void) const;
    virtual GEOM_FT Longitud(void) const;
    virtual GEOM_FT Area(void) const;
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

bool operator==(const SectorAnilloCircular2d &a,const SectorAnilloCircular2d &b);

#endif




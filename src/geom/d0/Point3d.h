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
//Point3d.h

#ifndef POINT3D_H
#define POINT3D_H

#include "../d3/GeomObj3d.h"
#include "../pos_vec/Pos3d.h"

//! @ingroup GEOM
//
//! @brief Point in 3D.
class Point3d : public GeomObj3d
  {
    Pos3d org;
  public:
    Point3d(void) : GeomObj3d() {}
    Point3d(GEOM_FT x,GEOM_FT y,GEOM_FT z=0) : GeomObj3d(), org(Pos3d(x,y,z))
      {}
    Point3d(const Point3d &otro) : GeomObj3d(otro), org(otro.org) {}
    Point3d &operator=(const Point3d &p)
      {
	GeomObj3d::operator=(p);
        org= p.org;
        return *this;
      }
    Point3d &operator=(const Pos3d &p)
      {
	org= p;
        return *this;
      }
    operator const Pos3d &()
      { return org; }
    inline Pos3d GetPos(void) const
    //Return the posicion del Point3d en el sistema global.
      { return org; }
    virtual GeomObj3d *clon(void) const
      { return new Point3d(*this); }
    virtual Pos3d Cdg(void) const
      { return org; }
    inline virtual unsigned short int Dimension(void) const
      { return 0; }
    virtual GEOM_FT Longitud(void) const
      { return 0.0; }
    virtual GEOM_FT Area(void) const
      { return 0.0; }
    virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    virtual GEOM_FT Ix(void) const
      { return 0.0; }
    virtual GEOM_FT Iy(void) const
      { return 0.0; }
    virtual GEOM_FT Iz(void) const
      { return 0.0; }
    inline bool domina_a(const Point3d &b) const
      { return org.domina_a(b.org); }
    inline virtual GEOM_FT GetMax(unsigned short int i) const
      { return org(i); }
    inline virtual GEOM_FT GetMin(unsigned short int i) const
      { return org(i); }
    friend int operator ==(const Point3d &a,const Point3d &b)
      { return ( a.org == b.org ); };
    inline void Print(std::ostream &os) const
      { os << org; }
  };
#endif




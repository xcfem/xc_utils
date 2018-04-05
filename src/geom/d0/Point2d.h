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
//Point2d.h

#ifndef POINT2D_H
#define POINT2D_H

#include "../d2/GeomObj2d.h"
#include "../pos_vec/Pos2d.h"

//! @ingroup GEOM
//
//! @brief Point in 2D.
class Point2d : public GeomObj2d
  {
    Pos2d org;
  public:
    Point2d(void) : GeomObj2d() {}
    explicit Point2d(const Pos2d &p): GeomObj2d(), org(p) {}
    Point2d(GEOM_FT x,GEOM_FT y) : GeomObj2d(), org(Pos2d(x,y))
      {}
    operator const Pos2d &()
      { return org; }
    inline Pos2d GetPos(void) const
    //Return the posicion del Point2d en el sistema global.
      { return org; }
    virtual GeomObj2d *clon(void) const
      { return new Point2d(*this); }
    virtual Pos2d Cdg(void) const
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
    virtual GEOM_FT Pxy(void) const
      { return 0.0; }
    virtual GEOM_FT Iz(void) const
      { return 0.0; }
    inline bool domina_a(const Point2d &b) const
      { return org.domina_a(b.org); }
    inline virtual GEOM_FT GetMax(unsigned short int i) const
      { return org(i); }
    inline virtual GEOM_FT GetMin(unsigned short int i) const
      { return org(i); }

    void Transforma(const Trf2d &trf2d);

    friend int operator ==(const Point2d &a,const Point2d &b)
      { return ( a.org == b.org ); };
    
    void Print(std::ostream &os) const;
    void Plot(Plotter &psos) const;
  };
#endif




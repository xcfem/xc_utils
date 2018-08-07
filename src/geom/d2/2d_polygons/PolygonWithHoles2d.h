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
//PolYgonoWithHoles2d.h

#ifndef POLYGON_WITH_HOLES_2D_H
#define POLYGON_WITH_HOLES_2D_H

#include "xc_utils/src/geom/d2/Surface2d.h"

class Line2d;
class Ray2d;
class Segment2d;
class Polygon2d;
class Polyline2d;


//! @ingroup GEOM
//
//! @brief Polígono que puede tener huecos.
class PolygonWithHoles2d: public Surface2d
  {
    CGPolygonWithHoles_2 cgpol; //CGAL polygon.
  public:
    typedef CGPolygonWithHoles_2::Hole_const_iterator Hole_const_iterator;
 
    PolygonWithHoles2d(void);
    explicit PolygonWithHoles2d(const Polygon2d &);
    virtual GeomObj *clon(void) const;

    bool In(const Pos2d &p, const double &tol) const;
    GEOM_FT getLength(void) const;
    inline GEOM_FT getPerimeter(void) const
      { return getLength(); }
    GEOM_FT getArea(void) const;
    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    Pos2d getCenterOfMass(void) const;
    GEOM_FT Ix(void) const;
    GEOM_FT Iy(void) const;
    GEOM_FT Pxy(void) const;

    PolygonWithHoles2d getTransformado(const Trf2d &);
    void Transforma(const Trf2d &);

    void add_hole(const Polygon2d &);
    void contour(const Polygon2d &);

    void Print(std::ostream &) const;
  };

#endif




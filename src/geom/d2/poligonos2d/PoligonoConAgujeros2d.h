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
//PoligonoConAgujeros2D.h

#ifndef POLIGONOCONAGUJEROS2D_H
#define POLIGONOCONAGUJEROS2D_H

#include "xc_utils/src/geom/d2/Superficie2d.h"

class Recta2d;
class SemiRecta2d;
class Segment2d;
class Poligono2d;
class Polilinea2d;


//! @ingroup GEOM
//
//! @brief Polígono que puede tener huecos.
class PoligonoConAgujeros2d: public Superficie2d
  {
    CGPoligonoConAgujeros_2 cgpol; //Poligono de CGAL.
  public:
    typedef CGPoligonoConAgujeros_2::Hole_const_iterator Hole_const_iterator;
 
    PoligonoConAgujeros2d(void);
    explicit PoligonoConAgujeros2d(const Poligono2d &);
    virtual GeomObj *clon(void) const;

    bool In(const Pos2d &p, const double &tol) const;
    GEOM_FT getLength(void) const;
    inline GEOM_FT Perimetro(void) const
      { return getLength(); }
    GEOM_FT getArea(void) const;
    GEOM_FT GetMax(unsigned short int i) const;
    GEOM_FT GetMin(unsigned short int i) const;
    Pos2d getCenterOfMass(void) const;
    GEOM_FT Ix(void) const;
    GEOM_FT Iy(void) const;
    GEOM_FT Pxy(void) const;

    PoligonoConAgujeros2d getTransformado(const Trf2d &);
    void Transforma(const Trf2d &);

    void add_hole(const Poligono2d &);
    void contour(const Poligono2d &);

    void Print(std::ostream &) const;
  };

#endif




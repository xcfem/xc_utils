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
//d2to3D.h

#ifndef D2TO3D_H
#define D2TO3D_H

#include "xc_utils/src/geom/d2/Superficie3d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"
#include "../tipos_cgal.h"

class Plane;
class Segmento2d;
class Segmento3d;
class MatrizPos3d;
class MatrizPos2d;

//! @ingroup GEOM
//
//! @brief Class that places 2D objects
//! (circle, ellipse, polygons, ...) in a 3D space.
class D2to3d: public Superficie3d
  {
    Ref2d3d ref;

  protected:
    Pos3d to_3d(const Pos2d &p2d) const;
    Segmento3d to_3d(const Segmento2d &sg2d) const;
    MatrizPos3d to_3d(const MatrizPos2d &p2d) const;
    Pos2d to_2d(const Pos3d &p3d) const;

    D2to3d(const Ref2d3d &rf)
      : ref(rf) {}
    D2to3d(const Pos3d &o);
    D2to3d(const Pos3d &o,const Pos3d &p,const Pos3d &q);
    D2to3d(const Pos3d &o,const Vector3d &n,const Vector3d &i);

    const Ref2d3d &get_ref(void) const
      { return ref; }
  public:
    D2to3d(void);
    D2to3d(const D2to3d &otro);
    D2to3d &operator =(const D2to3d &otro);
    void ThreePoints(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);

    inline virtual unsigned short int Dimension(void) const
    //Return the dimensión del objeto 0, 1, 2 ó 3.
      { return 2; }

    Plane GetPlano(void) const;

    friend bool operator ==(const D2to3d &a,const D2to3d &b);
    void Print(std::ostream &os) const;
  };

#endif

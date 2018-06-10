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
//Triangle3d.h

#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "xc_utils/src/geom/d2/Poligono3d.h"

class Plane;
class Triangle2d;

//! @ingroup GEOM
//
//! @brief Triangle in a three-dimensional space.
class Triangle3d: public Poligono3d
  {
    Triangle3d(const Ref2d3d &rf,const Triangle2d &p);

    inline void push_back(const Pos3d &p)
      { Poligono3d::push_back(p); }
  public:
    Triangle3d(void);
    Triangle3d(const Triangle3d &otro);
    Triangle3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Triangle3d &operator =(const Triangle3d &otro) ;
    virtual GeomObj *clon(void) const
      { return new Triangle3d(*this); }

    inline virtual unsigned int GetNumVertices(void) const
      { return 3; }
    GEOM_FT dist(const Pos3d &p) const;
    GEOM_FT dist2(const Pos3d &p) const;
  };

#endif

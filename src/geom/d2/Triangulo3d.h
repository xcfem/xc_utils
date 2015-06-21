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
//Triangulo3d.h

#ifndef TRIANGULO3D_H
#define TRIANGULO3D_H

#include "xc_utils/src/geom/d2/Poligono3d.h"

class Plano3d;
class Triangulo2d;

//! @ingroup GEOM
//
//! @brief Triangulo en tres dimensiones.
class Triangulo3d: public Poligono3d
  {
    Triangulo3d(const Ref2d3d &rf,const Triangulo2d &p);

    inline void push_back(const Pos3d &p)
      { Poligono3d::push_back(p); }
  public:
    Triangulo3d(void);
    Triangulo3d(const Triangulo3d &otro);
    Triangulo3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3);
    Triangulo3d &operator =(const Triangulo3d &otro) ;
    virtual GeomObj *clon(void) const
      { return new Triangulo3d(*this); }

    inline virtual unsigned int GetNumVertices(void) const
      { return 3; }
    GEOM_FT dist(const Pos3d &p) const;
    GEOM_FT dist2(const Pos3d &p) const;
  };

#endif

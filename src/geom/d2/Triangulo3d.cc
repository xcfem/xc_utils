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
//Triangulo3d.cc

#include "Triangulo3d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Triangulo2d.h"
#include "../Wm3/Wm3DistVector3Triangle3.h"
#include "xc_utils/src/base/any_const_ptr.h"

Triangulo3d::Triangulo3d(const Ref2d3d &rf,const Triangulo2d &t)
  : Poligono3d(rf,t.GetPoligono()) {}
Triangulo3d::Triangulo3d(void): Poligono3d() {}
Triangulo3d::Triangulo3d(const Triangulo3d &otro)
  : Poligono3d(otro) {}
Triangulo3d::Triangulo3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : Poligono3d(p1,p2,p3) {}

Triangulo3d &Triangulo3d::operator =(const Triangulo3d &otro) 
  {
    Poligono3d::operator=(otro);
    return *this;
  }

//! @brief Devuelve el cuadrado de la distancia del punto al triángulo.
GEOM_FT Triangulo3d::dist2(const Pos3d &p) const
  {
    Wm3::DistVector3Triangle3ft d(p.VectorPos(),*this);
    return d.GetSquared();
  }

//! @brief Devuelve la distancia del punto al triángulo.
GEOM_FT Triangulo3d::dist(const Pos3d &p) const
  {
    Wm3::DistVector3Triangle3ft d(p.VectorPos(),*this);
    return d.Get();
  }

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
//TriangularPrism3d.cc

#include "TriangularPrism3d.h"



TriangularPrism3d::TriangularPrism3d(const Triangle3d &tr,const double &h)
  : triangular_prism(Triangle3d(tr),h) {}
TriangularPrism3d::TriangularPrism3d(const TriangularPrism3d &c)
  : triangular_prism(c) {}
TriangularPrism3d &TriangularPrism3d::operator=(const TriangularPrism3d &c)
  {
    triangular_prism::operator=(c);
    return *this;
  }
GeomObj *TriangularPrism3d::clon(void) const
  { return new TriangularPrism3d(*this); }


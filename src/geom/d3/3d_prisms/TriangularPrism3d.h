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
//TriangularPrism3d.h

#ifndef TRIANGULARPRISM3D_H
#define TRIANGULARPRISM3D_H

#include "RightPrism3d.h"
#include "xc_utils/src/geom/d2/Triangle3d.h"


//! @ingroup GEOM
//
//! @brief Triangular right prism.
class TriangularPrism3d : public RightPrism3d<Triangle3d>
  {
  public:
    typedef RightPrism3d<Triangle3d> triangular_prism;
  public:
    TriangularPrism3d(const Triangle3d &tr= Triangle3d(),const double &h=1.0);
    TriangularPrism3d(const TriangularPrism3d &);
    TriangularPrism3d &operator=(const TriangularPrism3d &c);
    virtual GeomObj *clon(void) const;
    
  };
#endif







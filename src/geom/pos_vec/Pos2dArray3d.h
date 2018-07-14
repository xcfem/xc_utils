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
//Pos2dArray3d

#ifndef POS2DARRAY3D_H
#define POS2DARRAY3D_H

#include "Pos2d.h"
#include "PosArray3d.h"

class Pos2dArray;


//! @ingroup GEOM
//
//! @brief Array of positions ina two-dimensional space.
class Pos2dArray3d: public PosArray3d<Pos2d>
  {
  public:
    Pos2dArray3d(const size_t iLayers= 1);
    Pos2d GetCentro(void) const;
  };

class BND2d;

Pos2dArray3d create_uniform_grid(const BND2d &bnd,const size_t &ndiv_x,const size_t &ndiv_y,const size_t &ndiv_z= 0);

#endif

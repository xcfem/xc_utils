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
//Tetraedro3c.cc

#include "PolyhedronBase.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"

GEOM_FT PolyhedronBase::Longitud(void) const
  {
    std::cerr << "PolyhedronBase::Longitud() no implementada." << std::endl;
    return 0.0;
  }
GEOM_FT PolyhedronBase::Volumen(void) const
  {
    std::cerr << "PolyhedronBase::Volumen() no implementada." << std::endl;
    return 0.0;
  }
GEOM_FT PolyhedronBase::Ix(void) const
  {
    std::cerr << "PolyhedronBase::Ix() no implementado." << std::endl;
    return 0.0;
  }
GEOM_FT PolyhedronBase::Iy(void) const
  {
    std::cerr << "PolyhedronBase::Iy() no implementado." << std::endl;
    return 0.0;
  }
GEOM_FT PolyhedronBase::Iz(void) const
  {
    std::cerr << "PolyhedronBase::Iy() no implementado." << std::endl;
    return 0.0;
  }
Pos3d PolyhedronBase::Cdg(void) const
  {
    std::cerr << "PolyhedronBase::Cdg() no implementado." << std::endl;
    return Pos3d();
  }

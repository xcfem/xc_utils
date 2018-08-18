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
//Tetrahedron3d.cc

#include "PolyhedronBase.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"

//! @brief Return the object length.
GEOM_FT PolyhedronBase::getLength(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
    return 0.0;
  }
//! @brief Return the object volume.
GEOM_FT PolyhedronBase::getVolume(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented." << std::endl;
    return 0.0;
  }
GEOM_FT PolyhedronBase::Ix(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented." << std::endl;
    return 0.0;
  }
GEOM_FT PolyhedronBase::Iy(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented." << std::endl;
    return 0.0;
  }
GEOM_FT PolyhedronBase::Iz(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented." << std::endl;
    return 0.0;
  }
Pos3d PolyhedronBase::getCenterOfMass(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented." << std::endl;
    return Pos3d();
  }

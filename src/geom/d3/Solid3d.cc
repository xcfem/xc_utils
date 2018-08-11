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
//Solid3d.cc

#include "Solid3d.h"
#include <limits>       // std::numeric_limits

//! @brief Constructor.
Solid3d::Solid3d(void)
  : GeomObj3d(){}

//! @brief Return the distance to the argument.
GEOM_FT Solid3d::dist(const Pos3d &p) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented."
              << std::endl;
    return std::numeric_limits<double>::quiet_NaN( );
  }

void Solid3d::Print(std::ostream &os) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented."
              << std::endl;
  }

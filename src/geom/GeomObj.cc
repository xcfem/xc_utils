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
//GeomObj.cc

#include "GeomObj.h"

#include <iostream>

//! @brief Constructor
GeomObj::GeomObj(void) 
  : ProtoGeom() {}

//! Return the dimension used to compute the center of mass, as follows:
//! - dimension == 0 => return 1.0
//! - dimension == 1 => return getLength()
//! - dimension == 2 => return Area()
//! - dimension == 3 => return Volumen()
GEOM_FT GeomObj::getCenterOfMassArea(void) const
  {
    unsigned short int d= Dimension();
    GEOM_FT retval= 1.0;
    switch(d)
      {
      case 0:
	retval= 1.0;
	break;
      case 1:
	retval= getLength();
	break;
      case 2:
	retval= Area();
	break;
      case 3:
	retval= Volumen();
	break;
      default:
	retval= 1.0;
      }
    return retval;
  }

std::ostream &operator<<(std::ostream &os, const GeomObj &go)
  {
    go.Print(os);
    return os;
  }


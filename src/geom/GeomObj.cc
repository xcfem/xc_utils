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

GEOM_FT GeomObj::AreaCdg(void) const
  {
    unsigned short int d= Dimension();
    if(d==0) return 1.0;
    if(d==1) return Longitud();
    if(d==2) return Area();
    if(d==3) return Volumen();
    return 1.0;
  }

std::ostream &operator<<(std::ostream &os, const GeomObj &go)
  {
    go.Print(os);
    return os;
  }


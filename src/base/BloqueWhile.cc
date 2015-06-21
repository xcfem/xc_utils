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
//BloqueWhile.cc

#include "BloqueWhile.h"
#include "xc_utils/src/base/CmdStatus.h"

//! @brief Constructor.
BloqueWhile::BloqueWhile(EntCmd *owner)
  : BloqueCond(owner) {}

//! @brief Constructor.
BloqueWhile::BloqueWhile(EntCmd *owner,const std::string &cnd)
  : BloqueCond(owner,cnd) {}

//! Lee un objeto BloqueWhile desde archivo
//! Soporta los comandos:
//! -bucle: Lee el código a repetir si se cumple la condición.
bool BloqueWhile::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "BloqueWhile; procesando comando: " << cmd << std::endl;
    if(cmd == "bucle")
      {
        bloque= status.GetBloque();
        return true;
      }
    else
      return BloqueCond::procesa_comando(status);
  }

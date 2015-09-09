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
//BloqueIf.cc

#include "BloqueIf.h"
#include "xc_utils/src/base/CmdStatus.h"

//! @brief Constructor.
BloqueIf::BloqueIf(EntCmd *owner)
  : BloqueCond(owner) {}

//! @brief Constructor.
BloqueIf::BloqueIf(EntCmd *owner,const std::string &cnd,const std::string &thn,const std::string &els)
  : BloqueCond(owner,cnd,thn), bloque_else(els) {}

//! Lee un objeto BloqueIf desde archivo
//! Soporta los comandos:
//! -cond: Lee la condición del if.
//! -then: Lee el código a ejecutar si se cumple la condición.
//! -else: Lee el código a ejecutar si no se cumple la condición.
bool BloqueIf::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "BloqueIf; procesando comando: " << cmd << std::endl;
    if(cmd == "then")
      {
        bloque= status.GetBloque();
        return true;
      }
    else if(cmd == "else")
      {
        bloque_else= status.GetBloque();
        return true;
      }
    else
      return BloqueCond::procesa_comando(status);
  }
const std::string &BloqueIf::BloqueThen(void) const
  { return Bloque(); }
const std::string &BloqueIf::BloqueElse(void) const
  { return bloque_else; }

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
//BloqueCond.cc

#include "BloqueCond.h"
#include "xc_utils/src/base/CmdStatus.h"

//! @brief Constructor.
BloqueCond::BloqueCond(EntCmd *owner)
  : BloqueBase(owner,"cond") {}

//! @brief Constructor.
BloqueCond::BloqueCond(EntCmd *owner,const std::string &cnd,const std::string &b)
  : BloqueBase(owner,"cond",b), cond(cnd) {}

//! @brief Devuelve verdadero si se cumple la condición
//! definida en cond.
bool BloqueCond::verdadero(void) const
  { return EntCmd::verdadero(cond); }

//! Lee un objeto BloqueCond desde archivo
//! Soporta los comandos:
//! -cond: Lee la condición del if.
//! -then: Lee el código a ejecutar si se cumple la condición.
//! -else: Lee el código a ejecutar si no se cumple la condición.
bool BloqueCond::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "BloqueCond; procesando comando: " << cmd << std::endl;
    if(cmd == "cond")
      {
        cond= status.GetBloque();
        return true;
      }
    else
      return BloqueBase::procesa_comando(status);
  }

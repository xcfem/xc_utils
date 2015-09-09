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
//BloqueFor.cc

#include "BloqueFor.h"
#include "xc_utils/src/base/CmdStatus.h"

//! @brief Constructor.
BloqueFor::BloqueFor(EntCmd *owner)
  : BloqueWhile(owner) {}

//! @brief Constructor.
BloqueFor::BloqueFor(EntCmd *owner,const std::string &ini,const std::string &cont,const std::string &incr)
  : BloqueWhile(owner,cont), inicio(ini), incremento(incr) {}

//! @brief Devuelve verdadero si se cumple la condición
//! definida en cond.
bool BloqueFor::continua(void) const
  { return verdadero(); }

//! Lee un objeto BloqueFor desde archivo
//! Soporta los comandos:
//! -inicio: Lee el bloque de código que establece el valor de inicio.
//! -parada: Lee el bloque de código que establece el valor de parada.
//! -parada: Lee el bloque de código que establece el incremento.
bool BloqueFor::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "BloqueFor; procesando comando: " << cmd << std::endl;
    if(cmd == "inicio")
      {
        inicio= status.GetBloque();
        return true;
      }
    else if(cmd == "continua")
      {
        cond= status.GetBloque();
        return true;
      }
    else if(cmd == "incremento")
      {
        incremento= status.GetBloque();
        return true;
      }
    else
      return BloqueWhile::procesa_comando(status);
  }
const std::string &BloqueFor::Inicio(void) const
  { return inicio; }
const std::string &BloqueFor::Cond(void) const
  { return cond; }
const std::string &BloqueFor::Incremento(void) const
  { return incremento; }

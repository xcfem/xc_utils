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
//BloqueBase.cc

#include "BloqueBase.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Constructor.
BloqueBase::BloqueBase(EntCmd *owr, const std::string &nmb,const std::string &b)
  : EntWOwner(owr), nombre(nmb), bloque(b) {}

//! Lee un objeto BloqueBase desde archivo
//! Soporta los comandos:
//! -cond: Lee la condición del if.
//! -then: Lee el código a ejecutar si se cumple la condición.
//! -else: Lee el código a ejecutar si no se cumple la condición.
bool BloqueBase::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "BloqueBase; procesando comando: " << cmd << std::endl;
    if(cmd == "rutina")
      {
        bloque= status.GetBloque();
        return true;
      }
    else
      return EntWOwner::procesa_comando(status);
  }

//! @brief Devuelve el nombre del bloque de instrucciones.
const std::string &BloqueBase::getNombre(void) const
  { return nombre; }

//! @brief Devuelve el bloque de instrucciones.
const std::string &BloqueBase::Bloque(void) const
  { return bloque; }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
any_const_ptr BloqueBase::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "BloqueBase::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod == "getNombre")
      { return any_const_ptr(nombre); }
    else
      return EntWOwner::GetProp(cod);
  }

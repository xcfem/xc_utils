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
//Locale.cc

#include "Locale.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Constructor.
Locale::Locale(EntCmd *owr)
  : EntWOwner(owr), loc(std::locale("")) {}

//! Lee un objeto Locale desde archivo
//! Soporta los comandos:
//! -cond: Lee la condición del if.
//! -then: Lee el código a ejecutar si se cumple la condición.
//! -else: Lee el código a ejecutar si no se cumple la condición.
bool Locale::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "Locale; procesando comando: " << cmd << std::endl;
    if(cmd == "set")
      {
        const std::string &nombre= interpretaString(status.GetBloque(true));
        loc= std::locale(nombre.c_str());
        return true;
      }
    else
      return EntWOwner::procesa_comando(status);
  }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
any_const_ptr Locale::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "Locale::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod == "name")
      {
        tmp_gp_str= loc.name();
        return any_const_ptr(tmp_gp_str);
      }
    else
      return EntWOwner::GetProp(cod);
  }

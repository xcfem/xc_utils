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
//EntConNmb.cc

#include "EntConNmb.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "any_const_ptr.h"

//! Lee un objeto EntConNmb desde archivo
//! Soporta el comando "codigo" que lee el nombre del
//! objeto del archivo.
bool EntConNmb::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(EntConNmb: " << GetNombre() << ") Procesando comando: " << cmd << std::endl;
    if(cmd == "codigo")
      {
        nmb= interpretaString(status.GetString());
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! Devuelve la propiedad del objeto cuyo código se pasa
//! como parámetro.
//! Soporta el comando "codigo" o "nombre" (sinónimos) que
//! devuelven el nombre del objeto del archivo.
any_const_ptr EntConNmb::GetProp(const std::string &cod) const
  {
    if(cod=="nombre" || cod=="codigo")
      return any_const_ptr(GetNombre());
    else
      return EntCmd::GetProp(cod);
  }

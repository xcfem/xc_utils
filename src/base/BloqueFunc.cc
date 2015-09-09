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
//BloqueFunc.cc

#include "BloqueFunc.h"
#include "xc_utils/src/base/CmdStatus.h"
#include <boost/algorithm/string/trim.hpp>
#include "any_const_ptr.h"
#include "utils_any.h"

//! @brief Constructor.
BloqueFunc::BloqueFunc(EntCmd *owner, const std::string &nmb)
  : BloqueSub(owner,nmb), tipo_retval() {}

//! @brief Constructor.
BloqueFunc::BloqueFunc(EntCmd *owner, const std::string &nmb,const std::string &b,const std::string &def_args)
  : BloqueSub(owner,nmb,b,def_args), tipo_retval() {}
//! @brief Constructor de copia.
BloqueFunc::BloqueFunc(const BloqueFunc &otro)
  : BloqueSub(otro), tipo_retval(otro.tipo_retval) {}

//! @brief Operador asignación.
BloqueFunc &BloqueFunc::operator=(const BloqueFunc &otro)
  {
    tipo_retval= otro.tipo_retval;
    BloqueSub::operator=(otro);
    return *this;
  }

//! Lee un objeto BloqueFunc desde archivo
//! Soporta los comandos:
bool BloqueFunc::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "BloqueFunc; (" << nombre << ") procesando comando: " << cmd << std::endl;

    if(cmd == "tipo")
      {
        tipo_retval= interpretaString(status.GetString());
        return true;
      }
    else if(cmd == "return")
      {
        const std::string tmp= boost::trim_copy_if(boost::trim_copy(status.GetString()),boost::is_any_of("'"));
        interpretaUno(tmp);

        return true;
      }
    else
      return BloqueSub::procesa_comando(status);
  }

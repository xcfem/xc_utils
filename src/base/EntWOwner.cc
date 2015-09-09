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
//EntWOwner.cc

#include "EntWOwner.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Constructor.
EntWOwner::EntWOwner(EntCmd *owr)
  : EntCmd(owr) {}

//! Lee un objeto EntWOwner desde archivo
bool EntWOwner::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "EntWOwner; procesando comando: " << cmd << std::endl;
    if(cmd == "owner")
      {
	std::cerr << "El comando owner ESTÁ OBSOLETO, no debe emplearse." << std::endl;
        const std::string str= status.GetBloque();
        assert(Owner());
        Owner()->EjecutaBloque(str,"owner");
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
any_const_ptr EntWOwner::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntWOwner::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    return EntCmd::GetProp(cod);
  }

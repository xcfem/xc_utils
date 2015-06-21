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
//GeneradorCombinaciones.cc

#include "GeneradorCombinaciones.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "Combinaciones.h"

//! @brief Constructor.
cmb_acc::GeneradorCombinaciones::GeneradorCombinaciones(EntCmd *owr)
  : EntCmd(owr), combinaciones(NULL) {}

//! @brief Define la ponderación cuyo nombre se pasa como parámetro.
cmb_acc::AccionesClasificadas *cmb_acc::GeneradorCombinaciones::defPonderacion(const std::string &nmb,const MapCoefsPsi &coefs)
  { return pond_acciones.defPonderacion(nmb,coefs); }

//! @brief Inserta la acción que se pasa como parámetro.
cmb_acc::VRAccion &cmb_acc::GeneradorCombinaciones::inserta(const std::string &pond,const std::string &familia,const Accion &acc,const std::string &nmb_coefs_psi,const std::string &subfamilia)
  { return pond_acciones.inserta(pond,familia,acc,nmb_coefs_psi,subfamilia); }

//! @brief Generación de combinaciones
void cmb_acc::GeneradorCombinaciones::genera(void)
  {
    if(combinaciones) //Ya se generaron anteriormente.
      {
        delete combinaciones;
        combinaciones= NULL;
      }
    else
      combinaciones= new Combinaciones(pond_acciones.getCombinaciones());
  }

//! \fn cmb_acc::GeneradorCombinaciones::procesa_comando(CmdStatus &status)
//! @brief Lee el objeto desde archivo.
bool cmb_acc::GeneradorCombinaciones::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(GeneradorCombinaciones) Procesando comando: " << cmd << std::endl;
    if(cmd == "pond_acciones")
      {
        pond_acciones.LeeCmd(status);
        return true;
      }
    else if(cmd == "genera_combinaciones")
      {
        status.GetString(); //Ignora argumentos.
        genera();
        return true;
      }
    else if(cmd == "combinaciones")
      {
        if(!combinaciones) genera();
        combinaciones->LeeCmd(status);
        return true;          
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Devuelve la propiedad cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::GeneradorCombinaciones::GetProp(const std::string &cod) const
  {
    if(cod == "combGeneradas")
      {
        tmp_gp_bool= (combinaciones!=NULL);
        return any_const_ptr(tmp_gp_bool);
      }
    else if(cod == "combinaciones")
      return any_const_ptr(combinaciones);
    else
      return EntCmd::GetProp(cod);
  }

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
//Combinaciones.cc

#include "Combinaciones.h"
#include "xc_utils/src/loadCombinations/acciones/AccionesClasificadas.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Constructor por defecto.
cmb_acc::Combinaciones::Combinaciones(void)
 {}

//! @brief Constructor.
cmb_acc::Combinaciones::Combinaciones(const AccionesClasificadas &acc)
  : comb_uls_transient(acc.GetPersistentesOTransit()), comb_uls_accid(acc.GetAccidentales()),
    comb_uls_sism(acc.GetSismicas()), comb_sls_poco_frec(acc.GetPocoFrecuentes()),
    comb_sls_frec(acc.GetFrecuentes()), comb_sls_cuasi_perm(acc.GetCuasiPermanentes())
  {}

//! \fn cmb_acc::Combinaciones::procesa_comando(CmdStatus &status)
//! @brief Lee el objeto desde archivo.
bool cmb_acc::Combinaciones::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(Combinaciones) Procesando comando: " << cmd << std::endl;
    if(cmd == "comb_uls_transiententes")
      {
        comb_uls_transient.set_owner(this);
        comb_uls_transient.LeeCmd(status);
        return true;
      }
    else if(cmd == "comb_uls_accidentales")
      {
        comb_uls_accid.set_owner(this);
        comb_uls_accid.LeeCmd(status);
        return true;
      }
    else if(cmd == "comb_uls_sismicas")
      {
        comb_uls_sism.set_owner(this);
        comb_uls_sism.LeeCmd(status);
        return true;
      }
    else if(cmd == "comb_sls_poco_frecuentes")
      {
        comb_sls_poco_frec.set_owner(this);
        comb_sls_poco_frec.LeeCmd(status);
        return true;
      }
    else if(cmd == "comb_sls_frecuentes")
      {
        comb_sls_frec.set_owner(this);
        comb_sls_frec.LeeCmd(status);
        return true;
      }
    else if(cmd == "comb_sls_cuasi_permanentes")
      {
        comb_sls_cuasi_perm.set_owner(this);
        comb_sls_cuasi_perm.LeeCmd(status);
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Concatena las combinaciones de ambos objetos.
void cmb_acc::Combinaciones::Concat(const Combinaciones &otras)
  {
    comb_uls_transient= VectorCombinaciones::Concat(comb_uls_transient,otras.comb_uls_transient,0.0);
    comb_uls_accid= VectorCombinaciones::Concat(comb_uls_accid,otras.comb_uls_accid,0.0);
    comb_uls_sism= VectorCombinaciones::Concat(comb_uls_sism,otras.comb_uls_sism,0.0);
    comb_sls_poco_frec= VectorCombinaciones::Concat(comb_sls_poco_frec,otras.comb_sls_poco_frec,0.0);
    comb_sls_frec= VectorCombinaciones::Concat(comb_sls_frec,otras.comb_sls_frec,0.0);
    comb_sls_cuasi_perm= VectorCombinaciones::Concat(comb_sls_cuasi_perm,otras.comb_sls_cuasi_perm,0.0);
  }

//! @brief Devuelve la propiedad cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::Combinaciones::GetProp(const std::string &cod) const
  {
    if(cod == "getNumCombULS")
      {
        tmp_gp_szt= comb_uls_transient.size()+comb_uls_accid.size()+comb_uls_sism.size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "getNumCombELS")
      {
        tmp_gp_szt= comb_sls_poco_frec.size()+comb_sls_frec.size()+comb_sls_cuasi_perm.size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "comb_uls_transiententes")
      return any_const_ptr(&comb_uls_transient);
    else if(cod == "comb_uls_accidentales")
      return any_const_ptr(&comb_uls_accid);
    else if(cod == "comb_uls_sismicas")
      return any_const_ptr(&comb_uls_sism);
    else if(cod == "comb_sls_poco_frecuentes")
      return any_const_ptr(&comb_sls_poco_frec);
    else if(cod == "comb_sls_frecuentes")
      return any_const_ptr(&comb_sls_frec);
    else if(cod == "comb_sls_cuasi_permanentes")
      return any_const_ptr(&comb_sls_cuasi_perm);
    else
      return EntCmd::GetProp(cod);
  }


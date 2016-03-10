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
//VRAccion.cxx

#include "xc_utils/src/loadCombinations/actions/VRAccion.h"
#include "xc_utils/src/loadCombinations/actions/ListaVRAccion.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/loadCombinations/coeffs/GammaF.h"
#include "xc_utils/src/loadCombinations/coeffs/PsiCoeffsMap.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

//! @brief Constructor por defecto.
cmb_acc::VRAccion::VRAccion(const std::string &n, const std::string &descrip,ListaVRAccion *fam)
  : Accion(n,descrip), acc_familia(fam), coefs_psi(&PsiCoeffsMap::getCoefsPorDefecto()) {}

//! @brief Constructor por defecto.
cmb_acc::VRAccion::VRAccion(const Accion &a,ListaVRAccion *fam,const std::string &nmb_coefs)
  : Accion(a), acc_familia(fam), coefs_psi(&PsiCoeffsMap::getCoefsPorDefecto()) 
  {
    setPsiCoeffs(nmb_coefs);
  }

//! @brief Asigna los coeficientes de simultaneidad de la acción.
void cmb_acc::VRAccion::setPsiCoeffs(const std::string &nmb_coefs)
  {
    if(!nmb_coefs.empty())
      {
        const PsiCoeffs *tmp=NULL;
        if(acc_familia)
          tmp= acc_familia->getPtrPsiCoeffs()->getPtrCoefs(nmb_coefs);
        else
          std::cerr << "VRAccion::setPsiCoeffs; el puntero a la familia de acciones no está asignado." << std::endl;
        if(tmp)
           coefs_psi= tmp;
      }
  }

//! \fn cmb_acc::VRAccion::procesa_comando(CmdStatus &status)
//! @brief Lee el objeto desde archivo.
bool cmb_acc::VRAccion::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    const std::string str_err= "(VRAccion) Procesando comando: " + cmd; 
    if(verborrea>2)
      std::clog << str_err << std::endl;

    if(cmd == "setPsiCoeffs")
      {
        setPsiCoeffs(interpretaString(status.GetString()));
        return true;
      }
    else
      return Accion::procesa_comando(status);
  }

double cmb_acc::VRAccion::getPsi(short int r) const
  { return coefs_psi->getPsi(r); }

//! \fn cmb_acc::Accion cmb_acc::VRAccion::Valor(short int r) const
//! @brief Devuelve el valor representativo de la acción.
cmb_acc::Accion cmb_acc::VRAccion::Valor(short int r) const
  {
    Accion retval(*this);
    switch(r)
      {
      case(-1):
        break; //Valor característico.
      case(0):
        retval*=getPsi(0); //Valor de combinación.
        break;
      case(1):
        retval*=getPsi(1); //Valor frecuente.
        break;
      case(2):
        retval*=getPsi(2); //Valor cuasipermanente.
        break;
      default:
        break;
      }
    return retval;
  }

//! \fn any_const_ptr cmb_acc::VRAccion::GetProp(const std::string &cod) const
//! @brief Devuelve la propiedad del objeto cuyo código se pasa
//! como parámetro.
any_const_ptr cmb_acc::VRAccion::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "VRAccion::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod == "coefs_psi")
      return any_const_ptr(coefs_psi);
    else if(cod == "psi_0")
      {
        tmp_gp_dbl= getPsi(0);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "psi_1")
      {
        tmp_gp_dbl= getPsi(1);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "psi_2")
      {
        tmp_gp_dbl= getPsi(2);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "incompatibles")
      {
        tmp_gp_str= ListaStrIncompatibles(acc_familia);
        return any_const_ptr(tmp_gp_str);
      }
    else
      return Accion::GetProp(cod);
  }

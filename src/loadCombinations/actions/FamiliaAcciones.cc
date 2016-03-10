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
//FamiliaAcciones.cxx

#include "FamiliaAcciones.h"
#include "AccionesClasificadas.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variations.h"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationVector.h"
#include "MapFamiliasAcc.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "Accion.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

//! @brief Constructor por defecto.
cmb_acc::FamiliaAcciones::FamiliaAcciones(const std::string &nmb,const GammaF &gf)
  : EntConNmb(nmb),gammaf(gf) 
  {
    acciones.set_owner(this);
  }

//! @brief Lanza la ejecución del bloque de código que se pasa
//! como parámetro para cada una de las acciones de la familia.
void cmb_acc::FamiliaAcciones::for_each_accion(CmdStatus &status,const std::string &bloque)
  { acciones.for_each(status,bloque); }

//! \fn cmb_acc::FamiliaAcciones::procesa_comando(CmdStatus &status)
//! @brief Lee el objeto desde archivo.
bool cmb_acc::FamiliaAcciones::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(FamiliaAcciones) Procesando comando: " << cmd.c_str() << std::endl;
    if(cmd == "gammaf") //Lee coeficientes de ponderación de acciones.
      {
        gammaf.set_owner(this);
        gammaf.LeeCmd(status);
        return true;
      }
    else if(cmd == "acciones")
      {
        acciones.set_owner(this);
        acciones.LeeCmd(status);
        return true;
      }
    else if(cmd == "for_each_accion")
      {
        const std::string bloque= status.GetBloque();
        for_each_accion(status,bloque);
        return true;
      }
    else
      return EntConNmb::procesa_comando(status);
  }

//! @brief Devuelve un apuntador a los coeficientes que aplican para esta familia.
const cmb_acc::PsiCoeffsMap *cmb_acc::FamiliaAcciones::getPtrPsiCoeffs(void) const
  {
    const AccionesClasificadas *tmp= dynamic_cast<const AccionesClasificadas *>(Owner());
    if(tmp)
      return tmp->getPtrPsiCoeffs();
    else
      {
	std::cerr << "FamiliaAcciones::getPtrPsiCoeffs; no se encontró el objeto propietario de éste." << std::endl;
        return NULL;
      }
  }

//! @brief Inserta la acción que se le pasa como parámetro y le asigna los coeficientes de
//! simultaneidad cuyo nombre se pasa como parámetro.
cmb_acc::VRAccion &cmb_acc::FamiliaAcciones::inserta(const Accion &a,const std::string &nmb_coefs_psi)
  { return acciones.inserta(a,nmb_coefs_psi); }

//! @brief ??
//!
//! @param elu: Verdadero si se trata de un estado límite último.
//! @param sit_accidental: Verdadero si estamos en situación accidental.
//! @param r: Valor representativo para el caso general (r= -1 -> valor característico,r= 0 -> valor de combinación
//! r= 1 -> valor frecuente, r= 2 -> valor cuasipermanente).
//! @param d: Índice de la acción dominante (si no hay acción dominante d=-1).
//! @param rr: Valor representativo a emplear para la acción dominante.
cmb_acc::LoadCombinationVector cmb_acc::FamiliaAcciones::GetLoadCombinations(const bool &elu,const bool &sit_accidental,short int r,const int &d,const short int &rr) const
  {
    Variations var= CalculaVariations(elu,sit_accidental,d);
    const size_t num_variations= var.size();
    LoadCombinationVector retval(num_variations);
    FamiliaAcciones *this_no_const= const_cast<FamiliaAcciones *>(this);
    for(size_t i=0;i<num_variations;i++)
      {
        const Variation &v_i= var[i];
        retval[i]= acciones.FormaProdEscalar(v_i,r,d,rr);
        retval[i].set_owner(this_no_const);
      }
    retval= getCompatibles(retval); //Filtramos las que contienen acciones incompatibles.
    retval= retval.GetDistintas(); //Eliminamos las repetidas.
    return retval;
  }

//! \fn cmb_acc::FamiliaAcciones::CalculaVariations(const bool &elu,const bool &sit_accidental) const
//! @brief ??
cmb_acc::Variations cmb_acc::FamiliaAcciones::CalculaVariations(const bool &elu,const bool &sit_accidental,const int &d) const
  { return gammaf.calcula_variations(elu,sit_accidental,d,acciones); }

//! \fn any_const_ptr cmb_acc::FamiliaAcciones::GetProp(const std::string &cod) const
//! @brief Devuelve la propiedad del objeto cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::FamiliaAcciones::GetProp(const std::string &cod) const
  {
    if(cod == "num_acciones")
      {
        tmp_gp_szt= acciones.size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "num_familias")
      {
        tmp_gp_szt= 1;
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "lista_acciones")
      {
        tmp_gp_str= nombresAcciones(acciones.begin(),acciones.end());
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "acciones")
      return any_const_ptr(&acciones);
    else if(cod == "gammaf")
      return any_const_ptr(&gammaf);
    else
      return EntConNmb::GetProp(cod);
  }

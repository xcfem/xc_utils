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
//ActionsFamily.cxx

#include "ActionsFamily.h"
#include "ActionContainer.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variations.h"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationVector.h"
#include "ActionsFamiliesMap.h"
#include "Action.h"



//! @brief Constructor por defecto.
cmb_acc::ActionsFamily::ActionsFamily(const std::string &nmb,const GammaF &gf)
  : EntConNmb(nmb),gammaf(gf) 
  {
    actions.set_owner(this);
  }

//! @brief Return un apuntador a los coeficientes que aplican para esta familia.
const cmb_acc::PsiCoeffsMap *cmb_acc::ActionsFamily::getPtrPsiCoeffs(void) const
  {
    const cmb_acc::PsiCoeffsMap *retval= nullptr;
    const EntCmd *owr= Owner();
    const ActionContainer *tmp= dynamic_cast<const ActionContainer *>(owr);
    if(tmp)
      return tmp->getPtrPsiCoeffs();
    else
      {
	const ActionsFamiliesMap *fMap= dynamic_cast<const ActionsFamiliesMap *>(owr);
	if(fMap)
	  {
	    const ActionContainer *ac= dynamic_cast<const ActionContainer *>(fMap->Owner());
	    if(ac)
	      tmp= dynamic_cast<const ActionContainer *>(ac);
	  }
      }
    if(tmp)
      retval= tmp->getPtrPsiCoeffs();
    else
      std::cerr << getClassName() << "::" << __FUNCTION__
 	        << "; family: '" << getName()
		<< "' owner not found." << std::endl;
    return retval;
  }

//! @brief Insert the action argument and sets the "psi" load combination
//! factors.
cmb_acc::ActionRValue &cmb_acc::ActionsFamily::insert(const Action &a,const std::string &nmb_coefs_psi)
  { return actions.insert(a,nmb_coefs_psi); }

//! @brief ??
//!
//! @param elu: Verdadero si se trata de un estado límite último.
//! @param sit_accidental: Verdadero si estamos en situación accidental.
//! @param r: Valor representativo para el caso general (r= -1 -> characteristic value,r= 0 -> valor de combinación
//! r= 1 -> valor frecuente, r= 2 -> valor cuasipermanente).
//! @param d: Índice de la acción dominante (si no hay acción dominante d=-1).
//! @param rr: Valor representativo a emplear para la acción dominante.
cmb_acc::LoadCombinationVector cmb_acc::ActionsFamily::GetLoadCombinations(const bool &elu,const bool &sit_accidental,short int r,const int &d,const short int &rr) const
  {
    Variations var= computeVariations(elu,sit_accidental,d);
    const size_t num_variations= var.size();
    LoadCombinationVector retval(num_variations);
    ActionsFamily *this_no_const= const_cast<ActionsFamily *>(this);
    for(size_t i=0;i<num_variations;i++)
      {
        const Variation &v_i= var[i];
        retval[i]= actions.FormaProdEscalar(v_i,r,d,rr);
        retval[i].set_owner(this_no_const);
      }
    retval= getCompatibles(retval); //Filtramos las que contienen incompatible actions.
    retval= retval.GetDistintas(); //Eliminamos las repetidas.
    return retval;
  }

//! \fn cmb_acc::ActionsFamily::computeVariations(const bool &elu,const bool &sit_accidental) const
//! @brief ??
cmb_acc::Variations cmb_acc::ActionsFamily::computeVariations(const bool &elu,const bool &sit_accidental,const int &d) const
  { return gammaf.calcula_variations(elu,sit_accidental,d,actions); }


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
#include "ActionsAndFactors.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variations.h"
#include "xc_utils/src/loadCombinations/comb_analysis/LoadCombinationVector.h"
#include "Action.h"
#include "LeadingActionInfo.h"



//! @brief Default constructor.
cmb_acc::ActionsFamily::ActionsFamily(const std::string &nmb)
  : NamedEntity(nmb)
  {
    actions.set_owner(this);
  }

//! @brief Return the container that contains this object.
const  cmb_acc::ActionsAndFactors *cmb_acc::ActionsFamily::getActionsAndFactors(void) const
  {
    const CommandEntity *owr= Owner();
    const ActionsAndFactors *retval= dynamic_cast<const ActionsAndFactors *>(owr);
    if(!retval)
      std::cerr << getClassName() << "::" << __FUNCTION__
 	        << "; family: '" << getName()
		<< "' owner not found." << std::endl;
    return retval;
  }

//! @brief Return a pointer to the combination factors container.
const cmb_acc::CombinationFactorsMap *cmb_acc::ActionsFamily::getPtrCombinationFactors(void) const
  {
    const cmb_acc::CombinationFactorsMap *retval= nullptr;
    const ActionsAndFactors *tmp= getActionsAndFactors();
    if(tmp)
      retval= tmp->getFactors().getPtrCombinationFactors();
    return retval;
  }

//! @brief Return a pointer to the partial safety factors container.
const cmb_acc::PartialSafetyFactorsMap *cmb_acc::ActionsFamily::getPtrPartialSafetyFactors(void) const
  {
    const cmb_acc::PartialSafetyFactorsMap *retval= nullptr;
    const ActionsAndFactors *tmp= getActionsAndFactors();
    if(tmp)
      retval= tmp->getFactors().getPtrPartialSafetyFactors();
    return retval;
  }

//! @brief Insert the action argument and sets the "psi" load combination
//! factors.
cmb_acc::ActionRValue &cmb_acc::ActionsFamily::insert(const Action &a,const std::string &combination_factors_name,const std::string &partial_safety_factors_name)
  { return actions.insert(a,combination_factors_name,partial_safety_factors_name); }




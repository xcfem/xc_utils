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
//ActionRValue.cxx

#include "xc_utils/src/loadCombinations/actions/ActionRValue.h"
#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"
#include "xc_utils/src/loadCombinations/factors/PartialSafetyFactors.h"
#include "xc_utils/src/loadCombinations/factors/CombinationFactorsMap.h"



//! @brief Constructor por defecto.
cmb_acc::ActionRValue::ActionRValue(const std::string &n, const std::string &descrip,ActionRValueList *fam)
  : Action(n,descrip), acc_familia(fam), combination_factors(&CombinationFactorsMap::getCoefsPorDefecto()) {}

//! @brief Constructor por defecto.
cmb_acc::ActionRValue::ActionRValue(const Action &a,ActionRValueList *fam,const std::string &nmb_factors)
  : Action(a), acc_familia(fam), combination_factors(&CombinationFactorsMap::getCoefsPorDefecto()) 
  {
    setCombinationFactors(nmb_factors);
  }

//! @brief Asigna los coeficientes de simultaneidad de la acción.
void cmb_acc::ActionRValue::setCombinationFactors(const std::string &nmb_factors)
  {
    if(!nmb_factors.empty())
      {
        const CombinationFactors *tmp=nullptr;
        if(acc_familia)
          tmp= acc_familia->getPtrCombinationFactors()->getPtrCoefs(nmb_factors);
        else
          std::cerr << getClassName() << "::" << __FUNCTION__
	            << "; pointer to actions family not set." << std::endl;
        if(tmp)
           combination_factors= tmp;
	else
          std::cerr << getClassName() << "::" << __FUNCTION__
	            << "; combination factors with name: '" << nmb_factors
	            << "' not found." << std::endl;	  
      }
  }

//! @brief Return the r-th combination factor.
double cmb_acc::ActionRValue::getCombinationFactor(short int r) const
  { return combination_factors->getCombinationFactor(r); }

//! @brief Return the representative value of the action.
cmb_acc::Action cmb_acc::ActionRValue::Valor(short int r) const
  {
    Action retval(*this);
    switch(r)
      {
      case(-1):
        break; //characteristic value.
      case(0):
        retval*=getCombinationFactor(0); //Valor de combinación.
        break;
      case(1):
        retval*=getCombinationFactor(1); //Valor frecuente.
        break;
      case(2):
        retval*=getCombinationFactor(2); //Valor cuasipermanente.
        break;
      default:
        break;
      }
    return retval;
  }

//! @brief Print stuff.
void cmb_acc::ActionRValue::Print(std::ostream &os) const
  {
    Action::Print(os);
    if(combination_factors)
      os << "; " << *combination_factors;
  }

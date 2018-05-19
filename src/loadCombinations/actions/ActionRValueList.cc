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
//ActionRValueList.cxx

#include "ActionRValueList.h"
#include "ActionsFamily.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variation.h"
#include "LeadingActionInfo.h"

cmb_acc::ActionRValue &cmb_acc::ActionRValueList::push_back(const ActionRValue &a)
  {
    std::deque<ActionRValue>::push_back(a);
    ActionRValue &retval= back();
    return retval;
  }

//! @brief Insert the action being passed as parameter.
cmb_acc::ActionRValue &cmb_acc::ActionRValueList::insert(const Action &a,const std::string &combination_factors_name)
  {
    ActionRValue acc(a,this,combination_factors_name);
    acc.set_owner(this);
    return push_back(acc);
  }

//! @brief Return the representative value of the j-th action.
cmb_acc::Action cmb_acc::ActionRValueList::getRepresentativeValue(const LeadingActionInfo &lai,const size_t &j) const
  {
    Action retval= getValue(j,lai.getGeneralRepresentativeValueIndex());
    if(lai.leadingActionExists())
      if(lai.isLeadingActionIndex(j)) //j is the leading action index.
	{
	  retval= getValue(j,lai.getLeadingRepresentativeValueIndex()); //Representative value for the leading action.
	}
    return retval;
  }

//! \fn cmb_acc::ActionRValueList::FormaProdEscalar(const Variation &v,short int r,const int &d,const short int &rr) const
//! @brief Forma producto escalar.
//!
//! @param v: Variation a sumar.
//! @param leadingActioInfo: Information about the leading action.
cmb_acc::Action cmb_acc::ActionRValueList::FormaProdEscalar(const Variation &var,const LeadingActionInfo &lai) const//short int r,const int &d,const short int &rr) const
  {
    const size_t num_acciones= size();
    Action retval=Action::NULA(); //Initialize to zero.
    for(size_t j=0;j<num_acciones;j++)
      retval+=var[j]*getRepresentativeValue(lai,j);
    return retval;
  }

//! @brief Return a pointer to the table of coeficientes de simultaneidad.
const cmb_acc::CombinationFactorsMap *cmb_acc::ActionRValueList::getPtrCombinationFactors(void) const
  {
    const ActionsFamily *tmp= dynamic_cast<const ActionsFamily *>(Owner());
    if(tmp)
      return tmp->getPtrCombinationFactors();
    else
      {
	std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; owner not found." << std::endl;
        return nullptr;
      }
  }

void cmb_acc::ActionRValueList::Print(std::ostream &os) const
  {
    for(const_iterator i=begin();i!=end();i++)
      os << *i << ' ';
  }

//! @brief Operador salida.
std::ostream &cmb_acc::operator<<(std::ostream &os,const ActionRValueList &lvr)
  {
    lvr.Print(os);
    return os;
  }

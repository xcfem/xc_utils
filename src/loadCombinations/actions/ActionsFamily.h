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
//ActionsFamily.h


#ifndef FAMILIAACCIONES_H
#define FAMILIAACCIONES_H

#include "xc_utils/src/loadCombinations/factors/PartialSafetyFactors.h"
#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"

namespace cmb_acc{
class Variations;
class LoadCombinationVector;
class CombinationFactorsMap;
class ActionsAndFactors;
class ActionsFamiliesMap;
class LeadingActionInfo;

//! @ingroup CMBACC
//
//! @brief Family of actions (permanent, variable, accidental,...)
//!
//! Set of actions that share the same set of partial safety factors, for example::
//! -Permanent actions.
//! -Variable actions.
//! -Accidental actions.
//! -Earthquake actions.
class ActionsFamily: public EntConNmb
  {
  private:
    PartialSafetyFactors partial_safety_factors; //!< Partial safety factors para toda la familia.
    ActionRValueList actions; //!< Family actions container.

  protected:
    friend class ActionsFamiliesMap;
    friend class ActionsAndFactors;
  public:
    ActionsFamily(const std::string &nmb="",const PartialSafetyFactors &gf=PartialSafetyFactors());
    inline virtual ~ActionsFamily(void) {}
    ActionRValue &insert(const Action &,const std::string &combination_factors_name="");

    //! @brief Return the number of actions in the family.
    inline size_t getNumActions(void) const
      { return actions.size(); }
    inline const ActionRValueList &getActions(void) const
      { return actions; }
    inline ActionRValueList &getActions(void)
      { return actions; }
    inline void setActions(const ActionRValueList &acc)
      { actions= acc; }

    //! brief Return true if no actions in the family.
    inline bool empty(void) const
      { return actions.empty(); }

    inline void setPartialSafetyFactors(const PartialSafetyFactors &gf)
      { partial_safety_factors= gf; }
    inline PartialSafetyFactors &getPartialSafetyFactors(void)
      { return partial_safety_factors; }
    
    const ActionsAndFactors *getActionsAndFactors(void) const;
    const CombinationFactorsMap *getPtrCombinationFactors(void) const;
    
    Variations computeVariations(const bool &uls= true,const bool &sit_accidental= false,const int &d=-1) const;
    LoadCombinationVector getLoadCombinations(const bool &uls,const bool &sit_accidental,const LeadingActionInfo &) const;
  };
} //fin namespace nmb_acc.

#endif

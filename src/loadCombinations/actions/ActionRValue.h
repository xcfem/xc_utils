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
//ActionRValue.hxx
//Representative values of an action.

#ifndef ACTIONRVALUE_H
#define ACTIONRVALUE_H

#include "Action.h"

namespace cmb_acc{

class PartialSafetyFactors;
class CombinationFactors;
class Variations;
class LeadingActionInfo;

//! @ingroup CMBACC
//
//! @brief Representative values of an action.
class ActionRValue: public Action
  {
  private:
    ActionRValueList *acc_familia; //!< Container for the actions of the family.
    const PartialSafetyFactors *partial_safety_factors; //!< Partial safety factors for this action.
    const CombinationFactors *combination_factors; //!< Combination factors.

    inline double getCombinationFactor(short int r) const;

  protected:
    friend class ActionRValueList;
    //! @brief Constructor por defecto.
    ActionRValue(const std::string &n="", const std::string &descrip="",ActionRValueList *fam= nullptr);
    ActionRValue(const Action &a,ActionRValueList *fam= nullptr,const std::string &nmb_comb_factors= "",const std::string &nmb_partial_safety_factors= "");
  public:
    Action getValue(short int r) const;
    void setCombinationFactors(const std::string &);
    const PartialSafetyFactors *getPartialSafetyFactors(void) const;
    void setPartialSafetyFactors(const std::string &);
    int getIndex(void) const; 
    Variations getVariations(const bool &,const bool &) const;
    Action getRepresentativeValue(const LeadingActionInfo &) const;    
    Action getCombinationValue(const LeadingActionInfo &, const double &) const;    
    void Print(std::ostream &os) const;    
  };

} //fin namespace nmb_acc.

#endif

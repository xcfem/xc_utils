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
//ActionRValueList.hxx
//Conjunto de acciones.

#ifndef LISTAVRACCION_HXX
#define LISTAVRACCION_HXX

#include "xc_utils/src/kernel/CommandEntity.h"
#include <deque>
#include "ActionRValue.h"

namespace cmb_acc{
class Variation;
class Variations;
class CombinationFactorsMap;
class PartialSafetyFactorsMap;
class ActionsFamily;

//! @ingroup CMBACC
//
//! @brief List of representative values of actions (objetos ActionRValue).
class ActionRValueList: public std::deque<ActionRValue>, public CommandEntity
  {
    friend class Variation;
    friend class ActionsFamily;

    ActionRValue &push_back(const ActionRValue &a);
  public:
    int getIndex(const ActionRValue *) const;
    ActionRValue &insert(const Action &,const std::string &,const std::string &);
    Action buildCombination(const Variation &v,const LeadingActionInfo &) const;
    const CombinationFactorsMap *getPtrCombinationFactors(void) const;
    const PartialSafetyFactorsMap *getPtrPartialSafetyFactors(void) const;
    Variations computeVariations(const bool &,const bool &,const int &) const;
    LoadCombinationVector getCombinations(const bool &,const bool &,const LeadingActionInfo &) const;
    LoadCombinationVector getCombinationsWhenLeading(const bool &,const bool &,const short int &v) const;
    void Print(std::ostream &os) const;
  };

std::ostream &operator<<(std::ostream &os,const ActionRValueList &vs);

} //fin namespace nmb_acc.

#endif

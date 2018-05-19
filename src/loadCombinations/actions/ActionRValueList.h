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

#include "xc_utils/src/nucleo/EntCmd.h"
#include <deque>
#include "ActionRValue.h"

namespace cmb_acc{
class Variation;
class CombinationFactorsMap;
class ActionsFamily;
class LeadingActionInfo;

//! @ingroup CMBACC
//
//! @brief List of representative values of actions (objetos ActionRValue).
class ActionRValueList: public std::deque<ActionRValue>, public EntCmd
  {
    friend class Variation;
    friend class ActionsFamily;

    ActionRValue &push_back(const ActionRValue &a);
  public:
    //! @brief Return el valor de la acción de índice i
    inline Action getValue(const size_t &i,short int r) const
      { return (*this)[i].Valor(r); }
    Action getRepresentativeValue(const LeadingActionInfo &, const size_t &) const;
    ActionRValue &insert(const Action &,const std::string &);
    Action FormaProdEscalar(const Variation &v,const LeadingActionInfo &) const;
    const CombinationFactorsMap *getPtrCombinationFactors(void) const;
    void Print(std::ostream &os) const;
  };

std::ostream &operator<<(std::ostream &os,const ActionRValueList &vs);

} //fin namespace nmb_acc.

#endif

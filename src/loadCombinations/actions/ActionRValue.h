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
//Valores representativos de una acción.

#ifndef VRACCION_H
#define VRACCION_H

#include "Action.h"

namespace cmb_acc{

class GammaF;
class CombinationFactors;

//! @ingroup CMBACC
//
//! @brief Valores representativos de una acción.
class ActionRValue: public Action
  {
  private:
    ActionRValueList *acc_familia; //!< Container for the actions of the family.
    const GammaF *gammaf; //!< Partial safety factors for this action.
    const CombinationFactors *combination_factors; //!< Combination factors.

    inline double getCombinationFactor(short int r) const;

  protected:
    friend class ActionRValueList;
    //! @brief Constructor por defecto.
    ActionRValue(const std::string &n="", const std::string &descrip="",ActionRValueList *fam= nullptr);
    ActionRValue(const Action &a,ActionRValueList *fam= nullptr,const std::string &nmb_coefs= "");
  public:
    Action Valor(short int r) const;
    void setCombinationFactors(const std::string &);
    void Print(std::ostream &os) const;    
  };

} //fin namespace nmb_acc.

#endif

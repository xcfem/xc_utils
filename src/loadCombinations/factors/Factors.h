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
//Factors.h
//Container for the partial safety factors and the combination factors.

#ifndef FACTORS_H
#define FACTORS_H

#include "CombinationFactorsMap.h"
#include "PartialSafetyFactorsMap.h"

namespace cmb_acc{
//! @ingroup CMBACC
//
//! @brief Almacena todas las familias de acciones.
class Factors: public EntCmd
  {
  private:
    PartialSafetyFactorsMap partial_safety_factors; //!< Partial safety factors.
    CombinationFactorsMap combination_factors; //!< Combination factors.

  public:
    Factors(const PartialSafetyFactorsMap &psf= PartialSafetyFactorsMap(), const CombinationFactorsMap &cf= CombinationFactorsMap());

    const CombinationFactorsMap *getPtrCombinationFactors(void) const
      { return &combination_factors; }
    const CombinationFactorsMap &getCombinationFactors(void) const
      { return combination_factors; }
    const PartialSafetyFactorsMap *getPtrPartialSafetyFactors(void) const
      { return &partial_safety_factors; }
    const PartialSafetyFactorsMap &getPartialSafetyFactors(void) const
      { return partial_safety_factors; }
  };
} //fin namespace nmb_acc.

#endif

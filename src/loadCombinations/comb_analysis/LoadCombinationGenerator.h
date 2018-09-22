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
//LoadCombinationGenerator.h

#ifndef LOADCOMBINATIONGENERATOR_H
#define LOADCOMBINATIONGENERATOR_H

#include "ActionWeightingMap.h"

namespace cmb_acc{

class LoadCombinations;

//! @ingroup CMBACC
//
//! @brief Objeto that generates and manages the combinations.
class LoadCombinationGenerator: public CommandEntity
  {
  private:
    ActionWeightingMap action_weighting;
    LoadCombinations *combinations;
  public:
    LoadCombinationGenerator(CommandEntity *owr= nullptr);

    ActionRValue &insert(const std::string &pond,const std::string &,const Action &,const std::string &combination_factors_name="",const std::string &partial_safety_factors_name="");
    void genera(void);
    inline ActionWeightingMap &getActionWeighting(void)
      { return action_weighting; }
    inline void setActionWeighting(const ActionWeightingMap &pa)
      { action_weighting= pa; }
    inline LoadCombinations *getLoadCombinations(void)
      { return combinations; }
  };
} //fin namespace nmb_acc.


#endif

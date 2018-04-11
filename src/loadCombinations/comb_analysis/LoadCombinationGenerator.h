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
//! @brief Objeto encargado de generar y gestionar las combinaciones.
class LoadCombinationGenerator: public EntCmd
  {
  private:
    ActionWeightingMap action_weighting;
    LoadCombinations *combinaciones;
  public:
    LoadCombinationGenerator(EntCmd *owr= nullptr);

    ActionContainer *defPonderacion(const std::string &,const PsiCoeffsMap &coefs= PsiCoeffsMap());
    ActionRValue &insert(const std::string &pond,const std::string &,const Action &,const std::string &nmb_coefs_psi="",const std::string &subfamilia= "");
    void genera(void);
    inline ActionWeightingMap &getActionWeighting(void)
      { return action_weighting; }
    inline void setActionWeighting(const ActionWeightingMap &pa)
      { action_weighting= pa; }
    inline LoadCombinations *getLoadCombinations(void)
      { return combinaciones; }
  };
} //fin namespace nmb_acc.


#endif

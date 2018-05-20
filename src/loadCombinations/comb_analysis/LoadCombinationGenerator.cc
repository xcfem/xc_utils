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
//LoadCombinationGenerator.cc

#include "LoadCombinationGenerator.h"

#include "LoadCombinations.h"

//! @brief Constructor.
cmb_acc::LoadCombinationGenerator::LoadCombinationGenerator(EntCmd *owr)
  : EntCmd(owr), combinaciones(nullptr) {}

//! @brief Insert the action being passed as parameter.
cmb_acc::ActionRValue &cmb_acc::LoadCombinationGenerator::insert(const std::string &pond,const std::string &familia,const Action &acc,const std::string &combination_factors_name,const std::string &subfamilia)
  { return action_weighting.insert(pond,familia,acc,combination_factors_name,subfamilia); }

//! @brief Generación de combinaciones
void cmb_acc::LoadCombinationGenerator::genera(void)
  {
    if(combinaciones) //Ya se generaron anteriormente.
      {
        delete combinaciones;
        combinaciones= nullptr;
      }
    else
      combinaciones= new LoadCombinations(action_weighting.getLoadCombinations());
  }

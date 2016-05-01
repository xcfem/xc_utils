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

//! @brief Define la ponderación cuyo nombre se pasa como parámetro.
cmb_acc::ActionContainer *cmb_acc::LoadCombinationGenerator::defPonderacion(const std::string &nmb,const PsiCoeffsMap &coefs)
  { return action_weighting.defPonderacion(nmb,coefs); }

//! @brief Inserta la acción que se pasa como parámetro.
cmb_acc::ActionRValue &cmb_acc::LoadCombinationGenerator::inserta(const std::string &pond,const std::string &familia,const Action &acc,const std::string &nmb_coefs_psi,const std::string &subfamilia)
  { return action_weighting.inserta(pond,familia,acc,nmb_coefs_psi,subfamilia); }

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

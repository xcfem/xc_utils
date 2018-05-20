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
//ActionsAndFactors.h
//Almacena todas las familias de acciones para la estructura o el elemento estructural.

#ifndef ACTIONSANDFACTORS_H
#define ACTIONSANDFACTORS_H

#include "ActionContainer.h"
#include "xc_utils/src/loadCombinations/factors/Factors.h"

namespace cmb_acc{
//! @ingroup CMBACC
//
//! @brief Almacena todas las familias de acciones.
class ActionsAndFactors: public ActionContainer
  {
  private:
    Factors factors; //!< Factors to use to build combinations.

  protected:
    friend class ActionWeightingMap;
  public:
    ActionsAndFactors(const Factors &factors= Factors());

    const Factors &getFactors(void) const
      { return factors; }
  };
} //fin namespace nmb_acc.

#endif

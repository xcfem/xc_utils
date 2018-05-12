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
//ActionsFamily.h


#ifndef FAMILIAACCIONES_H
#define FAMILIAACCIONES_H

#include "xc_utils/src/loadCombinations/coeffs/GammaF.h"
#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"

namespace cmb_acc{
class Variations;
class LoadCombinationVector;
class PsiCoeffsMap;
class ActionContainer;
class ActionsFamiliesMap;

//! @ingroup CMBACC
//
//! @brief Family of actions (permanent, variable, accidental,...)
//!
//! Set of actions that share the same set of partial safety factors, for example::
//! -Permanent actions.
//! -Variable actions.
//! -Accidental actions.
//! -Earthquake actions.
class ActionsFamily: public EntConNmb
  {
  private:
    GammaF gammaf; //!< Partial safety factors para toda la familia.
    ActionRValueList actions; //!< Family actions container.

  protected:
    friend class ActionsFamiliesMap;
    friend class ActionContainer;
  public:
    ActionsFamily(const std::string &nmb="",const GammaF &gf=GammaF());
    inline virtual ~ActionsFamily(void) {}
    ActionRValue &insert(const Action &,const std::string &nmb_coefs_psi="");

    //! @brief Return the number of actions in the family.
    inline size_t getNumActions(void) const
      { return actions.size(); }
    inline const ActionRValueList &getActions(void) const
      { return actions; }
    inline ActionRValueList &getActions(void)
      { return actions; }
    inline void setActions(const ActionRValueList &acc)
      { actions= acc; }

    //! brief Return true if no actions in the family.
    inline bool empty(void) const
      { return actions.empty(); }

    inline void setGammaF(const GammaF &gf)
      { gammaf= gf; }
    inline GammaF &getGammaF(void)
      { return gammaf; }
    const PsiCoeffsMap *getPtrPsiCoeffs(void) const;
    
    Variations computeVariations(const bool &elu= true,const bool &sit_accidental= false,const int &d=-1) const;
    LoadCombinationVector GetLoadCombinations(const bool &elu,const bool &sit_accidental,short int r,const int &d=-1,const short int &rr=-1) const;
  };
} //fin namespace nmb_acc.

#endif

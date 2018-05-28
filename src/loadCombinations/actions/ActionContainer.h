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
//ActionContainer.h
//Almacena todas las familias de acciones para la estructura o el elemento estructural.

#ifndef ACTIONCONTAINER_H
#define ACTIONCONTAINER_H

#include "ActionsFamily.h"

namespace cmb_acc{
//! @ingroup CMBACC
//
//! @brief Almacena todas las familias de acciones.
class ActionContainer: public EntCmd
  {
  protected:
    ActionsFamily G; //!< Permanent actions.
    ActionsFamily G_aster; //!< Non-constant permanent actions.
    ActionsFamily Q; //!< Variable actions.
    ActionsFamily A; //!< Accidental actions.
    ActionsFamily AS; //!< Earthquake actions.

    LoadCombinationVector GetPermanentes(const bool &uls,const bool &sit_accidental) const;
    LoadCombinationVector GetVariables(const LoadCombinationVector &permanentes,const bool &uls,const bool &sit_accidental,const short int &v) const;
    LoadCombinationVector GetAccSis(const LoadCombinationVector &previas,const ActionsFamily &Acc) const;

  protected:
    friend class ActionWeightingMap;
  public:
    ActionContainer(void);
    inline virtual ~ActionContainer(void) {}

    ActionRValue &insert(const std::string &,const Action &,const std::string &combination_factors_name="",const std::string &partial_safety_factors_name="");

    const ActionsFamily &getPermanentActions(void) const;
    void setPermanentActions(const ActionsFamily &);
    const ActionsFamily &getPermanentActionsNC(void) const;
    void setPermanentActionsNC(const ActionsFamily &);
    const ActionsFamily &getVariableActions(void) const;
    void setVariableActions(const ActionsFamily &);
    const ActionsFamily &getAccidentalActions(void) const;
    void setAccidentalActions(const ActionsFamily &);
    const ActionsFamily &getSeismicActions(void) const;
    void setSeismicActions(const ActionsFamily &);
    
    //Estados límite últimos.
    LoadCombinationVector GetPersistentesOTransit(void) const;
    LoadCombinationVector GetAccidentales(void) const;
    LoadCombinationVector GetSismicas(void) const;
    LoadCombinationVector GetCombULS(void) const;
    //Estados límite de servicio.
    LoadCombinationVector GetPocoFrecuentes(void) const;
    LoadCombinationVector GetFrecuentes(void) const;
    LoadCombinationVector GetCuasiPermanentes(void) const;
    LoadCombinationVector GetCombSLS(void) const;

  };
} //fin namespace nmb_acc.

#endif

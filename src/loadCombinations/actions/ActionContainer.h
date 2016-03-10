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

#ifndef ACCIONESCLASIFICADAS_H
#define ACCIONESCLASIFICADAS_H

#include "ActionsFamily.h"
#include "ActionsFamiliesMap.h"
#include "xc_utils/src/loadCombinations/coeffs/PsiCoeffsMap.h"

namespace cmb_acc{
//! @ingroup CMBACC
//
//! @brief Almacena todas las familias de acciones.
class ActionContainer: public EntCmd
  {
  private:
    ActionsFamily G; //!< Acciones permanentes.
    ActionsFamiliesMap G_aster; //!< Acciones permanentes de valor no constante.
    ActionsFamily Q; //!< Acciones variables.
    ActionsFamily A; //!< Acciones accidentales.
    ActionsFamily AS; //!< Acciones sísmicas.
    PsiCoeffsMap coefs_psi; //!< Coeficientes de simultaneidad de las acciones.

    LoadCombinationVector GetLoadCombinationsG(const bool &elu,const bool &sit_accidental) const;
    LoadCombinationVector GetLoadCombinationsG_aster(const bool &elu,const bool &sit_accidental) const;
    LoadCombinationVector GetLoadCombinationsQ(const bool &elu,const bool &sit_accidental,short int r,int d=-1,short int rr=-1) const;
    LoadCombinationVector GetLoadCombinationsA(short int r,int d=-1,short int rr=-1) const;
    LoadCombinationVector GetLoadCombinationsAS(short int r,int d=-1,short int rr=-1) const;
    LoadCombinationVector GetPermanentes(const bool &elu,const bool &sit_accidental) const;
    LoadCombinationVector GetVariables(const LoadCombinationVector &permanentes,const bool &elu,const bool &sit_accidental,const short int &v) const;
    LoadCombinationVector GetAccSis(const LoadCombinationVector &previas,const ActionsFamily &Acc) const;

  protected:
    friend class ActionWeightingMap;
    void for_each_accion(CmdStatus &,const std::string &);
    virtual bool procesa_comando(CmdStatus &status);
  public:
    ActionContainer(const PsiCoeffsMap &coefs= PsiCoeffsMap());
    inline virtual ~ActionContainer(void) {}

    ActionRValue &inserta(const std::string &,const Action &,const std::string &nmb_coefs_psi="",const std::string &subfamilia= "");

    const ActionsFamily &getAccionesPermanentes(void) const;
    void setAccionesPermanentes(const ActionsFamily &);
    const ActionsFamiliesMap &getAccionesPermanentesNC(void) const;
    void setAccionesPermanentesNC(const ActionsFamiliesMap &);
    const ActionsFamily &getAccionesVariables(void) const;
    void setAccionesVariables(const ActionsFamily &);
    const ActionsFamily &getAccionesAccidentales(void) const;
    void setAccionesAccidentales(const ActionsFamily &);
    const ActionsFamily &getAccionesSismicas(void) const;
    void setAccionesSismicas(const ActionsFamily &);

    //Estados límite últimos.
    LoadCombinationVector GetPersistentesOTransit(void) const;
    LoadCombinationVector GetAccidentales(void) const;
    LoadCombinationVector GetSismicas(void) const;
    LoadCombinationVector GetCombELU(void) const;
    //Estados límite de servicio.
    LoadCombinationVector GetPocoFrecuentes(void) const;
    LoadCombinationVector GetFrecuentes(void) const;
    LoadCombinationVector GetCuasiPermanentes(void) const;
    LoadCombinationVector GetCombELS(void) const;

    const PsiCoeffsMap *getPtrPsiCoeffs(void) const
      { return &coefs_psi; }
    const PsiCoeffsMap &getPsiCoeffs(void) const
      { return coefs_psi; }
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };
} //fin namespace nmb_acc.

#endif

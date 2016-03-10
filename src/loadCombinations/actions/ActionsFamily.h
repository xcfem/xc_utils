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
//! @brief Familia de acciones (permanentes, variables, accidentales,...)
//!
//! Conjunto de acciones a las que se asignan unos mismos coeficientes de ponderación, p.ej. cada una de las siguientes:
//! -Acciones permanentes.
//! -Acciones variables.
//! -Acciones accidentales.
//! -Acciones sísmicas.
class ActionsFamily: public EntConNmb
  {
    GammaF gammaf; //!< Coeficientes de ponderación para toda la familia.
    ActionRValueList acciones; //!< Contenedor de acciones de la familia.

  protected:
    friend class ActionsFamiliesMap;
    friend class ActionContainer;
    void for_each_accion(CmdStatus &,const std::string &);
    virtual bool procesa_comando(CmdStatus &status);
  public:
    ActionsFamily(const std::string &nmb="",const GammaF &gf=GammaF());
    inline virtual ~ActionsFamily(void) {}
    ActionRValue &inserta(const Action &,const std::string &nmb_coefs_psi="");
    Variations CalculaVariations(const bool &elu= true,const bool &sit_accidental= false,const int &d=-1) const;
    //! @brief Devuelve el número de acciones de la familia.
    inline size_t getNumAcciones(void) const
      { return acciones.size(); }
    //! brief Devuelve verdadero si la familia esta vacía.
    inline bool Vacia(void) const
      { return acciones.empty(); }
    inline void setGammaF(const GammaF &gf)
      { gammaf= gf; }
    inline GammaF &getGammaF(void)
      { return gammaf; }
    const PsiCoeffsMap *getPtrPsiCoeffs(void) const;
    LoadCombinationVector GetLoadCombinations(const bool &elu,const bool &sit_accidental,short int r,const int &d=-1,const short int &rr=-1) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };
} //fin namespace nmb_acc.

#endif

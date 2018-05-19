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
//PartialSafetyFactors.cc
//Partial safety factors de acciones.

#include "PartialSafetyFactors.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variation.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variations.h"

#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"

cmb_acc::SLSPartialSafetyFactors::SLSPartialSafetyFactors(const float &fav,const float &desfav)
  : partial_safety_factors_fav(fav), partial_safety_factors_unfav(desfav) {}


//! @brief Return the partial safety factors for serviceability limit state.
cmb_acc::Variation cmb_acc::SLSPartialSafetyFactors::Coefs(void) const
  {
    if(partial_safety_factors_fav == partial_safety_factors_unfav) return Variation(1,partial_safety_factors_fav); //Si son iguales devuelve solo uno.
    Variation retval(2,0.0); //Partial safety factors.
    retval[0]= partial_safety_factors_fav; //Favorable.
    retval[1]= partial_safety_factors_unfav; //Desfavorable.
    return retval;
  }

void cmb_acc::SLSPartialSafetyFactors::Print(std::ostream &os) const
  { os << "favourable: " << partial_safety_factors_fav << ", unfavourable: " << partial_safety_factors_unfav; }

cmb_acc::ULSPartialSafetyFactors::ULSPartialSafetyFactors(const float &fav,const float &desfav,const float &fav_acc,const float &desfav_acc)
  : SLSPartialSafetyFactors(fav,desfav), partial_safety_factors_fav_acc(fav_acc), partial_safety_factors_unfav_acc(desfav_acc) {}

//! @brief Return the partial safety factors correspondientes 
//! a situaciones persistentes o transitorias.
cmb_acc::Variation cmb_acc::ULSPartialSafetyFactors::CoefsPT(void) const
  { return SLSPartialSafetyFactors::Coefs(); }

//! @brief Return the partial safety factors correspondientes 
//! a situaciones accidentales o sísmicas.
cmb_acc::Variation cmb_acc::ULSPartialSafetyFactors::CoefsAcc(void) const
  {
    if(partial_safety_factors_fav_acc == partial_safety_factors_unfav_acc) return Variation(1,partial_safety_factors_fav_acc); //Si son iguales devuelve solo uno.
    Variation retval(2,0.0); //Partial safety factors.
    retval[0]= partial_safety_factors_fav_acc; //Favorable.
    retval[1]= partial_safety_factors_unfav_acc; //Desfavorable.
    return retval;
  }

//! @brief Print stuff.
void cmb_acc::ULSPartialSafetyFactors::Print(std::ostream &os) const
  {
    SLSPartialSafetyFactors::Print(os);
    os << ", favourable (accidental): " << partial_safety_factors_fav_acc
       << ", unfavourable (accidental): " << partial_safety_factors_unfav_acc;
  }

//! @brief Constructor
cmb_acc::PartialSafetyFactors::PartialSafetyFactors(const ULSPartialSafetyFactors &gf_uls, const SLSPartialSafetyFactors &gf_els)
  : EntCmd(), uls_partial_safety_factors(gf_uls), sls_partial_safety_factors(gf_els) {}

//! @brief Return the partial safety factors for serviceability limit states.
cmb_acc::Variation cmb_acc::PartialSafetyFactors::CoefsEls(void) const
  { return sls_partial_safety_factors.Coefs(); }

//! \fn cmb_acc::PartialSafetyFactors::calcula_variations(const bool &uls,const bool &sit_accidental) const
//! @brief Calcula las variations que pueden formarse con las acciones de la familia.
//!
//! @param n: Número de acciones de la familia.
//! @param uls: Verdadero si se trata de un ultimate limit state.
//! @param sit_accidental: Verdadero si se trata de una situación accidental o sísmica.
//! @param d: Índice de la acción dominante (-1 si ninguna es dominante).
cmb_acc::Variations cmb_acc::PartialSafetyFactors::calcula_variations(const bool &uls,const bool &sit_accidental,const int &d,const ActionRValueList &lvr) const
  {
    const size_t n= lvr.size();
    Variations retval;
    if(n<1) return retval;
    if(uls)
      if(sit_accidental)
        retval= Variations::Calcula(uls_partial_safety_factors.CoefsAcc(),d,lvr);
      else
        retval= Variations::Calcula(uls_partial_safety_factors.CoefsPT(),d,lvr);
    else
      retval= Variations::Calcula(sls_partial_safety_factors.Coefs(),d,lvr);
    return retval;
  }

//! @brief Print stuff.
void cmb_acc::PartialSafetyFactors::Print(std::ostream &os) const
  {
    os << " SLS: " << sls_partial_safety_factors
       << " ULS: " << uls_partial_safety_factors;
  }

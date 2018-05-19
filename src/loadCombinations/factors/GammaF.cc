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
//GammaF.cc
//Partial safety factors de acciones.

#include "GammaF.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variation.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variations.h"

#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"

cmb_acc::GammaFSLS::GammaFSLS(const float &fav,const float &desfav)
  : gamma_f_fav(fav), gamma_f_desfav(desfav) {}


//! @brief Return the partial safety factors for serviceability limit state.
cmb_acc::Variation cmb_acc::GammaFSLS::Coefs(void) const
  {
    if(gamma_f_fav == gamma_f_desfav) return Variation(1,gamma_f_fav); //Si son iguales devuelve solo uno.
    Variation retval(2,0.0); //Partial safety factors.
    retval[0]= gamma_f_fav; //Favorable.
    retval[1]= gamma_f_desfav; //Desfavorable.
    return retval;
  }

void cmb_acc::GammaFSLS::Print(std::ostream &os) const
  { os << "favourable: " << gamma_f_fav << ", unfavourable: " << gamma_f_desfav; }

cmb_acc::GammaFULS::GammaFULS(const float &fav,const float &desfav,const float &fav_acc,const float &desfav_acc)
  : GammaFSLS(fav,desfav), gamma_f_fav_acc(fav_acc), gamma_f_desfav_acc(desfav_acc) {}

//! @brief Return the partial safety factors correspondientes 
//! a situaciones persistentes o transitorias.
cmb_acc::Variation cmb_acc::GammaFULS::CoefsPT(void) const
  { return GammaFSLS::Coefs(); }

//! @brief Return the partial safety factors correspondientes 
//! a situaciones accidentales o sísmicas.
cmb_acc::Variation cmb_acc::GammaFULS::CoefsAcc(void) const
  {
    if(gamma_f_fav_acc == gamma_f_desfav_acc) return Variation(1,gamma_f_fav_acc); //Si son iguales devuelve solo uno.
    Variation retval(2,0.0); //Partial safety factors.
    retval[0]= gamma_f_fav_acc; //Favorable.
    retval[1]= gamma_f_desfav_acc; //Desfavorable.
    return retval;
  }

//! @brief Print stuff.
void cmb_acc::GammaFULS::Print(std::ostream &os) const
  {
    GammaFSLS::Print(os);
    os << ", favourable (accidental): " << gamma_f_fav_acc
       << ", unfavourable (accidental): " << gamma_f_desfav_acc;
  }

//! @brief Constructor
cmb_acc::GammaF::GammaF(const GammaFULS &gf_uls, const GammaFSLS &gf_els)
  : EntCmd(), gammaf_uls(gf_uls), gammaf_els(gf_els) {}

//! @brief Return the partial safety factors for serviceability limit states.
cmb_acc::Variation cmb_acc::GammaF::CoefsEls(void) const
  { return gammaf_els.Coefs(); }

//! \fn cmb_acc::GammaF::calcula_variations(const bool &uls,const bool &sit_accidental) const
//! @brief Calcula las variations que pueden formarse con las acciones de la familia.
//!
//! @param n: Número de acciones de la familia.
//! @param uls: Verdadero si se trata de un ultimate limit state.
//! @param sit_accidental: Verdadero si se trata de una situación accidental o sísmica.
//! @param d: Índice de la acción dominante (-1 si ninguna es dominante).
cmb_acc::Variations cmb_acc::GammaF::calcula_variations(const bool &uls,const bool &sit_accidental,const int &d,const ActionRValueList &lvr) const
  {
    const size_t n= lvr.size();
    Variations retval;
    if(n<1) return retval;
    if(uls)
      if(sit_accidental)
        retval= Variations::Calcula(gammaf_uls.CoefsAcc(),d,lvr);
      else
        retval= Variations::Calcula(gammaf_uls.CoefsPT(),d,lvr);
    else
      retval= Variations::Calcula(gammaf_els.Coefs(),d,lvr);
    return retval;
  }

//! @brief Print stuff.
void cmb_acc::GammaF::Print(std::ostream &os) const
  {
    os << " SLS: " << gammaf_els
       << " ULS: " << gammaf_uls;
  }

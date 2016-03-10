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
//Coeficientes de ponderación de acciones.

#include "GammaF.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variation.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variations.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"

cmb_acc::GammaFELS::GammaFELS(const float &fav,const float &desfav)
  : gamma_f_fav(fav), gamma_f_desfav(desfav) {}


bool cmb_acc::GammaFELS::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(GammaFELS) Procesando comando: " << cmd << std::endl;
    if(cmd == "favorable")
      {
        gamma_f_fav= interpretaDouble(status.GetString());
        return true;
      }
    else if(cmd == "desfavorable")
      {
        gamma_f_desfav= interpretaDouble(status.GetString());
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Devuelve los coeficientes de ponderación correspondientes a situaciones de servicio.
cmb_acc::Variation cmb_acc::GammaFELS::Coefs(void) const
  {
    if(gamma_f_fav == gamma_f_desfav) return Variation(1,gamma_f_fav); //Si son iguales devuelve solo uno.
    Variation retval(2,0.0); //Coeficientes de ponderación.
    retval[0]= gamma_f_fav; //Favorable.
    retval[1]= gamma_f_desfav; //Desfavorable.
    return retval;
  }

//! \fn any_const_ptr cmb_acc::GammaFELS::GetProp(const std::string &cod) const
//! @brief Devuelve la propiedad del objeto cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::GammaFELS::GetProp(const std::string &cod) const
  {
    if(cod == "favorable")
      return any_const_ptr(gamma_f_fav);
    else if(cod == "desfavorable")
      return any_const_ptr(gamma_f_desfav);
    else
      return EntCmd::GetProp(cod);
  }

cmb_acc::GammaFELU::GammaFELU(const float &fav,const float &desfav,const float &fav_acc,const float &desfav_acc)
  : GammaFELS(fav,desfav), gamma_f_fav_acc(fav_acc), gamma_f_desfav_acc(desfav_acc) {}

bool cmb_acc::GammaFELU::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(GammaFELU) Procesando comando: " << cmd << std::endl;
    if(cmd == "favorable_accidental")
      {
        gamma_f_fav_acc= status.GetFloat();
        return true;
      }
    else if(cmd == "desfavorable_accidental")
      {
        gamma_f_desfav_acc= status.GetFloat();
        return true;
      }
    else
      return GammaFELS::procesa_comando(status);
  }

//! @brief Devuelve los coeficientes de ponderación correspondientes 
//! a situaciones persistentes o transitorias.
cmb_acc::Variation cmb_acc::GammaFELU::CoefsPT(void) const
  { return GammaFELS::Coefs(); }

//! @brief Devuelve los coeficientes de ponderación correspondientes 
//! a situaciones accidentales o sísmicas.
cmb_acc::Variation cmb_acc::GammaFELU::CoefsAcc(void) const
  {
    if(gamma_f_fav_acc == gamma_f_desfav_acc) return Variation(1,gamma_f_fav_acc); //Si son iguales devuelve solo uno.
    Variation retval(2,0.0); //Coeficientes de ponderación.
    retval[0]= gamma_f_fav_acc; //Favorable.
    retval[1]= gamma_f_desfav_acc; //Desfavorable.
    return retval;
  }

//! \fn any_const_ptr cmb_acc::GammaFELU::GetProp(const std::string &cod) const
//! @brief Devuelve la propiedad del objeto cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::GammaFELU::GetProp(const std::string &cod) const
  {
    if(cod == "favorable_accidental")
      return any_const_ptr(gamma_f_fav_acc);
    else if(cod == "desfavorable_accidental")
      return any_const_ptr(gamma_f_desfav_acc);
    else
      return GammaFELS::GetProp(cod);
  }

//! @brief Constructor
cmb_acc::GammaF::GammaF(const GammaFELU &gf_elu, const GammaFELS &gf_els)
  : EntCmd(), gammaf_elu(gf_elu), gammaf_els(gf_els) {}

//! @brief Lectura desde archivo.
bool cmb_acc::GammaF::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(GammaF) Procesando comando: " << cmd << std::endl;
    if(cmd == "gammaf_elu") //Lee coeficientes de ponderación de acciones en ELU.
      {
        gammaf_elu.LeeCmd(status);
        return true;
      }
    else if(cmd == "gammaf_els") //Lee coeficientes de ponderación de acciones en ELS.
      {
        gammaf_els.LeeCmd(status);
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Devuelve los coeficientes de ponderación correspondientes 
//! a estados límite de servicio.
cmb_acc::Variation cmb_acc::GammaF::CoefsEls(void) const
  { return gammaf_els.Coefs(); }

//! \fn cmb_acc::GammaF::calcula_variations(const bool &elu,const bool &sit_accidental) const
//! @brief Calcula las variations que pueden formarse con las acciones de la familia.
//!
//! @param n: Número de acciones de la familia.
//! @param elu: Verdadero si se trata de un estado límite último.
//! @param sit_accidental: Verdadero si se trata de una situación accidental o sísmica.
//! @param d: Índice de la acción dominante (-1 si ninguna es dominante).
cmb_acc::Variations cmb_acc::GammaF::calcula_variations(const bool &elu,const bool &sit_accidental,const int &d,const ActionRValueList &lvr) const
  {
    const size_t n= lvr.size();
    Variations retval;
    if(n<1) return retval;
    if(elu)
      if(sit_accidental)
        retval= Variations::Calcula(gammaf_elu.CoefsAcc(),d,lvr);
      else
        retval= Variations::Calcula(gammaf_elu.CoefsPT(),d,lvr);
    else
      retval= Variations::Calcula(gammaf_els.Coefs(),d,lvr);
    return retval;
  }

//! \fn any_const_ptr cmb_acc::GammaF::GetProp(const std::string &cod) const
//! @brief Devuelve la propiedad del objeto cuyo código se pasa como parámetro.
any_const_ptr cmb_acc::GammaF::GetProp(const std::string &cod) const
  {
    if(cod == "gammaf_elu")
      return any_const_ptr(&gammaf_elu);
    else if(cod == "gammaf_els")
      return any_const_ptr(&gammaf_els);
    else
      return EntCmd::GetProp(cod);
  }

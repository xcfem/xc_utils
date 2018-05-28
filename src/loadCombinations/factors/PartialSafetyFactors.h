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
//PartialSafetyFactors.h
//Partial safety factors for actions.


#ifndef PARTIALSAFETYFACTORS_HXX
#define PARTIALSAFETYFACTORS_HXX

#include "xc_utils/src/nucleo/EntCmd.h"


namespace cmb_acc{
class Variation;
class Variations;
class ActionRValueList;

//! @ingroup CMBACC
//
//! @brief Serviceability limit states partial safety factors.
class SLSPartialSafetyFactors: public EntCmd
  {
  protected:
    //Partial safety factors
    float partial_safety_factors_fav; //!< favourable effect.
    float partial_safety_factors_unfav; //!< unfavourable effect.

    //! @brief Lee el objeto desde archivo.

    friend class PartialSafetyFactors;
    Variation Coefs(void) const;
  public:
    //! @brief Constructor por defecto. Supone control normal.
    SLSPartialSafetyFactors(const float &fav=0.0,const float &desfav=1.0);
    inline float getFavorable(void) const
      { return partial_safety_factors_fav; }
    inline void setFavorable(const float &f)
      { partial_safety_factors_fav= f; }
    inline float getDesfavorable(void) const
      { return partial_safety_factors_unfav; }
    inline void setDesfavorable(const float &f)
      { partial_safety_factors_unfav= f; }
    virtual void Print(std::ostream &os) const;
  };
 
inline std::ostream &operator<<(std::ostream &os, const SLSPartialSafetyFactors &g)
  {
    g.Print(os);
    return os;
  }
 
//! @brief Partial safety factors de una familia de acciones (permanentes, variables,...), en estados límite últimos .
class ULSPartialSafetyFactors: public SLSPartialSafetyFactors
  {
    //Partial safety factors
    float partial_safety_factors_fav_acc; //!< para favourable effect en situacion accidental o sísmica.
    float partial_safety_factors_unfav_acc; //!< para unfavourable effect en situacion accidental o sísmica.
  protected:
    //! @brief Lee el objeto desde archivo.

    friend class PartialSafetyFactors;
    //! @brief Return the partial safety factors correspondientes a situación persistente o transitoria.
    Variation CoefsPT(void) const;
    //! @brief Return the partial safety factors correspondientes a situación accidental o sísmica.
    Variation CoefsAcc(void) const;
  public:
    //! @brief Constructor por defecto. Supone control normal.
    ULSPartialSafetyFactors(const float &fav=0.0,const float &desfav=1.8,const float &fav_acc=0.0,const float &desfav_acc=1.0);
    inline float getFavorableAccidental(void) const
      { return partial_safety_factors_fav_acc; }
    inline void setFavorableAccidental(const float &f)
      { partial_safety_factors_fav_acc= f; }
    inline float getDesfavorableAccidental(void) const
      { return partial_safety_factors_unfav_acc; }
    inline void setDesfavorableAccidental(const float &f)
      { partial_safety_factors_unfav_acc= f; }
    virtual void Print(std::ostream &os) const;
  };

//! @brief Partial safety factors de una familia de acciones en SLS y ULS.
class PartialSafetyFactors: public EntCmd
  {
    ULSPartialSafetyFactors uls_partial_safety_factors; //!< Partial safety factors en estados límite últimos.
    SLSPartialSafetyFactors sls_partial_safety_factors; //!< Partial safety factors en serviceability limit states.
  protected:
    Variation CoefsEls(void) const;
  public:
    PartialSafetyFactors(const ULSPartialSafetyFactors &gf_uls=ULSPartialSafetyFactors(), const SLSPartialSafetyFactors &gf_els=SLSPartialSafetyFactors());

    //! @brief Return the partial safety factors for ultimate limit states.
    inline const ULSPartialSafetyFactors &getULSPartialSafetyFactors(void) const
      { return uls_partial_safety_factors; }
    //! @brief Return the partial safety factors for serviceability limit states.
    inline const SLSPartialSafetyFactors &getSLSPartialSafetyFactors(void) const
      { return sls_partial_safety_factors; }
    Variation getVariation(const bool &uls,const bool &sit_accidental) const;
    virtual void Print(std::ostream &os) const;
  };

inline std::ostream &operator<<(std::ostream &os, const PartialSafetyFactors &g)
  {
    g.Print(os);
    return os;
  }

} //fin namespace nmb_acc.

#endif

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
//GammaF.h
//Partial safety factors de acciones.


#ifndef GAMMAF_HXX
#define GAMMAF_HXX

#include "xc_utils/src/nucleo/EntCmd.h"


namespace cmb_acc{
class Variation;
class Variations;
class ActionRValueList;

//! @ingroup CMBACC
//
//! @brief Partial safety factors de una familia de acciones (permanentes, variables,...), en serviceability limit states.
class GammaFELS: public EntCmd
  {
  protected:
    //Partial safety factors
    float gamma_f_fav; //!< para favourable effect.
    float gamma_f_desfav; //!< para unfavourable effect.

    //! @brief Lee el objeto desde archivo.

    friend class GammaF;
    Variation Coefs(void) const;
  public:
    //! @brief Constructor por defecto. Supone control normal.
    GammaFELS(const float &fav=0.0,const float &desfav=1.0);
    inline float getFavorable(void) const
      { return gamma_f_fav; }
    inline void setFavorable(const float &f)
      { gamma_f_fav= f; }
    inline float getDesfavorable(void) const
      { return gamma_f_desfav; }
    inline void setDesfavorable(const float &f)
      { gamma_f_desfav= f; }
    virtual void Print(std::ostream &os) const;
  };
 
inline std::ostream &operator<<(std::ostream &os, const GammaFELS &g)
  {
    g.Print(os);
    return os;
  }
 
//! @brief Partial safety factors de una familia de acciones (permanentes, variables,...), en estados límite últimos .
class GammaFELU: public GammaFELS
  {
    //Partial safety factors
    float gamma_f_fav_acc; //!< para favourable effect en situacion accidental o sísmica.
    float gamma_f_desfav_acc; //!< para unfavourable effect en situacion accidental o sísmica.
  protected:
    //! @brief Lee el objeto desde archivo.

    friend class GammaF;
    //! @brief Return the partial safety factors correspondientes a situación persistente o transitoria.
    Variation CoefsPT(void) const;
    //! @brief Return the partial safety factors correspondientes a situación accidental o sísmica.
    Variation CoefsAcc(void) const;
  public:
    //! @brief Constructor por defecto. Supone control normal.
    GammaFELU(const float &fav=0.0,const float &desfav=1.8,const float &fav_acc=0.0,const float &desfav_acc=1.0);
    inline float getFavorableAccidental(void) const
      { return gamma_f_fav_acc; }
    inline void setFavorableAccidental(const float &f)
      { gamma_f_fav_acc= f; }
    inline float getDesfavorableAccidental(void) const
      { return gamma_f_desfav_acc; }
    inline void setDesfavorableAccidental(const float &f)
      { gamma_f_desfav_acc= f; }
    virtual void Print(std::ostream &os) const;
  };

//! @brief Partial safety factors de una familia de acciones en ELS y ELU.
class GammaF: public EntCmd
  {
    GammaFELU gammaf_elu; //!< Partial safety factors en estados límite últimos.
    GammaFELS gammaf_els; //!< Partial safety factors en serviceability limit states.
  protected:
    Variation CoefsEls(void) const;
  public:
    GammaF(const GammaFELU &gf_elu=GammaFELU(), const GammaFELS &gf_els=GammaFELS());

    inline const GammaFELU &getGammaFELU(void) const
      { return gammaf_elu; }
    inline const GammaFELS &getGammaFELS(void) const
      { return gammaf_els; }
    //! @brief Return the partial safety factors correspondientes a estado límite de servicio.
    Variations calcula_variations(const bool &elu,const bool &sit_accidental,const int &d,const ActionRValueList &) const;
    virtual void Print(std::ostream &os) const;
  };

inline std::ostream &operator<<(std::ostream &os, const GammaF &g)
  {
    g.Print(os);
    return os;
  }

} //fin namespace nmb_acc.

#endif

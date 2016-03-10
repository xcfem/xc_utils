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
//Coeficientes de ponderación de acciones.


#ifndef GAMMAF_HXX
#define GAMMAF_HXX

#include "xc_utils/src/nucleo/EntCmd.h"


namespace cmb_acc{
class Variation;
class Variations;
class ListaVRAccion;

//! @ingroup CMBACC
//
//! @brief Coeficientes de mayoración de una familia de acciones (permanentes, variables,...), en estados límite de servicio.
class GammaFELS: public EntCmd
  {
  protected:
    //Coeficientes de ponderación
    float gamma_f_fav; //!< para efecto favorable.
    float gamma_f_desfav; //!< para efecto desfavorable.

    //! @brief Lee el objeto desde archivo.
    virtual bool procesa_comando(CmdStatus &status);
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
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

//! @brief Coeficientes de mayoración de una familia de acciones (permanentes, variables,...), en estados límite últimos .
class GammaFELU: public GammaFELS
  {
    //Coeficientes de ponderación
    float gamma_f_fav_acc; //!< para efecto favorable en situacion accidental o sísmica.
    float gamma_f_desfav_acc; //!< para efecto desfavorable en situacion accidental o sísmica.
  protected:
    //! @brief Lee el objeto desde archivo.
    virtual bool procesa_comando(CmdStatus &status);
    friend class GammaF;
    //! @brief Devuelve los coeficientes de ponderación correspondientes a situación persistente o transitoria.
    Variation CoefsPT(void) const;
    //! @brief Devuelve los coeficientes de ponderación correspondientes a situación accidental o sísmica.
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
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

//! @brief Coeficientes de ponderación de una familia de acciones en ELS y ELU.
class GammaF: public EntCmd
  {
    GammaFELU gammaf_elu; //!< Coeficientes de ponderación en estados límite últimos.
    GammaFELS gammaf_els; //!< Coeficientes de ponderación en estados límite de servicio.
  protected:
    virtual bool procesa_comando(CmdStatus &status);
    Variation CoefsEls(void) const;
  public:
    GammaF(const GammaFELU &gf_elu=GammaFELU(), const GammaFELS &gf_els=GammaFELS());

    inline const GammaFELU &getGammaFELU(void) const
      { return gammaf_elu; }
    inline const GammaFELS &getGammaFELS(void) const
      { return gammaf_els; }
    //! @brief Devuelve los coeficientes de ponderación correspondientes a estado límite de servicio.
    Variations calcula_variations(const bool &elu,const bool &sit_accidental,const int &d,const ListaVRAccion &) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

} //fin namespace nmb_acc.

#endif

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
//VRAccion.hxx
//Valores representativos de una acción.

#ifndef VRACCION_H
#define VRACCION_H

#include "Accion.h"

namespace cmb_acc{

class GammaF;
class CoefsPsi;

//! @ingroup CMBACC
//
//! @brief Valores representativos de una acción.
class VRAccion: public Accion
  {
  private:
    ListaVRAccion *acc_familia; //!< Contenedor de la familia de acciones de la que ésta forma parte.
    const CoefsPsi *coefs_psi; //!< Coeficientes de simultaneidad para valor de combinación.

    //! @brief Devuelve el coeficiente de combinación cuyo índice se pasa como parámetro.
    inline double getPsi(short int r) const;

  protected:
    virtual bool procesa_comando(CmdStatus &status);

    friend class ListaVRAccion;
    //! @brief Constructor por defecto.
    VRAccion(const std::string &n="", const std::string &descrip="",ListaVRAccion *fam= NULL);
    VRAccion(const Accion &a,ListaVRAccion *fam= NULL,const std::string &nmb_coefs= "");
  public:
    Accion Valor(short int r) const;
    void setCoefsPsi(const std::string &);
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

} //fin namespace nmb_acc.

#endif

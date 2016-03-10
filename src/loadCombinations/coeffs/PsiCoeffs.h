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
//PsiCoeffs.hxx
//Valores representativos de una acción.

#ifndef PSICOEFFS_H
#define PSICOEFFS_H

#include "xc_utils/src/nucleo/EntCmd.h"

namespace cmb_acc{

//! @ingroup CMBACC
//
//! @brief Coeficientes de simultaneidad de una acción.
class PsiCoeffs: public EntCmd
  {
  private:
    double psi_0; //!< Coeficiente de simultaneidad para obtener el valor de combinación.
    double psi_1; //!< Coeficiente de simultaneidad para obtener el valor frecuente.
    double psi_2; //!< Coeficiente de sumultaneidad para obtener el valor cuasipermanente.

  protected:
    virtual bool procesa_comando(CmdStatus &status);

  public:
    //! @brief Constructor por defecto.
    PsiCoeffs(const double &p0= 1.0, const double &p1= 1.0, const double &p2= 1.0)
      : EntCmd(),psi_0(p0), psi_1(p1), psi_2(p2) {}
    //! @brief Constructor de copia.
    const double &getPsi(short int r) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

} //fin namespace nmb_acc.

#endif

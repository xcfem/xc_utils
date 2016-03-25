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
//ActionRValue.cxx

#include "xc_utils/src/loadCombinations/actions/ActionRValue.h"
#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"
#include "xc_utils/src/loadCombinations/coeffs/GammaF.h"
#include "xc_utils/src/loadCombinations/coeffs/PsiCoeffsMap.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

//! @brief Constructor por defecto.
cmb_acc::ActionRValue::ActionRValue(const std::string &n, const std::string &descrip,ActionRValueList *fam)
  : Action(n,descrip), acc_familia(fam), coefs_psi(&PsiCoeffsMap::getCoefsPorDefecto()) {}

//! @brief Constructor por defecto.
cmb_acc::ActionRValue::ActionRValue(const Action &a,ActionRValueList *fam,const std::string &nmb_coefs)
  : Action(a), acc_familia(fam), coefs_psi(&PsiCoeffsMap::getCoefsPorDefecto()) 
  {
    setPsiCoeffs(nmb_coefs);
  }

//! @brief Asigna los coeficientes de simultaneidad de la acción.
void cmb_acc::ActionRValue::setPsiCoeffs(const std::string &nmb_coefs)
  {
    if(!nmb_coefs.empty())
      {
        const PsiCoeffs *tmp=NULL;
        if(acc_familia)
          tmp= acc_familia->getPtrPsiCoeffs()->getPtrCoefs(nmb_coefs);
        else
          std::cerr << "ActionRValue::setPsiCoeffs; el puntero a la familia de acciones no está asignado." << std::endl;
        if(tmp)
           coefs_psi= tmp;
      }
  }

double cmb_acc::ActionRValue::getPsi(short int r) const
  { return coefs_psi->getPsi(r); }

//! \fn cmb_acc::Action cmb_acc::ActionRValue::Valor(short int r) const
//! @brief Devuelve el valor representativo de la acción.
cmb_acc::Action cmb_acc::ActionRValue::Valor(short int r) const
  {
    Action retval(*this);
    switch(r)
      {
      case(-1):
        break; //Valor característico.
      case(0):
        retval*=getPsi(0); //Valor de combinación.
        break;
      case(1):
        retval*=getPsi(1); //Valor frecuente.
        break;
      case(2):
        retval*=getPsi(2); //Valor cuasipermanente.
        break;
      default:
        break;
      }
    return retval;
  }

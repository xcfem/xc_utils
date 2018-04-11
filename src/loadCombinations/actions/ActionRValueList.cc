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
//ActionRValueList.cxx

#include "xc_utils/src/loadCombinations/actions/ActionRValueList.h"
#include "xc_utils/src/loadCombinations/actions/ActionsFamily.h"
#include "xc_utils/src/loadCombinations/comb_analysis/Variation.h"

cmb_acc::ActionRValue &cmb_acc::ActionRValueList::push_back(const ActionRValue &a)
  {
    std::deque<ActionRValue>::push_back(a);
    ActionRValue &retval= back();
    return retval;
  }

//! @brief Insert the action being passed as parameter.
cmb_acc::ActionRValue &cmb_acc::ActionRValueList::insert(const Action &a,const std::string &nmb_coefs_psi)
  {
    ActionRValue acc(a,this,nmb_coefs_psi);
    acc.set_owner(this);
    return push_back(acc);
  }

//! \fn cmb_acc::ActionRValueList::FormaProdEscalar(const Variation &v,short int r,const int &d,const short int &rr) const
//! @brief Forma producto escalar.
//!
//! @param v: Variation a sumar.
//! @param r: Valor representativo para el caso general (r= -1 -> characteristic value,r= 0 -> valor de combinación
//! r= 1 -> valor frecuente, r= 2 -> valor cuasipermanente).
//! @param d: Índice de la acción determinante (si no hay acción determinante d=-1).
//! @param rr: Valor representativo a emplear para la acción determinante.
cmb_acc::Action cmb_acc::ActionRValueList::FormaProdEscalar(const Variation &var,short int r,const int &d,const short int &rr) const
  {
    const size_t num_acciones= size();
    Action retval=Action::NULA(); //Inicializar a cero.
    for(size_t j=0;j<num_acciones;j++)
      {
        Action tmp= GetValor(j,r);
        if(d>-1) //Existe acción determinante
          if(j==size_t(d)) //Corresponde con el índice j.
            {
              tmp= GetValor(j,rr); //Acción determinante.
            }
        retval+=var[j]*tmp;
      }
    return retval;
  }

//! @brief Devuelve un puntero a la tabla de coeficientes de simultaneidad.
const cmb_acc::PsiCoeffsMap *cmb_acc::ActionRValueList::getPtrPsiCoeffs(void) const
  {
    const ActionsFamily *tmp= dynamic_cast<const ActionsFamily *>(Owner());
    if(tmp)
      return tmp->getPtrPsiCoeffs();
    else
      {
	std::cerr << "ActionRValueList::getPtrPsiCoeffs; no se encontró el objeto propietario de éste." << std::endl;
        return nullptr;
      }
  }

void cmb_acc::ActionRValueList::Print(std::ostream &os) const
  {
    for(const_iterator i=begin();i!=end();i++)
      os << *i << ' ';
  }

//! @brief Operador salida.
std::ostream &cmb_acc::operator<<(std::ostream &os,const ActionRValueList &lvr)
  {
    lvr.Print(os);
    return os;
  }

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
//LeadingActionInfo.cxx

#include "LeadingActionInfo.h"
#include "Action.h"

cmb_acc::LeadingActionInfo::LeadingActionInfo(const short int &i, const short int &lrv, const short int &grv)
  : CommandEntity(),index(i), leading_representative_value_index(lrv),
    general_representative_value_index(grv) {}

//! @brief Print stuff.
void cmb_acc::LeadingActionInfo::Print(std::ostream &os) const
  {
    os << "leading action index= " << index
       << ", leading action representative value index= "
       <<  leading_representative_value_index
       << ", general action representative value index= "
       << general_representative_value_index;
  }

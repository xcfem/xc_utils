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
//CombinationFactors.cxx

#include "CombinationFactors.h"

//! @brief Return the r-th combination factor.
const float &cmb_acc::CombinationFactors::getCombinationFactor(short int r) const
  {
    switch(r)
      {
      case(0):
        return psi_0;
      case(1):
        return psi_1;
      case(2):
        return psi_2;
      default:
	std::cerr << getClassName() << "::" << __FUNCTION__
	          << " índex: " << r
		  << " out of range (0..2)." << std::endl;
        return psi_0;
      }
  }

//! @brief Print stuff.
void cmb_acc::CombinationFactors::Print(std::ostream &os) const
  {
    os << "psi_0= " << psi_0
       << ", psi_1= " <<  psi_1
       << ", psi_2= " << psi_2;
  }

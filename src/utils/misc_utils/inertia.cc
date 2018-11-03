//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//inertia.cc

#include "inertia.h"
#include <iostream>

//! @brief Return the angle that defines a principal axes of inertia.
double theta_inertia(const double &Ix,const double &Iy,const double &Pxy)
  {
    const double tol= std::numeric_limits<double>::epsilon();
    const double eps= abs(Ix-Iy)/std::max(Ix,Iy);
    if(eps<tol)
      if(abs(Pxy)<tol)
	return 0.0;
      else
        if(Pxy<0)
	  return M_PI/4.0;
        else
	  return -M_PI/4.0;
    else
      return (atan(-2*Pxy/(Ix-Iy)))/2.0;
  }

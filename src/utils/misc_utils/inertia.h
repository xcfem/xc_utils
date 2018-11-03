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
//inertia.h

#ifndef INERTIA_H
#define INERTIA_H

#include <cmath>
#include "matem.h"

double theta_inertia(const double &Ix,const double &Iy,const double &Pxy);

//! @brief Auxiliary function to compute principal moments of inertia.
inline double R_inertia(const double &Ix,const double &Iy,const double Pxy)
  { return sqrt(sqr((Ix-Iy)/2)+sqr(Pxy)); }

//! @brief Return the principal major moment of inertia.
inline double I1_inertia(const double &iy,const double &iz,const double &pyz)
  { return (iy+iz)/2+R_inertia(iy,iz,pyz); }

//! @brief Return the principal minor moment of inertia.
inline double I2_inertia(const double &iy,const double &iz,const double &pyz)
  { return (iy+iz)/2-R_inertia(iy,iz,pyz); }


#endif

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
//gj_aux.h
//Auxiliary functions for the Gauss and Jordan methods
//for solving linear systems of equations.

#ifndef GJ_AUX_H
#define GJ_AUX_H

#include "math.h"
const double zero = 1e-7;

//The following functions must be defined for any object intended to be
//used with the routines from gauss.h and jordan.h

inline double gj_abs(const double &r)
  { return fabs(r); }
inline double gj_inv(const double &r)
  { return 1/r; }

#endif

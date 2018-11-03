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
//mchne_eps.h
//Epsilon de la máquina

#ifndef MCHNE_EPS_H
#define MCHNE_EPS_H

#include "matem.h"
#include <limits>

#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif

static const double VARIABLE_IS_NOT_USED mchne_eps_flt= std::numeric_limits<float>::epsilon(); //machine_epsilon((const float &) 0.0);
static const double VARIABLE_IS_NOT_USED mchne_eps_dbl= std::numeric_limits<double>::epsilon(); //machine_epsilon((const double &) 0.0);
static const double VARIABLE_IS_NOT_USED mchne_eps_ldbl= std::numeric_limits<long double>::epsilon(); //machine_epsilon((const long double &) 0.0);

static const double VARIABLE_IS_NOT_USED sqrt_mchne_eps_flt= sqrt(mchne_eps_flt);
static const double VARIABLE_IS_NOT_USED sqrt_mchne_eps_dbl= sqrt(mchne_eps_dbl);
static const double VARIABLE_IS_NOT_USED sqrt_mchne_eps_ldbl= sqrt(mchne_eps_ldbl);

#endif

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
#ifndef	GSSLEG_H
#define	GSSLEG_H

#include <cmath>
#include <cstdio>
#include <vector>

typedef std::vector<double> v_double;

/* I originally used the Gauss-Legendre routine 'gauleg' from
   Numerical Recipes in C.  Since that is copyrighted, I decided
   to write my own.  In doing so I think I found a couple errors
   in the Gauss-Legendre recurrence relation in NRiC (in the
   theory section, not in the code itself). */

void gss_leg(double x1, double x2,v_double &x,v_double &w);

#endif

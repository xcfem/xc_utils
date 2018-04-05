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
//gssleg.cc

#include "gssleg.h"
#include <iostream>

#define	TOLERANCE	3.0e-11 /* value used in NRiC */

void gss_leg(double x1, double x2,v_double &x,v_double &w)
  {
    size_t n= x.size();
    if(n!=w.size())
      {
        std::cerr << "Error en gss_leg" << std::endl;
        return;
      }
    double xavg = (x2+x1)/2.0, dx = (x2-x1);
    double zi, oldzi;
    size_t n2 = (n+1)/2;
    double p[3], dp;

    // loop over lower half the points
    for(size_t i=1;i<=n2;i++)
      {
        //initial guess at root
        zi = cos(M_PI*(i-.25)/(n+.5));
        do
          {
            // Calculate value of nth polynomial.  This will be used
            // to calculate the derivative of the polynomial later on.
            // the derivative in turn is used to improve the guess of the
            // root
            p[1] = 0.0;
            p[2] = 1.0;
            for(size_t j=1;j<=n;j++)
              {			
                p[0] = p[1];
                p[1] = p[2];
                p[2] = ((2*j-1)*zi*p[1]-(j-1.0)*p[0])/j;
              }

            // Newton-Raphson refinement - Continue until the
            // iteration doesn't improve much
            oldzi = zi;
            dp = n*(zi*p[2]-p[1])/(zi*zi-1.0);
            zi = oldzi - p[2]/dp;
          }
        while(fabs(zi-oldzi) > TOLERANCE);
		
        // Refinement succeeded, now transform from (-1,1) to (x1,x2)
        x[i-1] = xavg-(dx/2.0)*zi;
        w[i-1] = dx/((1.0-zi*zi)*dp*dp);
        //Mirror image values
        x[n-i] = xavg+(dx/2.0)*zi;
        w[n-i] = w[i-1];
      }
  }

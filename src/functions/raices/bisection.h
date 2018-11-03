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
//bisection.h

#ifndef BISECTION_H
#define BISECTION_H

#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/utils/misc_utils/mchne_eps.h"

template<class F>
inline bool Bisection(double low, double high, double tolerance,double &root,const double *params, F f)
  {
    if (f(low, params) * f(high, params) > 0) return false;

    while (fabs(high - low) > tolerance)
      {
        root = (low + high) / 2; //Actualizamos la aproximación
        if (f(root, params) * f(high, params) > 0)
          high = root;
        else
          low = root;
      }
    return true;
  }

class SolverBiseccion
  {
    double low;
    double high;
    double tolerance;
    bool error;

    template<class F>
    double Biseccion(const double &raiz,const double *params, F f)
      {
        double root= raiz;
        error= Bisection(low,high,tolerance,root,params,f);
        return root;
      }

  public:
    SolverBiseccion(const double &min,const double &max,const double &tol= sqrt_mchne_eps_dbl)
      : low(min), high(max), tolerance(tol), error(false) {}
    inline const bool &GetError(void) const
      { return error; }
    void Reset(const double &min,const double &max,const double &tol= sqrt_mchne_eps_dbl)
      {
        low=min;
        high= max;
        tolerance= tol;
        error= false;
      }
    template<class F>
    inline double Solve(const double &raiz,const double *params, F f)
      {
        const double low_bak= low;
        const double high_bak= high;
        const double tolerance_bak= tolerance;
        const double retval=Biseccion(raiz,params,f);
        Reset(low_bak,high_bak,tolerance_bak);
        return retval;
      }
  };

#endif

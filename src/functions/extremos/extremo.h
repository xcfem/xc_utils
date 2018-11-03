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
//Extremo.h
//Cálculo del extremo de una función unimodal
//en el intervalo (a,b) mediante el método
//de la razón aurea.

#ifndef EXTREMO_H
#define EXTREMO_H

#include "xc_utils/src/matrices/m_double.h"
#include "xc_utils/src/utils/misc_utils/mchne_eps.h"
#include "parametriza.h"

typedef enum {interior=1, exterior=2} situ;   // interior, exterior

const bool ant= false;   // extremo anterior
const bool post= true;   // extremo posterior

m_double extremo_calcx(const double &a,const double &b,const double &ab);

m_double extremo_cx( m_double &x,const bool &cambia,const long &interior,const long &exterior);

template<class F>
inline m_double extremo_cy( const F &f,m_double &y,const m_double &x,
                            const bool &cambia,
                            const long &interior,const long &exterior)
  {
    y(cambia+1,(long)exterior)= y(cambia+1,(long)interior);
    y(cambia+1,(long)interior)= y(!cambia+1,(long)interior);
    y(!cambia+1,(long)interior)= f(x(!cambia+1,(long)interior));
    return y;
  }

template <class F>
double extremo( const double &a,const double &b,bool minimo,
                const F &f,const double &dx= sqrt_mchne_eps_dbl)
  {
    bool crece, cambia;

    double ab = b - a;
    m_double x= extremo_calcx(a,b,ab);
    m_double y= matrix_argument(f,x);

    while (ab > dx)
      {
        crece = (y(ant+1,(long)interior) < y(post+1,(long)interior));
        cambia= (crece == minimo);   /* extremo que cambia */
        x= extremo_cx(x,cambia,(long)interior,(long)exterior);
        y= extremo_cy(f,y,x,cambia,(long)interior,(long)exterior);
        ab = x(post+1,(long)exterior) - x(ant+1,(long)exterior);
      }
    return (0.5 * (x(1,(long)exterior) + x(2,(long)exterior)));
  }

template <class F,size_t i>
double extremo( const double &a,const double &b,bool minimo,
                F f, const m_double &x0,
                const double &dx= sqrt_mchne_eps_dbl)
  {
    Parametriza<F,i> pf(f,x0);
    return extremo(a, b, minimo, pf);
  }

#endif

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
//extremo.cc

#include "extremo.h"

m_double extremo_calcx(const double &a,const double &b,const double &ab)
  {
    const double r= (sqrt(5.0)-1)/2.0; //0.61803399...

    m_double x(2,2);
    x(ant+1,exterior)= a;  x(ant+1,interior)= b - ab * r;
    x(post+1,exterior)= b; x(post+1,interior)= a + ab * r;
    return x;
  }

m_double extremo_cx( m_double &x,const bool &cambia,
                            const long &interior,const long &exterior)
  {
    x(cambia+1,exterior)= x(cambia+1,interior);
    x(cambia+1,interior)= x(!cambia+1,interior);
    x(!cambia+1,interior)= x(ant+1,exterior) + 
                           x(post+1,exterior) - 
                           x(cambia+1,interior);
    return x;
  }

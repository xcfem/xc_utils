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
//Gumbel.h

#ifndef GUMBEL_HXX
#define GUMBEL_HXX

#include <cmath>

class Gumbel
  {
    double a;
    double u;
  public:
    Gumbel(const double &alpha, const double &u_)
      : a(alpha), u(u_) {}
    double operator()(const double &x) const
      { return exp(-exp(-a*(x-u))); }
    double Inv(const double &F) const
      { return u-(log(-log(F)))/a; }
  };

#endif

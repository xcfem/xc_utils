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
//PuntosGauss.cc
#include "gssleg.h"

#include "PuntosGauss.h"

//! Genera los puntos de Gauss entre x1 y x2 para un número
//! de ordenadas n.
PuntosGauss::PuntosGauss(double x1, double x2, int n) : ConjPG(n)
  {
    v_double w(n); //pesos.
    v_double x(n); //abcisas.
    int i;

    gss_leg(x1, x2, x, w);
    for(i=0;i<n;i++)
      {
        (*this)[i].w = w[i];
        (*this)[i].x = x[i];
      }
  }
std::ostream& operator<<(std::ostream& o, const PuntosGauss& gpts)
  {
    PuntosGauss::const_iterator i;
    for(i=gpts.begin();i!=gpts.end();i++)
      o << (*i) << ", ";
    return o;
  }

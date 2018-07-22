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
#ifndef	PSOGSS1D_H
#define	PSOGSS1D_H

#include <iostream>


//! Clase para almacenar coordenadas y peso en una dimensión.
struct GaussWeights1D
  {
    double x, w;
    GaussWeights1D()
      : x(0.0), w(0.0) {}
    GaussWeights1D(double X, double W)
      : x(X), w(W) {}
    GaussWeights1D(const GaussWeights1D &gpw)
      : x(gpw.x), w(gpw.w) {}
    GaussWeights1D &operator=(const GaussWeights1D &other)
      {
        x= other.x;
        w= other.w;
        return *this;
      }
  };

std::ostream &operator<<(std::ostream &o, const GaussWeights1D &ggw);


#endif


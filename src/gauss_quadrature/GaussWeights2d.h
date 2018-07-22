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
#ifndef	PSOGSS2D_H
#define	PSOGSS2D_H

#include <iostream>
#include "GaussWeights1d.h"

//! @brief Estructura para almacenar coordenadas y peso en dos dimensiones.
struct GaussWeights2D: public GaussWeights1D
  {
    double y;
    GaussWeights2D(void)
     : GaussWeights1D(), y(0.0) {}
    GaussWeights2D(const GaussWeights2D& gpw)
     : GaussWeights1D(gpw), y(gpw.y) {}
    GaussWeights2D(double X, double Y, double W)
     : GaussWeights1D(X,W), y(Y) {}
    GaussWeights2D &operator=(const GaussWeights2D &other)
      {
        GaussWeights1D::operator=(other);
        y= other.y;
        return *this;
      }
  };

std::ostream& operator<<(std::ostream& o, const GaussWeights2D &ggw);

#endif

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
#include "PsoGss1d.h"

//! @brief Estructura para almacenar coordenadas y peso en dos dimensiones.
struct PsoGss2D: public PsoGss1D
  {
    double y;
    PsoGss2D(void)
     : PsoGss1D(), y(0.0) {}
    PsoGss2D(const PsoGss2D& gpw)
     : PsoGss1D(gpw), y(gpw.y) {}
    PsoGss2D(double X, double Y, double W)
     : PsoGss1D(X,W), y(Y) {}
    PsoGss2D &operator=(const PsoGss2D &otro)
      {
        PsoGss1D::operator=(otro);
        y= otro.y;
        return *this;
      }
  };

std::ostream& operator<<(std::ostream& o, const PsoGss2D &ggw);

#endif

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
#ifndef	PSOGSS3D_H
#define	PSOGSS3D_H

#include <iostream>
#include "PsoGss2d.h"

struct PsoGss3D: public PsoGss2D
  {
    double z;
    PsoGss3D()
      : PsoGss2D(), z(0.0) {}
    PsoGss3D(const PsoGss3D& ggw)
      : PsoGss2D(ggw), z(ggw.z) {}
    PsoGss3D(const double &X, const double &Y, const double &Z, const double &W)
      : PsoGss2D(X,Y,W), z(Z) {}
    PsoGss3D &operator=(const PsoGss3D &otro)
      {
        PsoGss2D::operator=(otro);
        z= otro.z;
        return *this;
      }
  };

std::ostream& operator<<(std::ostream& o, const PsoGss3D &ggw);

#endif

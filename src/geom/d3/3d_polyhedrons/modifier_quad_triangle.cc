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
//modifier_quad_triangle.cc

#include "modifier_quad_triangle.h"

float correction_factor(unsigned int ne, unsigned int nq)
  {
    if(ne == 2 && nq == 1)
      return -0.20505f;
    if(ne == 3 && nq == 1)
      return 0.80597f;
    if(ne == 3 && nq == 2)
      return 0.61539f;
    if(ne == 4 && nq == 1)
      return 0.34792f;
    if(ne == 4 && nq == 2)
      return 0.21380f;
    if(ne == 4 && nq == 3)
      return 0.10550f;
    return 0.0f;
  }

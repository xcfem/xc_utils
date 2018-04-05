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
//Point2d.cc

#include "Point2d.h"
#include <plotter.h>

#include "xc_utils/src/geom/trf/Trf2d.h"
void Point2d::Print(std::ostream &os) const
  { os << org; }
void Point2d::Plot(Plotter &plotter) const
  {
    org.Plot(plotter);
  }

//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Point2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d pA= trf2d.Transforma(org);
    (*this)= Point2d(pA);
  }


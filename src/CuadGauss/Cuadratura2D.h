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
#ifndef	CUADRATURA2D_H
#define	CUADRATURA2D_H

#include <vector>
#include "PsoGss2d.h"
#include "PuntosGauss.h"

typedef std::vector<PsoGss2D> ConjPG2;


class Cuadratura2D : public ConjPG2
  {
  public:
    Cuadratura2D( double x1, double x2,double y1, double y2,int nx, int ny);
    inline size_t Size() const
      { return size(); }
    inline const PsoGss2D &Get(int p) const
      { return (*this)[p]; }
    friend std::ostream& operator<<(std::ostream& o, const Cuadratura2D& gpts);
  };

const Cuadratura2D TwoByTwo(-1.0,1.0,-1.0,1.0,2,2);

#endif








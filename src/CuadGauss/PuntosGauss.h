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
//PuntosGauss.h

#ifndef	PUNTOSGAUSS_H
#define	PUNTOSGAUSS_H

#include <cmath>
#include <vector>
#include "PsoGss1d.h"

typedef std::vector<PsoGss1D> ConjPG; //Pesos de Gauss;


class PuntosGauss : public ConjPG
  {
  public:
    PuntosGauss() : ConjPG(0) {}
    PuntosGauss(double x1, double x2, int n);
    inline size_t Size() const
      { return size(); }
    inline const PsoGss1D &Get(int p) const
      { return (*this)[p]; }
    friend std::ostream& operator<<(std::ostream& o, const PuntosGauss& gpts);
  };

#endif

















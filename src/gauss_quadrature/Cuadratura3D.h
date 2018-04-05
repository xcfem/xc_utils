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
#ifndef	CUADRATURA3D_H
#define	CUADRATURA3D_H

#include <vector>
#include "GaussPoints.h"
#include "PsoGss3d.h"

class Pos3d;

typedef std::vector<PsoGss3D> ConjPG3;

class Cuadratura3D : public ConjPG3
  {
    int num_dim;
  public:
    Cuadratura3D(const Pos3d &p1,const Pos3d &p2,int nx = 2, int ny = 1, int nz = 1);
    inline size_t Size() const
      { return size(); }
    inline const PsoGss3D &Get(int p) const
      { return (*this)[p]; }
    inline int NumDim() const
      { return num_dim; }
    friend std::ostream& operator<<(std::ostream& o, const Cuadratura3D& gpts);
  };

#endif








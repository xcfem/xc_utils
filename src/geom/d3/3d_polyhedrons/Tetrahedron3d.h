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
//TETRAHEDRON3D.h

#ifndef TETRAHEDRON3D_H
#define TETRAHEDRON3D_H

#include <iostream>
#include "PolyhedronBase.h"
#include "PolygonMap.h"

class HalfSpace3d;
class Polyhedron3d;

//! @ingroup GEOM
//
//! @brief Tetrahedron.
class Tetrahedron3d: public PolyhedronBase
  {
    CGTetrahedron_3 cgtetrahedron;
  public:
    Tetrahedron3d(void);
    Tetrahedron3d(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3);
    Tetrahedron3d(const HalfSpace3d &, const HalfSpace3d &,const HalfSpace3d &, const HalfSpace3d &);
    GeomObj *clon(void) const
      { return new Tetrahedron3d(*this); }
    Polyhedron3d getPolyhedron3d(void) const;
    GEOM_FT getArea(void) const;
    GEOM_FT getVolumeWithSign(void) const;
    GEOM_FT getVolume(void) const;
    double GetMax(short unsigned int i) const;
    double GetMin(short unsigned int i) const;
    bool In(const Pos3d &,const double &) const;
    void Print(std::ostream &os) const;
  };

PolygonMap<CGPolyhedron_3> getPolygonMap(const Tetrahedron3d &t);

#endif

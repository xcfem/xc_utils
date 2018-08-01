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
//TETRAEDRO3D.h

#ifndef TETRAEDRO3D_H
#define TETRAEDRO3D_H

#include <iostream>
#include "PolyhedronBase.h"
#include "PolygonMap.h"

class HalfSpace3d;
class Poliedro3d;

//! @ingroup GEOM
//
//! @brief Tetraedro.
class Tetraedro3d: public PolyhedronBase
  {
    CGTetrahedron_3 cgtetraedro;
  public:
    Tetraedro3d(void);
    Tetraedro3d(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3);
    Tetraedro3d(const HalfSpace3d &, const HalfSpace3d &,const HalfSpace3d &, const HalfSpace3d &);
    GeomObj *clon(void) const
      { return new Tetraedro3d(*this); }
    Poliedro3d getPoliedro3d(void) const;
    GEOM_FT getArea(void) const;
    GEOM_FT getVolumeWithSign(void) const;
    GEOM_FT getVolume(void) const;
    double GetMax(short unsigned int i) const;
    double GetMin(short unsigned int i) const;
    bool In(const Pos3d &,const double &) const;
    void Print(std::ostream &os) const;
  };

PolygonMap<CGPoliedro_3> getPolygonMap(const Tetraedro3d &t);

#endif

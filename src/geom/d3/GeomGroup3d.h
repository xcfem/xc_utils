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
//GeomGroup3d.h

#ifndef GEOMGROUP3D_H
#define GEOMGROUP3D_H

#include "xc_utils/src/utils/stl/pdeque.h"
#include "GeomObj3d.h"
#include "xc_utils/src/geom/lists/GeomGroup.h"

class Line3d;


//! @ingroup GEOM
//
//! @brief Group of 3D entities.
class GeomGroup3d : public GeomGroup<GeomObj3d>
  {

    virtual GEOM_FT inertia(const Line3d &e) const;
  public:
    typedef pdeque_geom_obj::const_iterator const_iterator;
    typedef pdeque_geom_obj::iterator iterator;


    GeomGroup3d(void) : GeomGroup<GeomObj3d>() {}

    virtual GeomObj3d *clon(void) const
      { return new GeomGroup3d(*this); }

    virtual Pos3d getCenterOfMass(void) const;

    virtual GEOM_FT Ix(void) const;
    //Moment of inertia with respect to the center of mass in local coordinates.
    virtual GEOM_FT Iy(void) const;
    //Moment of inertia with respect to the center of mass in local coordinates.
    virtual GEOM_FT Iz(void) const;
    //Moment of inertia with respect to the center of mass in local coordinates.
    GEOM_FT Pxy(void) const;
    //product of inertia with respect to the center of mass in local coordinates.

    
  };

#endif

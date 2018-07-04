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
//GmGrupo3d.h

#ifndef GMGRUPO3D_H
#define GMGRUPO3D_H

#include "xc_basic/src/stl/pdeque.h"
#include "GeomObj3d.h"
#include "xc_utils/src/geom/listas/GmGrupo.h"

class Recta3d;


//! @ingroup GEOM
//
//! @brief Grupo de entidades geométricas en tres dimensiones.
class GmGrupo3d : public GmGrupo<GeomObj3d>
  {

    virtual GEOM_FT inercia(const Recta3d &e) const;
  public:
    typedef pdeque_geom_obj::const_iterator const_iterator;
    typedef pdeque_geom_obj::iterator iterator;


    GmGrupo3d(void) : GmGrupo<GeomObj3d>() {}
    GmGrupo3d(const GmGrupo3d &other) : GmGrupo<GeomObj3d>(other) {}

    virtual GeomObj3d *clon(void) const
      { return new GmGrupo3d(*this); }

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

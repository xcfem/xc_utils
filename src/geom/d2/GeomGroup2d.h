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
//GeomGroup2d.h

#ifndef GEOMGROUP2D_H
#define GEOMGROUP2D_H

#include "xc_basic/src/stl/pdeque.h"
#include "GeomObj2d.h"
#include "xc_utils/src/geom/listas/GeomGroup.h"

class Line2d;

//! @ingroup GEOM
//
//! @brief  Group of 3D entities.
class GeomGroup2d : public GeomGroup<GeomObj2d>
  {

    virtual GEOM_FT inercia(const Line2d &e) const;
  public:
    typedef pdeque_geom_obj::const_iterator const_iterator;
    typedef pdeque_geom_obj::iterator iterator;


    GeomGroup2d(void) : GeomGroup<GeomObj2d>() {}

    virtual GeomObj2d *clon(void) const
      { return new GeomGroup2d(*this); }

    //! @brief Return the volume of the object.
    inline virtual GEOM_FT getVolume(void) const
      { return 0.0; }
    virtual Pos2d getCenterOfMass(void) const;

    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    GEOM_FT Pxy(void) const;

    void Print(std::ostream &stream) const;
    void Plot(Plotter &) const;

    void Transforma(const Trf2d &trf2d);

    
  };

#endif

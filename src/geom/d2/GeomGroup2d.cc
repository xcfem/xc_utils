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
//GeomGroup2d.cc

#include "GeomGroup2d.h"

#include <plotter.h>
#include <iostream>

#include "xc_utils/src/geom/pos_vec/Dir2d.h"
#include "xc_utils/src/geom/d0/Point2d.h"
#include "xc_utils/src/geom/d1/Line2d.h"
#include "xc_utils/src/geom/d1/Ray2d.h"
#include "xc_utils/src/geom/d1/Segment2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Triangle2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"

//! @brief Return el moment of inertia with respect to the line argument.
GEOM_FT GeomGroup2d::inertia(const Line2d &e) const
  {
    if(objetos.empty()) return 0.0;
    if(!igual_dimension())
      {
        cerr << getClassName() << "::" << __FUNCTION__
	     << "; warning, the object of the group have"
	     << " different dimensions." << endl;
      }
    register pdeque_geom_obj::const_iterator i(objetos.begin());
    register GEOM_FT retval((*i)->I(e));
    i++;
    for(;i!=objetos.end();i++)
      retval+= (*i)->I(e);
    return retval;
  }

//! @brief Moment of inertia with respect to an axis parallel to
//! the x axis passing through the center of mass.
GEOM_FT GeomGroup2d::Ix(void) const
  { return inertia(Line2d(getCenterOfMass(),Dir2d(1.0,0.0))); }

//! @brief Moment of inertia with respect to an axis parallel to
//! the y axis passing through the center of mass.
GEOM_FT GeomGroup2d::Iy(void) const
  { return inertia(Line2d(getCenterOfMass(),Dir2d(0.0,1.0))); }

//! @brief Moment of inertia with respect to the axis parallel to
//! the x and y axis passing through the center of mass.
GEOM_FT GeomGroup2d::Pxy(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	 << "; not implemented, 0 is returned." << endl;
    return 0.0;
  }

//! @brief Return the center of mass.
Pos2d GeomGroup2d::getCenterOfMass(void) const
  {
    if(objetos.empty()) return Pos2d();
    if(!igual_dimension())
      {
        cerr << getClassName() << "::" << __FUNCTION__
	     << "; Warning!, the objects in the group"
	     << " have different dimensions." << endl;
      }
    register pdeque_geom_obj::const_iterator i(objetos.begin());
    GEOM_FT area_i= (*i)->getCenterOfMassArea();
    Vector2d num= (*i)->getCenterOfMass().VectorPos()*area_i;
    GEOM_FT denom(area_i);
    i++;
    for(;i!=objetos.end();i++)
      {
        area_i= (*i)->getCenterOfMassArea();
        num= num + (*i)->getCenterOfMass().VectorPos()*area_i;
        denom+= area_i;
      }
    num= num*(1/denom);
    return Origen2d+num;
  }

//! @brief Applies the transformation to the points.
void GeomGroup2d::Transforma(const Trf2d &trf2d)
  {
    for(pdeque_geom_obj::iterator i= objetos.begin();i!=objetos.end();i++)
      (*i)->Transforma(trf2d);
  }

void GeomGroup2d::Print(std::ostream &stream) const
  {
    for(register pdeque_geom_obj::const_iterator i= objetos.begin();i!=objetos.end();i++)
      (*i)->Print(stream);
  }
void GeomGroup2d::Plot(Plotter &plotter) const
  {
    for(register pdeque_geom_obj::const_iterator i= objetos.begin();i!=objetos.end();i++)
      (*i)->Plot(plotter);
  }


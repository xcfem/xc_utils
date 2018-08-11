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
//GeomGroup3d.cc

#include "GeomGroup3d.h"


#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d0/Point3d.h"
#include "xc_utils/src/geom/d1/Line3d.h"
#include "xc_utils/src/geom/d1/Ray3d.h"
#include "xc_utils/src/geom/d1/Segment3d.h"

//Return the moment of inertia with respect to the line argument
GEOM_FT GeomGroup3d::inercia(const Line3d &e) const
  {
    if(objetos.empty()) return 0.0;
    if(!igual_dimension())
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; Warning!, the objects of the group have"
	          << " different dimensions." << std::endl;
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
GEOM_FT GeomGroup3d::Ix(void) const
  { return inercia(Line3d(getCenterOfMass(),Dir3d(1.0,0.0,0.0))); }

//! @brief Moment of inertia with respect to an axis parallel to
//! the y axis passing through the center of mass.
GEOM_FT GeomGroup3d::Iy(void) const
  { return inercia(Line3d(getCenterOfMass(),Dir3d(0.0,1.0,0.0))); }

//! @brief Moment of inertia with respect to an axis parallel to
//! the z axis passing through the center of mass.
GEOM_FT GeomGroup3d::Iz(void) const
  { return inercia(Line3d(getCenterOfMass(),Dir3d(0.0,0.0,1.0))); }

//! @brief Moment of inertia with respect to the axis parallel to
//! the x and y axis passing through the center of mass.
GEOM_FT GeomGroup3d::Pxy(void) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented, 0 is returned." << std::endl;
    return 0.0;
  }

//! @brief Return the position of the object's center of mass.
Pos3d GeomGroup3d::getCenterOfMass(void) const
  {
    if(objetos.empty()) return Pos3d();
    if(!igual_dimension())
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
	          << "; Warning!, the objects of this group"
	          << " have different dimensions." << std::endl;
      }    register pdeque_geom_obj::const_iterator i(objetos.begin());
    GEOM_FT area_i= (*i)->getCenterOfMassArea();
    Vector3d num= (*i)->getCenterOfMass().VectorPos()*area_i;
    GEOM_FT denom(area_i);
    i++;
    for(;i!=objetos.end();i++)
      {
        area_i= (*i)->getCenterOfMassArea();
        num= num + (*i)->getCenterOfMass().VectorPos()*area_i;
        denom+= area_i;
      }
    num= num*(1/denom);
    return Origen3d+num;
  }

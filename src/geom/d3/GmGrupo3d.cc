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
//GmGrupo3d.cc

#include "GmGrupo3d.h"


#include "xc_utils/src/geom/pos_vec/Dir3d.h"
#include "xc_utils/src/geom/d0/Point3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d1/Ray3d.h"
#include "xc_utils/src/geom/d1/Segment3d.h"

GEOM_FT GmGrupo3d::inercia(const Recta3d &e) const
//Return el moment of inertia with respect to la recta e
  {
    if(objetos.empty()) return 0.0;
    if(!igual_dimension())
      {
        std::cerr << "¡Ojo!, GmGrupo3d::inercia: los objetos del grupo tienen distintas dimensiones." << std::endl;
      }
    register pdeque_geom_obj::const_iterator i(objetos.begin());
    register GEOM_FT retval((*i)->I(e));
    i++;
    for(;i!=objetos.end();i++)
      retval+= (*i)->I(e);
    return retval;
  }

GEOM_FT GmGrupo3d::Ix(void) const
//Moment of inertia with respect to the center of mass in local coordinates.
{ return inercia(Recta3d(getCenterOfMass(),Dir3d(1.0,0.0,0.0))); }
GEOM_FT GmGrupo3d::Iy(void) const
//Moment of inertia with respect to the center of mass in local coordinates.
{ return inercia(Recta3d(getCenterOfMass(),Dir3d(0.0,1.0,0.0))); }
GEOM_FT GmGrupo3d::Iz(void) const
//Moment of inertia with respect to the center of mass in local coordinates.
{ return inercia(Recta3d(getCenterOfMass(),Dir3d(0.0,0.0,1.0))); }
GEOM_FT GmGrupo3d::Pxy(void) const
  {
    std::cerr << "GmGrupo3d::Pxy not implemented, 0 is returned." << std::endl;
    return 0.0;
  }

Pos3d GmGrupo3d::getCenterOfMass(void) const
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

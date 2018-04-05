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
//SemiRecta3d.cc

#include "SemiRecta3d.h"

#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Pos3d.h"

SemiRecta3d::SemiRecta3d(const Pos3d &p1,const Pos3d &p2)
  : Linea3d(), cgsr(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        std::clog << getClassName() << "::" << __FUNCTION__
		  << "; degenerate line, the points: "
             << p1 << " and " << p2 << " are the same." << std::endl;
      }
  }
void SemiRecta3d::TwoPoints(const Pos3d &p1,const Pos3d &p2)
  { (*this)= SemiRecta3d(p1,p2); }

Dir3d SemiRecta3d::GetDir(void) const
  { return Dir3d(cgsr.direction()); }
Vector3d SemiRecta3d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Returns the squared distand from the point.
GEOM_FT SemiRecta3d::dist2(const Pos3d &p) const
  {
    const Recta3d r= RectaSoporte();
    const Pos3d proj= r.Projection(p);
    GEOM_FT retval= p.dist2(proj); //OK if projection inside half-line.
    if(!In(proj)) //Projection outside half-line.
      retval= p.dist2(Origen());
    return retval;
  }

//! @brief Return the distance 
//! from the point a la semirrecta.
GEOM_FT SemiRecta3d::dist(const Pos3d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Return true if son paralelas.
bool SemiRecta3d::Paralela(const SemiRecta3d &r) const
  { return (GetDir()== r.GetDir()); }

//! @brief Return true if son paralelas.
bool SemiRecta3d::Paralela(const Recta3d &r) const
  { return (GetDir()== r.GetDir()); }

//! @brief Return the point intersección de recta and semirrecta, if doesn't exists la
//! intersección devuelve la lista vacía.
GeomObj3d::list_Pos3d SemiRecta3d::Interseccion(const Recta3d &r) const
  {
    const Recta3d sop= RectaSoporte();
    GeomObj3d::list_Pos3d retval= sop.Interseccion(r);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //intersection point is NOT on the ray.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

//! @brief Return the intersección de la semirrecta con un plano coord_i=cte.
GeomObj3d::list_Pos3d SemiRecta3d::Interseccion(unsigned short int i, const double &d) const
  {
    GeomObj3d::list_Pos3d lp;
    lp= RectaSoporte().Interseccion(i,d);
    if(!lp.empty())
      {
        const Vector3d i_= VDir();
        const double l= RectaSoporte().getLambda(i,d,i_);
        if(l<0.0)
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

//! @brief Return the point intersección de ambas semirectas, if doesn't exists
//! intersección devuelve la lista vacía.
GeomObj3d::list_Pos3d SemiRecta3d::Interseccion(const SemiRecta3d &sr) const
  {
    const Recta3d sop1= RectaSoporte();
    GeomObj3d::list_Pos3d retval= sr.Interseccion(sop1);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //intersection point is NOT on the ray.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }




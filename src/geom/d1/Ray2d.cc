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
//Ray2d.cc

#include "Ray2d.h"

#include <plotter.h>
#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"

Ray2d::Ray2d(const Pos2d &p1,const Pos2d &p2)
  : Linear2d(), cgsr(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        clog << getClassName() << "::" << __FUNCTION__
	     << "; degenerated line, the points: "
             << p1 << " and " << p2 << " are the same." << endl;
      }
  }
Ray2d::Ray2d(const Pos2d &p1,const Vector2d &vdir)
  : Linear2d(), cgsr(p1.ToCGAL(),vdir.ToCGAL()) {}
void Ray2d::TwoPoints(const Pos2d &p1,const Pos2d &p2)
  { (*this)= Ray2d(p1,p2); }

Dir2d Ray2d::GetDir(void) const
  { return Dir2d(cgsr.direction()); }
Vector2d Ray2d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Return the squared distance 
//! from the point to the ray.
GEOM_FT Ray2d::dist2(const Pos2d &p) const
  {
    Line2d r= getSupportLine();
    Pos2d proj= r.Projection(p);
    GEOM_FT retval= p.dist2(proj); //Ok if projection inside half-line.
    if(!In(proj)) //Projection outside half-line.
      retval= p.dist2(Origen());
    return retval;
  }

//! @brief Return the distance 
//! from the point to the ray.
GEOM_FT Ray2d::dist(const Pos2d &p) const
  { return sqrt_FT(dist2(p)); }

bool Ray2d::intersects(const Line2d &r) const
  { return do_intersect(r.cgr,cgsr); }

//! @brief Return the intersection of the ray with the plane
//! defined by the equation coord_i= d.
GeomObj2d::list_Pos2d Ray2d::getIntersection(unsigned short int i, const double &d) const
  {
    GeomObj2d::list_Pos2d lp;
    lp= getSupportLine().getIntersection(i,d);
    if(!lp.empty())
      {
        const Vector2d i_= VDir();
        const double l= getSupportLine().getLambda(i,d,i_);
        if(l<0.0)
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

//! @brief Return the point intersection of the line and the ray, if it
//! doesn't exists return an empty list.
GeomObj2d::list_Pos2d Ray2d::getIntersection(const Line2d &r) const
  {
    GeomObj2d::list_Pos2d retval;
    if(intersects(r))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        result = CGAL::intersection(cgsr,r.cgr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << getClassName() << "::" << __FUNCTION__
	         << "; unknown error." << endl
                 << "sg: " << *this << endl
                 << "r: " << r << endl;
          }
      }
    return retval;
  }

//! @brief Return the point intersection of both lines, if doesn't exists
//! returns an empty list.
GeomObj2d::list_Pos2d Ray2d::getIntersection(const Ray2d &r2) const
  {
    GeomObj2d::list_Pos2d retval;
    if(*this == r2)
      {
        cerr << getClassName() << "::" << __FUNCTION__
	     << "; rays are the same, all its points belong"
	     << " to the intersection." << std::endl;
        return retval;
      }
    if(intersects(r2))
      {
        CGAL::Object result;
        Pos2d ptoi;
        result = CGAL::intersection(this->cgsr,r2.cgsr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << "intersection(Ray2d,Ray2d): unknown error." 
                 << endl;
          }
      }
    return retval;
  }


//! @brief Applies to the ray the transformation argument.
void Ray2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d p1= trf2d.Transforma(Origen());
    const Pos2d p2= trf2d.Transforma(Point(100));
    (*this)= Ray2d(p1,p2);
  }

void Ray2d::Print(std::ostream &os) const
  { os << PtoParametricas(0.0) << " " << PtoParametricas(100.0); }
void Ray2d::Plot(Plotter &psos) const
  {
    //Ray is not drawn, it must be clipped first.
  }


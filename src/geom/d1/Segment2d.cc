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
//Segment2d.cc

#include "Segment2d.h"
#include <plotter.h>

#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/VectorPos2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"




//! @brief Constructor.
Segment2d::Segment2d(const Pos2d &p1,const Pos2d &p2)
  : Linea2d(), cgseg(p1.ToCGAL(),p2.ToCGAL())
  {
    if(verbosity>2 && EsDegenerada())
      {
        clog << getClassName() << "::" << __FUNCTION__
	     << "; degenerated line, the points: "
             << p1 << " and " << p2 << " are the same." << endl;
      }
  }
void Segment2d::TwoPoints(const Pos2d &p1,const Pos2d &p2)
  { (*this)= Segment2d(p1,p2); }

GeomObj *Segment2d::clon(void) const
  { return new Segment2d(*this); }

//! @brief Return the direction of the segment.
Dir2d Segment2d::GetDir(void) const
  { return Dir2d(cgseg.direction()); }

//! @brief Return el direction vector of the segment.
Vector2d Segment2d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Return el direction vector of the segment.
Vector2d Segment2d::Normal(void) const
  { return VDir().Normal(); }

//! @brief Return el vector que une el origen con el extremo of the segment.
Vector2d Segment2d::GetVector(void) const
  { return Destino()-Origen(); }

//! @brief Return the angle of the segment con el vector (0->2PI).
GEOM_FT Segment2d::getAngle(const Vector2d &v) const
  { return angle(VDir(),v); }

//! @brief Return the angle of the segment con el vector (-PI->0->PI).
GEOM_FT Segment2d::getSignedAngle(const Vector2d &v) const
  { return signedAngle(VDir(),v); }

//! @brief Return the angle of the segment con el vector (0->2PI).
GEOM_FT Segment2d::getAngle(const Segment2d &s) const
  { return getAngle(s.VDir()); }

//! @brief Return the angle of the segment con el vector (-PI->0->PI).
GEOM_FT Segment2d::getSignedAngle(const Segment2d &s) const
  { return getSignedAngle(s.VDir()); }


//! @brief Return the angle of the segment con el X axis.
GEOM_FT Segment2d::XAxisAngle(void) const
  { return VDir().XAxisAngle(); }

//! @brief Return the angle of the segment con el Y axis.
GEOM_FT Segment2d::YAxisAngle(void) const
  { return VDir().YAxisAngle(); }

GEOM_FT angle(const Segment2d &r,const Vector2d &v)
  { return r.getAngle(v); }

GEOM_FT angle(const Vector2d &v, const Segment2d &r)
  { return v.getAngle(r.VDir()); }

//! @brief Return object length.
GEOM_FT Segment2d::getLength(void) const
  { return Origen().dist(Destino()); }

//! @brief Return the position of the center of mass of the segment.
Pos2d Segment2d::getCenterOfMass(void) const
  {
    Pos2d retval= Origen();
    const Vector2d v= (Destino()-retval)/2;
    retval= retval+v;
    return retval;
  }

//! @brief Return the recta perpendicular a r que pasa por p.
Recta2d Segment2d::Perpendicular(const Pos2d &p) const
  { return RectaSoporte().Perpendicular(p); }

//! @brief Return the recta paralela a ésta que pasa por p.
Recta2d Segment2d::Paralela(const Pos2d &p) const
  { return RectaSoporte().Paralela(p); }

//! @brief Return the a copy of the segment translatec along
//! the vector argument.
Segment2d Segment2d::Offset(const Vector2d &v) const
  {
    const Pos2d p= Origen()+v;
    const Pos2d q= Destino()+v;
    return Segment2d(p,q);
  }

//! @brief Return a segment parallel to this one at the distance
//! argument. If the distance is poisitive the new segment will
//! be on the right from this one.
Segment2d Segment2d::Offset(const GEOM_FT &d) const
  {
    const Vector2d v= d*RectaSoporte().VersorDir();
    const Vector2d n(v.y(),-v.x());
    return Offset(n);
  }

//! @brief Return the perpendicular_bisector of the segment.
Recta2d Segment2d::getPerpendicularBisector(void) const
  {
    const Pos2d p=getCenterOfMass();
    const Vector2d v= VDir().Perpendicular(CGAL::COUNTERCLOCKWISE);
    const Pos2d p2= p+100.0*v;
    return Recta2d(p,p2);
  }

//! Return true if the point is on the segment.
bool Segment2d::In(const Pos2d &p, const double &tol) const
  {
    bool retval= cgseg.has_on(p.ToCGAL());
    if(!retval)
      {
        const Pos2d &O= Origen();
        const Pos2d &D= Origen();
        const double L= getLength();
        if(L>=tol)
          {
            const double x1= O.x();
            const double y1= O.y(); 
            const double x2= D.x();
            const double y2= D.y();
            const double px= p.x();
            const double py= p.y();
            const double u1= ( ((px-x1)*(x2-x1)) +((py-y1)*(y2-y1)) );
	    const double u= u1/(L*L);
            retval= (u>-tol) && (u<(1+tol));
          }
      }
    return retval;
  }


//! @brief Return the squared distance to the segment.
GEOM_FT Segment2d::dist2(const Pos2d &p) const
  {
    const Recta2d r= RectaSoporte();
    const Pos2d proj= r.Projection(p);
    GEOM_FT retval= p.dist2(proj); //Ok if projected point inside segment.
    const Pos2d A= Origen();
    const Pos2d B= Destino();
    const GEOM_FT denom= (B.x()-A.x())*(B.x()-A.x())+(B.y()-A.y())*(B.y()-A.y());
    if(denom!=0)
      {
        const GEOM_FT u= ( (p.x()-A.x())*(B.x()-A.x()) + (p.y()-A.y())*(B.y()-A.y()) )/denom;
        if(u<0.0) //Distance to the origin.
	  retval= p.dist2(A);
	else if(u>1.0) //Distance to the destination.
          retval= p.dist2(B);
      }
    return retval;

  }

//! @brief Return the distance from the point to the segment.
GEOM_FT Segment2d::dist(const Pos2d &p) const
  { return sqrt(dist2(p)); }

//! @brief Return a point of the segment at a distance lambda from its origin.
Pos2d Segment2d::PtoParametricas(const GEOM_FT &lambda) const
  { return Origen()+lambda*VDir().Normalizado(); }

//! @brief Return the coordenada paramétrica que corresponde
//! a la coordenada natural se pasa como parámetro.
double Segment2d::getParamCooNatural(const GEOM_FT &chi) const
  { return (chi+1.0)/2.0; }

//! @brief Return the point of the segment cuyas coordenada
//! natural se pasa como parámetro.
Pos2d Segment2d::PtoCooNatural(const GEOM_FT &chi) const
  { return PtoParametricas(getParamCooNatural(chi)); }

bool Segment2d::intersects(const Recta2d &r) const
  { return CGAL::do_intersect(r.cgr,cgseg); }
bool Segment2d::intersects(const Ray2d &sr) const
  { return do_intersect(sr.cgsr,cgseg); }

//! @brief Return the intersection of the line with a plane defined
//! by the equation coord_i=cte.
GeomObj2d::list_Pos2d Segment2d::getIntersection(unsigned short int i, const double &d) const
  {
    GeomObj2d::list_Pos2d lp;
    lp= RectaSoporte().getIntersection(i,d);
    if(!lp.empty())
      {
        const Vector2d i_= VDir();
        const double l= RectaSoporte().getLambda(i,d,i_);
        if( (l<0.0) || (l>getLength()) )
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

//! @brief Return the intersection point of the line and the segment, if
//! the intersection doesn't exists returns an empty list.
GeomObj2d::list_Pos2d Segment2d::getIntersection(const Recta2d &r) const
  {
    GeomObj2d::list_Pos2d retval;
    if(intersects(r))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        CGSegment_2 segi;
        result = CGAL::intersection(cgseg,r.cgr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else if(CGAL::assign(segi, result)) 
          retval.push_back(getCenterOfMass()); //Return el centro de ESTE.
        else
          {
            const GEOM_FT d1= r.dist2(Origen());
            const GEOM_FT d2= r.dist2(Destino());
            const GEOM_FT tol= getLength()/1e4;
            if(d1<tol)
              retval.push_back(Origen());
            else if(d2<tol)
              retval.push_back(Destino());
            else
              cerr << "Segment2d::getIntersection(Recta2d): unknown error." << endl
                   << "sg: " << *this << endl
                   << "r: " << r << endl
                   << "tol: " << tol << endl
                   << "d1: " << d1 << endl
                   << "d2: " << d2 << endl;
          }
      }
    return retval;
  }

//! @brief Return the intersection of the segment and the ray,
//! if it doesn't exists return an empty list.
GeomObj2d::list_Pos2d Segment2d::getIntersection(const Ray2d &sr) const
  {
    GeomObj2d::list_Pos2d retval;
    if(intersects(sr))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        result = CGAL::intersection(cgseg,sr.cgsr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << "Segment2d::getIntersection(Ray2d): unknown error." << endl
                 << "sg: " << *this << endl
                 << "sr: " << sr << endl;
          }
      }
    return retval;
  }

//! @brief Return the intersection of the segments, if
//! the intersection doesn't exists returns an empty list.
GeomObj2d::list_Pos2d Segment2d::getIntersection(const Segment2d &r2) const
  {
    GeomObj2d::list_Pos2d retval;
    if(*this == r2)
      {
        cerr << getClassName() << "::" << __FUNCTION__
	     << "; segments are de same, all its points belong to the"
	     << " intersection." << endl;
        retval.push_back(Origen());
        retval.push_back(Destino());
        return retval;
      }
    if(intersects(r2))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        result = CGAL::intersection(cgseg,r2.cgseg);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << getClassName() << "::" << __FUNCTION__
		 << "; unknown error." << endl
                 << "s: " << *this << endl
                 << "s2: " << r2 << endl;
          }
      }
    return retval;
  }

GEOM_FT dist(const Pos2d &p,const Segment2d &r)
  { return sqrt_FT(r.dist2(p)); }

//! @brief Return the points that results from the segment division.
//! @param num_partes: number of segments.
VectorPos2d Segment2d::Divide(int num_partes) const
  { return VectorPos2d(Origen(),Destino(),num_partes); }

//! @brief Aplica a la recta la transformación que se
//! pasa como parámetro.
void Segment2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d p1= trf2d.Transforma(Origen());
    const Pos2d p2= trf2d.Transforma(Destino());
    (*this)= Segment2d(p1,p2);
  }

void Segment2d::Print(std::ostream &os) const
  { os << Origen() << " " << Destino(); }
void Segment2d::Plot(Plotter &plotter) const
  {
    const Pos2d p1= Origen();
    const Pos2d p2= Destino();
    plotter.fline(p1.x(),p1.y(),p2.x(),p2.y());
  }

//! Return the point de intersection of the segment con la recta, if exists.
Pos2d intersection_point(const Segment2d &s, const Recta2d &r)
  {
    Pos2d retval;
    GeomObj2d::list_Pos2d tmp= intersection(s,r);
    if(tmp.empty())
      retval.setExists(false);
    else
      retval= *tmp.begin();
     return retval;
  }

//! Return the point de intersection of the segment con la recta, if exists.
Pos2d intersection_point(const Recta2d &r, const Segment2d &s)
  { return intersection_point(s,r); }

//! Return the intersection of the segments if exists.
Pos2d intersection_point(const Segment2d &s1, const Segment2d &s2)
  {
    Pos2d retval;
    GeomObj2d::list_Pos2d tmp= intersection(s1,s2);
    if(tmp.empty())
      retval.setExists(false);
    else
      retval= *tmp.begin();
    return retval;
  }

std::list<Segment2d> sin_degenerados(const std::list<Segment2d> &lista)
  {
    std::list<Segment2d> retval;
    for(list<Segment2d>::const_iterator i=lista.begin();i!=lista.end();i++)
      if(!(*i).EsDegenerada())
        retval.push_back(*i);
    return retval;
  }



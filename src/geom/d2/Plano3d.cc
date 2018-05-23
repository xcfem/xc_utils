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
//Plano3d.cc

#include "Plano3d.h"
#include "../listas/ThreePoints3d.h"
#include "GeneralEquationOfPlane.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/d1/SemiRecta3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d1/Polilinea3d.h"
#include "xc_utils/src/geom/d2/Poligono3d.h"
#include "xc_utils/src/geom/d2/Triangulo3d.h"
#include "xc_utils/src/geom/d3/GmGrupo3d.h"
#include "xc_basic/src/util/mchne_eps.h"



#include "CGAL/linear_least_squares_fitting_3.h"

Plano3d::Plano3d(void)
  : Superficie3d(), cgp(CGPoint_3(0,0,0), CGPoint_3(1,0,0), CGPoint_3(0,1,0)) {}

Plano3d::Plano3d(const CGPlane_3 &cgp)
  : Superficie3d(), cgp(cgp) {}

//! @brief Constructor: plane defined by three points.
Plano3d::Plano3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : Superficie3d(), cgp(p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL()) 
  {
    // const GEOM_FT tol2= 1e-3;
    // const GEOM_FT d12= p1.dist2(p2);
    // if(d12<tol2)
    //   {
    //     std::clog << "Plano3d; points p1= " << p1 << " and p2= " 
    //               << p2 << " are too close d= " << sqrt(d12) << std::endl;
    //   }
    // const GEOM_FT d13= p1.dist2(p3);
    // if(d13<tol2)
    //   {
    //     std::clog << "Plano3d; points p1= " << p1 << " and p3= " 
    //               << p3 << " are too close d= " << sqrt(d13) << std::endl;
    //   }
    // const GEOM_FT d23= p2.dist2(p3);
    // if(d23<tol2)
    //   {
    //     std::clog << "Plano3d; points p2= " << p2 << " and p3= " 
    //               << p3 << " are too close d= " << sqrt(d23) << std::endl;
    //   }  
  }


//! @brief Constructor: plane defined by the point and the normal vector.
Plano3d::Plano3d(const Pos3d &o,const Vector3d &v)
  : Superficie3d(), cgp(o.ToCGAL(),v.ToCGAL()) {}

//! @brief Converts the point classification to the polygon one.
Plano3d::clasif_poligono Plano3d::clfpnt2clfpol(const CGAL::Oriented_side os)
  {
    clasif_poligono retval= DETRAS;
    switch(os)
      {
        case CGAL::ON_NEGATIVE_SIDE:
          retval= DETRAS;
          break;
        case CGAL::ON_POSITIVE_SIDE:
          retval= DELANTE;
          break;
        case CGAL::ON_ORIENTED_BOUNDARY:
          retval= DENTRO;
          break;
      }
    return retval;
  }

Plano3d::Plano3d(const Recta3d &r,const Pos3d &p)
  : Superficie3d(), cgp(r.ToCGAL(),p.ToCGAL()) {}
Plano3d::Plano3d(const Segmento3d &s,const Vector3d &v)
  : Superficie3d(), cgp(s.RectaSoporte().ToCGAL(),(s.Origen()+v).ToCGAL()) {}
Plano3d::Plano3d(const Pos3d &p,const Vector3d &v1,const Vector3d &v2)
  : Superficie3d(), cgp(p.ToCGAL(),(p+v1).ToCGAL(),(p+v2).ToCGAL()) {}
Plano3d::Plano3d(const GeomObj3d::list_Pos3d &lp): Superficie3d(), cgp()
  {
    if(lp.size()<3)
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; the list must contain at least three points." 
             << std::endl;
      }
    GeomObj3d::list_Pos3d::const_iterator i= lp.begin();
    ThreePoints(*i,*i++,*i++);
  }
Plano3d::Plano3d(const Poligono3d &pg3d)
  : Superficie3d(), cgp()
  { *this= pg3d.GetPlano(); }
Plano3d::Plano3d(const GeneralEquationOfPlane &eg)
  : Superficie3d(), cgp(eg.a(),eg.b(),eg.c(),eg.d()) {}

Plano3d::Plano3d(const Plano3d &otro)
  : Superficie3d(), cgp(otro.cgp) {}

Plano3d &Plano3d::operator=(const Plano3d &otro)
  {
    cgp=(otro.cgp);
    Superficie3d::operator=(otro);
    return *this;
  }

GeomObj *Plano3d::clon(void) const
  { return new Plano3d(*this); }

void Plano3d::ThreePoints(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  { operator=(Plano3d(p1,p2,p3)); }

//! @brief Return el vector normal al plano con sentido hacia el lado "positivo".
Vector3d Plano3d::Normal(void) const
  { return Vector3d(cgp.orthogonal_vector()); }
//! @brief Return un vector ortogonal al devuelto por Normal().
Vector3d Plano3d::Base1(void) const
  { return Vector3d(cgp.base1()); }
//! @brief Return un vector ortogonal al devuelto por Normal() y al devuelto por Base1().
Vector3d Plano3d::Base2(void) const
  { return Vector3d(cgp.base2()); }

//! @brief Return un sistema de coordenadas cuyo plano XY
//! coincide con éste.
SisCooRect2d3d Plano3d::getSisCoo(void) const
  { return SisCooRect2d3d(Base1(),Base2()); }

//! @brief Return un sistema de referencia cuyo plano XY
//! coincide con éste.
Ref2d3d Plano3d::getRef(const Pos3d &org) const
  { return Ref2d3d(org,Base1(),Base2()); }

void Plano3d::Swap(void)
  { operator=(GetSwap()); }
Plano3d Plano3d::GetSwap(void) const
  { return Plano3d(cgp.opposite()); }

//! @brief Return the projection of the point onto this plane.
Pos3d Plano3d::Projection(const Pos3d &p) const
  { return Pos3d(cgp.projection(p.ToCGAL())); }

//! @brief Return the projection of the vector onto this plane.
Vector3d Plano3d::Projection(const Vector3d &v) const
  {
    const Vector3d n= Normal().Normalizado();
    return cross(cross(n,v),n);
  }

//! @brief Return the projection of the line onto this plane.
Recta3d Plano3d::Projection(const Recta3d &r) const
  {
    Recta3d retval;
    const Pos3d p0= Projection(r.Point(0));
    const Pos3d p1= Projection(r.Point(100));
    const double d= p0.dist(p1);
    if(d>mchne_eps_dbl)
      retval= Recta3d(p0,p1);
    else
      retval.setExists(false);
    return retval;
  }

GeomObj3d::list_Pos3d Plano3d::Projection(const GeomObj3d::list_Pos3d &ptos) const
  {
    GeomObj3d::list_Pos3d retval;
    for(GeomObj3d::list_Pos3d::const_iterator i=ptos.begin();i!=ptos.end();i++)
      retval.push_back(Projection(*i));
    return retval;
  }
// Poligono Plano3d::Projection(const Poligono &pg) const
//   { return pg.Projection(*this); }

//! @brief Return an arbitrary point on the plane.
Pos3d Plano3d::Point(void) const
  { return Pos3d(cgp.point()); }

bool Plano3d::LadoPositivo(const Pos3d &p) const
  { return cgp.has_on_positive_side(p.ToCGAL()); }
bool Plano3d::LadoNegativo(const Pos3d &p) const
  { return cgp.has_on_negative_side(p.ToCGAL()); }

//! @brief Return true if the point is in the plane.
bool Plano3d::In(const Pos3d &p, const GEOM_FT &tol) const
  { 
    bool retval= false;
    if(cgp.has_on(p.ToCGAL()))
      retval= true;
    else if(dist(p)<=tol)
      retval= true;
    return retval;
  }

CGAL::Oriented_side Plano3d::ClassifyPoint(const Pos3d &p) const
  { return cgp.oriented_side(p.ToCGAL()); }

GEOM_FT Plano3d::dist(const Pos3d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brief Return the signed distance from the point.
GEOM_FT Plano3d::PseudoDist(const Pos3d &p) const
  {
    GEOM_FT retval= dist(p);
    if(LadoNegativo(p))
      return -retval;
    else
      return retval;
  }
//! @brief Return the signed squared distance from the point.
GEOM_FT Plano3d::PseudoDist2(const Pos3d &p) const
  {
    GEOM_FT retval= dist2(p);
    if(LadoNegativo(p))
      return -retval;
    else
      return retval;
  }

//! @brief Return the squared distance from the point.
GEOM_FT Plano3d::dist2(const Pos3d &p) const
  { return p.dist2(Projection(p)); }

//! @brief Returns the plane equation in general form: ax + by + cz + d = 0
GeneralEquationOfPlane Plano3d::getGeneralEquation(void) const
  { return GeneralEquationOfPlane(cgp.a(),cgp.b(),cgp.c(),cgp.d()); }

//! @brief Return the position of the centroid.
//! Any point in the plane can be its centroid.
Pos3d Plano3d::getCenterOfMass(void) const
  { return Point(); }

Plano3d::clasif_poligono Plano3d::ClasificaPoligono(const Poligono3d &pol) const
  {
    GeomObj::list_Pos3d lv= pol.ListaVertices();
    return ClassifyPoints(lv.begin(),lv.end());
  }

Plano3d FromCGAL(const CGPlane_3 &p)
  { return Plano3d(p); }

bool operator==(const Plano3d &p1,const Plano3d &p2)
  { return (p1.cgp == p2.cgp); }

void Plano3d::Print(std::ostream &os) const
  {
    os << "point: " << Point()
       << " normal: " << Normal()
       << std::endl;
  }

//! @brief Return the x coordinate of the point of the plane
//! such:
//! y = p.x()
//! z = p.y()
GEOM_FT Plano3d::x(const Pos2d &p) const
  { return getGeneralEquation().x(p); }

//! @brief Return the y coordinate of the point of the plane
//! such:
//! x = p.x()
//! z = p.y()
GEOM_FT Plano3d::y(const Pos2d &p) const
  { return getGeneralEquation().y(p); }

//! @brief Return the z coordinate of the point of the plane
//! such:
//! x = p.x()
//! y = p.y()
GEOM_FT Plano3d::z(const Pos2d &p) const
  { return getGeneralEquation().z(p); }

//! @brief Creates a Plano3d object from the its equation
//! in general form: general ax + by + cz + d = 0
void Plano3d::GeneralEquation(const GeneralEquationOfPlane &eq)
  { operator=(Plano3d(eq)); }

//! @brief Returns true if intesection exists.
bool Plano3d::Interseca(const Plano3d &p) const
  { return do_intersect(ToCGAL(),p.ToCGAL()); }

//! @brief Returns (if exists) la intersección con el plano que se pasa como parámetro.
Recta3d Plano3d::Interseccion(const Plano3d &p) const
  { return recta_interseccion(*this,p); }

// //! @brief Return (if exists) la intersección con el plano que se pasa como parámetro.
// Recta3d Plano3d::Interseccion(const Plano3d &p) const
//   {
//     const Recta3d retval= Interseccion(p);
//     if(!retval.exists())
//       std::cerr << "Intersection with plane doesn't exists: "
//                 << p << std::endl;
//     return retval;
//   }

//! @brief Return verdadero if exists la intersección con la recta que se pasa como parámetro.
bool Plano3d::Interseca(const Recta3d &r) const
  { return do_intersect(ToCGAL(),r.ToCGAL()); }

//! @brief Return (if exists) la intersección con la recta que se pasa como parámetro.
Pos3d Plano3d::Interseccion(const Recta3d &r) const
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(*this,r);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

// //! @brief Return (if exists) la intersección con la recta que se pasa como parámetro.
// Pos3d Plano3d::Interseccion(const Recta3d &r) const
//   {
//     const Pos3d retval= Interseccion(r);
//     if(!retval.exists())
//       std::cerr << "Intersection with line "
//                 << r << "doesn't exists." << std::endl;
//     return retval;
//   }

//! @brief Return verdadero if exists la intersección con la recta que se pasa como parámetro.
bool Plano3d::Interseca(const SemiRecta3d &sr) const
  { return do_intersect(ToCGAL(),sr.ToCGAL()); }

//! @brief Return (if exists) la intersección con la semirrecta que se pasa como parámetro.
Pos3d Plano3d::Interseccion(const SemiRecta3d &sr) const
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(*this,sr);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

//! @brief Return verdadero if exists la intersección con el segmento que se pasa como parámetro.
bool Plano3d::Interseca(const Segmento3d &sg) const
  { return do_intersect(ToCGAL(),sg.ToCGAL()); }

//! @brief Return (if exists) la intersección con la semirrecta que se pasa como parámetro.
Pos3d Plano3d::Interseccion(const Segmento3d &sg) const
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(*this,sg);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

// //! @brief Return (if exists) la intersección con la recta que se pasa como parámetro.
// Pos3d Plano3d::Interseccion(const SemiRecta3d &sr) const
//   {
//     const Pos3d retval= Interseccion(sr);
//     if(!retval.exists())
//       std::cerr << "Intersection with ray doesn't exists: "
//                 << sr << std::endl;
//     return retval;
//   }

//! @brief Return the trace on the XY plane.
Recta3d Plano3d::XYTrace(void) const
  { return Interseccion(PlanoXY3d); }

//! @brief Return the trace on the XZ plane.
Recta3d Plano3d::XZTrace(void) const
  { return Interseccion(PlanoXZ3d); }

//! @brief Return the trace on the YZ plane.
Recta3d Plano3d::YZTrace(void) const
  { return Interseccion(PlanoYZ3d); }

//! @brief Return the maximum slope line with respect to the XY plane.
Recta3d Plano3d::getMaximumSlopeLineXY(void) const
  {
    Recta3d retval;
    Recta3d trace= XYTrace();
    if(trace.exists())
      {
        Pos3d point(Point());
        Plano3d p(perpendicular(trace,point));
        retval= recta_interseccion(p,*this);
      }
    return retval;
  }

//! @brief Return the maximum slope line with respect to the XZ plane.
Recta3d Plano3d::getMaximumSlopeLineXZ(void) const
  {
    Recta3d retval;
    Recta3d trace= XZTrace();
    if(trace.exists())
      {
        Pos3d point(Point());
        Plano3d p(perpendicular(trace,point));
        retval= recta_interseccion(p,*this);
      }
    return retval;
  }

//! @brief Return the maximum slope line with respect to the YZ plane.
Recta3d Plano3d::getMaximumSlopeLineYZ(void) const
  {
    Recta3d retval;
    Recta3d trace= YZTrace();
    if(trace.exists())
      {
        Pos3d point(Point());
        Plano3d p(perpendicular(trace,point));
        retval= recta_interseccion(p,*this);
      }
    return retval;
  }

//! @brief Return the angle between this plane and the argument.
GEOM_FT Plano3d::Angulo(const Plano3d &p) const
  { return angulo(*this,p); }

//! @brief Return the angle between this plane and the argument.
GEOM_FT Plano3d::Angulo(const Vector3d &v) const
  { return angulo(*this,v); }

//! @brief Returns the slope angle with respect to the XY plane
GEOM_FT Plano3d::getSlopeAngleXY(void) const
  { return angulo(*this,PlanoXY3d); }

//! @brief Returns the slope angle with respect to the XZ plane
GEOM_FT Plano3d::getSlopeAngleXZ(void) const
  { return angulo(*this,PlanoXZ3d); }

//! @brief Returns the slope angle with respect to the YZ plane
GEOM_FT Plano3d::getSlopeAngleYZ(void) const
  { return angulo(*this,PlanoYZ3d); }

//! @brief Compute the plane that best suits the point cloud.
GEOM_FT Plano3d::AjusteMinimosCuadrados(const GeomObj3d::list_Pos3d &lp)
  {
    std::list<CGPoint_3> points;
    for(GeomObj3d::list_Pos3d::const_iterator i=lp.begin(); i!=lp.end();i++)
      points.push_back((*i).ToCGAL()); 
    GEOM_FT quality= linear_least_squares_fitting_3(points.begin(),points.end(),cgp,CGAL::Dimension_tag<0>());
    return quality;
  }

//! @brief Return the plane normal to r that passes through p.
Plano3d perpendicular(const Recta3d &r, const Pos3d &p)
  { return r.Perpendicular(p); }

//! @brief Recta intersección de dos planos.
Recta3d recta_interseccion(const Plano3d &p1, const Plano3d &p2)
  {
    Recta3d retval;
    GmGrupo3d tmp= interseccion(p1,p2);
    if(!tmp.empty())
      {
        const Recta3d *ptr_recta= dynamic_cast<const Recta3d *>(tmp.begin()->get_const_ptr());
        if(ptr_recta)
          retval= *ptr_recta;
      }
    else
      retval.setExists(false);
    return retval;
  }

//! @brief Intersección de tres planos.
Pos3d intersection_point(const Plano3d &p1, const Plano3d &p2, const Plano3d &p3)
  {
    Pos3d retval;
    GmGrupo3d tmp= interseccion(p1,p2);
    if(!tmp.empty())
      {
        const Recta3d *ptr_recta= dynamic_cast<const Recta3d *>(tmp.begin()->get_const_ptr());
        if(ptr_recta)
          retval= intersection_point(p3,*ptr_recta);
      }
    else
      retval.setExists(false);
    return retval;
  }

//! @brief Intersection of two planes.
GmGrupo3d interseccion(const Plano3d &p1, const Plano3d &p2)
  {
    GmGrupo3d retval;
    const auto p1_cg= p1.ToCGAL();
    const auto p2_cg= p2.ToCGAL();
    if(do_intersect(p1_cg,p2_cg))
      {
        const CGAL::Object result= CGAL::intersection(p1_cg,p2_cg);
        if(const CGRecta_3 *ri= CGAL::object_cast<CGRecta_3 >(&result))
	  {
	    const Recta3d r3d(*ri);
            retval.push_back(r3d);
	  }
        else
          {
            CGPlane_3 planoi;
            if(CGAL::assign(planoi, result))
              {
                std::cerr << __FUNCTION__
		          << "; the planes are the same." 
                          << std::endl;
              }
            else
              {
                std::cerr << __FUNCTION__
			  << "; unknown error." 
                          << std::endl;
              }
	  }
      }
    return retval;
  }

//! @brief Intersection of the a plane with an straight line.
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Recta3d &r)
  {
    GeomObj3d::list_Pos3d retval;
    if(do_intersect(p.ToCGAL(),r.ToCGAL()))
      {
        CGAL::Object result;
        CGPoint_3 ptoi;
        CGRecta_3 ri;
        result = CGAL::intersection(p.ToCGAL(),r.ToCGAL());
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos3d(ptoi));
        else
          if(CGAL::assign(ri, result))
            {
              std::cerr << __FUNCTION__
			<< "(Plano3d,Recta3d): the plane contains the line." 
                        << std::endl;
            }
          else
            {
              std::cerr << __FUNCTION__
			<< "(Plano3d,Recta3d): unknown error." 
                        << std::endl;
            }
      }
    return retval;
  }

//! @brief Return the intersection of the plane with the ray.
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const SemiRecta3d &sr)
  {
    GeomObj3d::list_Pos3d retval;
    if(do_intersect(p.ToCGAL(),sr.ToCGAL()))
      {
        CGAL::Object result;
        CGPoint_3 ptoi;
        CGRecta_3 ri;
        result = CGAL::intersection(p.ToCGAL(),sr.ToCGAL());
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos3d(ptoi));
        else
          if(CGAL::assign(ri, result))
            {
              std::cerr << __FUNCTION__
			<< "(Plano3d,SemiRecta3d): the plane contains the line." 
                   << std::endl;
            }
          else
            {
              std::cerr << __FUNCTION__
			<< "(Plano3d,SemiRecta3d): unknown error." 
                        << std::endl;
            }
      }
    // else
    //   std::cerr << "Doesn't itersect." << std::endl;
    return retval;    
  }

//! @brief Return the intersection of the ray with the plane.
GeomObj3d::list_Pos3d interseccion(const SemiRecta3d &sr, const Plano3d &p)
  { return interseccion(p,sr); }

//! @brief Return the intersection of the plane with the segment.
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Segmento3d &sg)
  {
    GeomObj3d::list_Pos3d retval;
    if(do_intersect(p.ToCGAL(),sg.ToCGAL()))
      {
        CGAL::Object result;
        CGPoint_3 ptoi;
        CGRecta_3 ri;
        result = CGAL::intersection(p.ToCGAL(),sg.ToCGAL());
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos3d(ptoi));
        else
          if(CGAL::assign(ri, result))
            {
              std::cerr << __FUNCTION__
			<< "(Plano3d,Segmento3d): the plane contains"
		        << " the segment." << std::endl;
            }
          else
            {
              std::cerr << __FUNCTION__
			<< "(Plano3d,Segmento3d): unknown error." 
                        << std::endl;
            }
      }
    // else
    //   std::cerr << "No intersecan." << std::endl;
    return retval;    
  }

//! @brief Return the intersection of the segment with the plane.
GeomObj3d::list_Pos3d interseccion(const Segmento3d &sg, const Plano3d &p)
  { return interseccion(p,sg); }

//! @brief Return the intersection(s) of the plane with the polyline.
GeomObj3d::list_Pos3d interseccion(const Plano3d &p, const Polilinea3d &pl)
  { return pl.getIntersection(p); }

//! @brief Return the intersection(s) of the polyline with the plane.
GeomObj3d::list_Pos3d interseccion(const Polilinea3d &pl, const Plano3d &p)
  { return pl.getIntersection(p); }

Pos3d intersection_point(const Plano3d &p, const Recta3d &r)
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(p,r);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

Pos3d intersection_point(const Recta3d &r, const Plano3d &p)
  { return intersection_point(p,r); }

Pos3d intersection_point(const Plano3d &p, const SemiRecta3d &sr)
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(p,sr);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }

Pos3d intersection_point(const SemiRecta3d &sr, const Plano3d &p)
  { return intersection_point(p,sr); }

Pos3d intersection_point(const Plano3d &p, const Segmento3d &sg)
  {
    Pos3d retval;
    GeomObj3d::list_Pos3d tmp= interseccion(p,sg);
    if(!tmp.empty())
      retval= *tmp.begin();
    else
      retval.setExists(false);
    return retval;
  }
Pos3d intersection_point(const Segmento3d &sg, const Plano3d &p)
  { return intersection_point(p,sg); }

GEOM_FT angulo(const Recta3d &r,const Plano3d &p)
  {
    GEOM_FT retval;
    const Recta3d rProj= p.Projection(r);
    if(rProj.exists())
      retval= angulo(r,rProj);
    else
      {
        retval= NAN;
        std::cerr << __FUNCTION__
		  << "; error when computing projection." << std::endl;
      }
    return retval;
  }

GEOM_FT angulo(const Plano3d &p,const Recta3d &r)
  { return angulo(r,p); }

GEOM_FT angulo(const Vector3d &v,const Plano3d &p)
  { return M_PI/2 - angulo(p.Normal(),v); }

GEOM_FT angulo(const Plano3d &p,const Vector3d &v)
  { return angulo(v,p); }

GEOM_FT angulo(const Plano3d &p1,const Plano3d &p2)
  {
    GEOM_FT retval= angulo(p1.Normal(),p2.Normal());
    return retval;
  }


GeomObj3d::list_Pos3d interseccion(const Recta3d &r, const Plano3d &p)
  { return interseccion(p,r); }

//! @brief Return the points of intersection between the planes.
GeomObj3d::list_Pos3d intersection_points(const std::deque<Plano3d> &planos)
  {
    GeomObj3d::list_Pos3d retval;
    const size_t sz= planos.size();
    for(size_t i=0;i<sz;i++)
      for(size_t j=i+1;j<sz;j++)
        for(size_t k=j+1;k<sz;k++)
	  {
            const Pos3d p= intersection_point(planos[i],planos[j],planos[k]);
            if(p.exists())
              retval.push_back(p);
          }
    return retval;
  }

//! @brief Return true if la recta es paralela al plano.
bool paralelos(const Plano3d &p, const Recta3d &r)
  { return(!do_intersect(p.ToCGAL(),r.ToCGAL())); }

//! @brief Return true if los planos son paralelos.
bool paralelos(const Plano3d &p1, const Plano3d &p2)
  { return(!do_intersect(p1.ToCGAL(),p2.ToCGAL())); }


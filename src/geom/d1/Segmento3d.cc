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
//Segmento3d.cc

#include "Segmento3d.h"

#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Pos3d.h"

//! @brief Constructor.
Segmento3d::Segmento3d(void): Linea3d(),cgseg(CGPoint_3(0,0,0),CGPoint_3(1,0,0)) {}

//! @brief Constructor.
Segmento3d::Segmento3d(const CGSegmento_3 &r)
  : Linea3d(), cgseg(r) {}

//! @brief Constructor.
Segmento3d::Segmento3d(const Pos3d &p1,const Pos3d &p2)
  : Linea3d(), cgseg(p1.ToCGAL(),p2.ToCGAL())
  {
    if(EsDegenerada())
      {
        std::clog << getClassName() << "::" << __FUNCTION__
		  << "; degenerated line, the points: "
             << p1 << " and " << p2 << " are the same." << std::endl;
      }
  }

//! @brief Constructor.
Segmento3d::Segmento3d(const Segmento3d &r)
  : Linea3d(),cgseg(r.cgseg) {}

//! @brief Operador asignación.
Segmento3d &Segmento3d::operator=(const Segmento3d &r)
  {
    Linea3d::operator=(r);
    cgseg= r.cgseg;
    return *this;
  }

GeomObj *Segmento3d::clon(void) const
  { return new Segmento3d(*this); }
GEOM_FT Segmento3d::GetMax(unsigned short int i) const
  { return std::max(Origen()(i),Destino()(i)); }
GEOM_FT Segmento3d::GetMin(unsigned short int i) const
  { return std::min(Origen()(i),Destino()(i)); }
Recta3d Segmento3d::RectaSoporte(void) const
  { return Recta3d(cgseg.supporting_line()); }
Pos3d Segmento3d::Origen(void) const
  { return Pos3d(cgseg.source()); }
Pos3d Segmento3d::Destino(void) const
  { return Pos3d(cgseg.target()); }
GEOM_FT Segmento3d::getSlope(void) const
  { return RectaSoporte().getSlope(); }
const Pos3d Segmento3d::Point(const int &i) const
  { return Pos3d(cgseg.point(i)); }

//! @brief Return a point of the line at a distance lambda from its origin.
Pos3d Segmento3d::PtoParametricas(const GEOM_FT &lambda) const
  { return Point(0)+lambda*VDir(); }

//! @brief Return the coordenada paramétrica que corresponde
//! a la coordenada natural se pasa como parámetro.
double Segmento3d::getParamCooNatural(const GEOM_FT &chi) const
  { return (chi+1.0)/2.0; }

//! @brief Return the point del segmento cuyas coordenada
//! natural se pasa como parámetro.
Pos3d Segmento3d::PtoCooNatural(const GEOM_FT &chi) const
  { return PtoParametricas(getParamCooNatural(chi)); }

inline bool Segmento3d::EsDegenerada(void) const
  { return cgseg.is_degenerate(); }
//! @brief Return true if the point is in the segment.
bool Segmento3d::In(const Pos3d &p, const double &tol) const
  { return cgseg.has_on(p.ToCGAL()); }

void Segmento3d::TwoPoints(const Pos3d &p1,const Pos3d &p2)
  { (*this)= Segmento3d(p1,p2); }

Dir3d Segmento3d::GetDir(void) const
  { return Dir3d(cgseg.direction()); }
Vector3d Segmento3d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Return el parámetro «lambda» tal que p= Origen()+lambda*VDir()
GEOM_FT Segmento3d::getLambda(const Pos3d &p) const
  {
    const Vector3d v(Origen(),p);
    const Vector3d dir(Normaliza(VDir()));
    return dot(v,dir);
  }

//! @brief Return el cuadrado de la distance from the point al segmento.
GEOM_FT Segmento3d::dist2(const Pos3d &p) const
  {
    const Recta3d r= RectaSoporte();
    const Pos3d proj= r.Projection(p);
    GEOM_FT retval= p.dist2(proj); //Ok if projected point inside segment.
    const Pos3d A= Origen();
    const Pos3d B= Destino();
    const GEOM_FT denom= (B.x()-A.x())*(B.x()-A.x())+(B.y()-A.y())*(B.y()-A.y())+(B.z()-A.z())*(B.z()-A.z());
    if(denom!=0)
      {
        const GEOM_FT u= ( (p.x()-A.x())*(B.x()-A.x()) + (p.y()-A.y())*(B.y()-A.y()) + (p.z()-A.z())*(B.z()-A.z()) )/denom;
        if(u<0.0) //Distancia al origen.
	  retval= p.dist2(A);
	else if(u>1.0) //Distancia al destino.
          retval= p.dist2(B);
      }
    return retval;
  }

//! @brief Return the distance from the point al segmento.
GEOM_FT Segmento3d::dist(const Pos3d &p) const
  { return sqrt(dist2(p)); }

bool Segmento3d::Paralelo(const Recta3d &r) const
  { return paralelas(RectaSoporte(),r); }
bool Segmento3d::Paralelo(const SemiRecta3d &sr) const
  { return paralelas(RectaSoporte(),sr); }
bool Segmento3d::Paralelo(const Segmento3d &r) const
  { return paralelas(RectaSoporte(),r.RectaSoporte()); }

//! @brief Return the length of the segment.
GEOM_FT Segmento3d::getLength(void) const
  { return Origen().dist(Destino()); }

Pos3d Segmento3d::getCenterOfMass(void) const
  {
    Pos3d retval= Origen();
    const Vector3d v= (Destino()-retval)/2;
    retval= retval+v;
    return retval;
  }

GeomObj3d::list_Pos3d Segmento3d::Interseccion(const Recta3d &r) const
//Return the point intersection de recta and segmento, if doesn't exists la
//intersection devuelve la lista vacía.
  {
    const Recta3d sop= RectaSoporte();
    GeomObj3d::list_Pos3d retval= sop.Interseccion(r);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //the intersection point is NOT on the segment.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }
//! @brief Return the point intersection de semirrecta and segmento, if
//! the intersection doesn't exists returns an empty list.
GeomObj3d::list_Pos3d Segmento3d::Interseccion(const SemiRecta3d &sr) const
  {
    const Recta3d sop= RectaSoporte();
    GeomObj3d::list_Pos3d retval= sr.Interseccion(sop);
    if(!retval.empty()) //Intersection exists.
      {
        const Pos3d &pint= *retval.begin();
        if(!In(pint)) //the intersection point is NOT on the segment.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

//! @brief Return the intersection of the line with the plane defined
//! by the equation coord_i=cte.
GeomObj3d::list_Pos3d Segmento3d::Interseccion(unsigned short int i, const double &d) const
  {
    GeomObj3d::list_Pos3d lp;
    lp= RectaSoporte().Interseccion(i,d);
    if(!lp.empty())
      {
        const Vector3d i_= VDir();
        const double l= RectaSoporte().getLambda(i,d,i_);
        if( (l<0.0) || (l>getLength()) )
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

GeomObj3d::list_Pos3d Segmento3d::Interseccion(const Segmento3d &sg2) const
//Return the point intersection entre segmentos, if doesn't exists la
//intersection devuelve la lista vacía.
  {
    const Recta3d sop= RectaSoporte();
    GeomObj3d::list_Pos3d retval= sg2.Interseccion(sop);
    if(!retval.empty()) //Intersection exists
      {
        const Pos3d &pint= *retval.begin(); //This point is on sg2 and on
	                                    // the recta soporte de sg1.
        if(!In(pint)) //the intersection point is NOT on sg1.
          retval.erase(retval.begin(),retval.end());
      }
    return retval;
  }

GEOM_FT dist(const Pos3d &p,const Segmento3d &r)
  { return sqrt_FT(dist2(r,p)); }

//! @brief Returns angle with vector.
GEOM_FT Segmento3d::Angulo(const Vector3d &v) const
  { return angulo(VDir(),v); }
//! @brief Returns angle with another line segment.
GEOM_FT Segmento3d::Angulo(const Segmento3d &s) const
  { return Angulo(s.VDir()); }
GEOM_FT angulo(const Segmento3d &r,const Vector3d &v)
  { return r.Angulo(v); }
//Moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Segmento3d::Ix(void) const
  { return 0.0; }
//Moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Segmento3d::Iy(void) const
  { return NAN; }
//Moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Segmento3d::Iz(void) const
  { return NAN; }
bool operator==(const Segmento3d &r1,const Segmento3d &r2)
  { return (r1.cgseg==r2.cgseg); }
void Segmento3d::Print(std::ostream &os) const
  { os << Origen() << " " << Destino(); }


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
//Segmento2d.cc

#include "Segmento2d.h"
#include <plotter.h>

#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/VectorPos2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"




//! @brief Constructor.
Segmento2d::Segmento2d(const Pos2d &p1,const Pos2d &p2)
  : Linea2d(), cgseg(p1.ToCGAL(),p2.ToCGAL())
  {
    if(verbosity>2 && EsDegenerada())
      {
        clog << getClassName() << "::" << __FUNCTION__
	     << "; degenerated line, the points: "
             << p1 << " and " << p2 << " are the same." << endl;
      }
  }
void Segmento2d::TwoPoints(const Pos2d &p1,const Pos2d &p2)
  { (*this)= Segmento2d(p1,p2); }

GeomObj *Segmento2d::clon(void) const
  { return new Segmento2d(*this); }

//! @brief Return the dirección del segmento.
Dir2d Segmento2d::GetDir(void) const
  { return Dir2d(cgseg.direction()); }

//! @brief Return el direction vector del segmento.
Vector2d Segmento2d::VDir(void) const
  { return GetDir().GetVector(); }

//! @brief Return el direction vector del segmento.
Vector2d Segmento2d::Normal(void) const
  { return VDir().Normal(); }

//! @brief Return el vector que une el origen con el extremo del segmento.
Vector2d Segmento2d::GetVector(void) const
  { return Destino()-Origen(); }

//! @brief Return el ángulo del segmento con el vector (0->2PI).
GEOM_FT Segmento2d::Angulo(const Vector2d &v) const
  { return angulo(VDir(),v); }

//! @brief Return el ángulo del segmento con el vector (-PI->0->PI).
GEOM_FT Segmento2d::AnguloSigno(const Vector2d &v) const
  { return anguloSigno(VDir(),v); }

//! @brief Return el ángulo del segmento con el vector (0->2PI).
GEOM_FT Segmento2d::Angulo(const Segmento2d &s) const
  { return Angulo(s.VDir()); }

//! @brief Return el ángulo del segmento con el vector (-PI->0->PI).
GEOM_FT Segmento2d::AnguloSigno(const Segmento2d &s) const
  { return AnguloSigno(s.VDir()); }


//! @brief Return el ángulo del segmento con el X axis.
GEOM_FT Segmento2d::XAxisAngle(void) const
  { return VDir().XAxisAngle(); }

//! @brief Return el ángulo del segmento con el Y axis.
GEOM_FT Segmento2d::YAxisAngle(void) const
  { return VDir().YAxisAngle(); }

GEOM_FT angulo(const Segmento2d &r,const Vector2d &v)
  { return r.Angulo(v); }

GEOM_FT angulo(const Vector2d &v, const Segmento2d &r)
  { return v.Angulo(r.VDir()); }

GEOM_FT Segmento2d::Longitud(void) const
  { return Origen().dist(Destino()); }

//! @brief Return the posición del centro de gravedad del segmento.
Pos2d Segmento2d::Cdg(void) const
  {
    Pos2d retval= Origen();
    const Vector2d v= (Destino()-retval)/2;
    retval= retval+v;
    return retval;
  }

//! @brief Return the recta perpendicular a r que pasa por p.
Recta2d Segmento2d::Perpendicular(const Pos2d &p) const
  { return RectaSoporte().Perpendicular(p); }

//! @brief Return the recta paralela a ésta que pasa por p.
Recta2d Segmento2d::Paralela(const Pos2d &p) const
  { return RectaSoporte().Paralela(p); }

//! @brief Return el segmento que resulta de aplicar a ésta el desplazamiento v.
Segmento2d Segmento2d::Offset(const Vector2d &v) const
  {
    const Pos2d p= Origen()+v;
    const Pos2d q= Destino()+v;
    return Segmento2d(p,q);
  }

//! @brief Return un segmento paralelo a éste a la distancia
//! que se pasa como parámetro. Si la distance es positiva,
//! el nuevo segmento quedará a la derecha de la anterior.
Segmento2d Segmento2d::Offset(const GEOM_FT &d) const
  {
    const Vector2d v= d*RectaSoporte().VersorDir();
    const Vector2d n(v.y(),-v.x());
    return Offset(n);
  }

//! @brief Return the mediatriz del segmento.
Recta2d Segmento2d::Mediatriz(void) const
  {
    const Pos2d p= Cdg();
    const Vector2d v= VDir().Perpendicular(CGAL::COUNTERCLOCKWISE);
    const Pos2d p2= p+100.0*v;
    return Recta2d(p,p2);
  }

//! Return true if the point is on the segment.
bool Segmento2d::In(const Pos2d &p, const double &tol) const
  {
    bool retval= cgseg.has_on(p.ToCGAL());
    if(!retval)
      {
        const Pos2d &O= Origen();
        const Pos2d &D= Origen();
        const double L= Longitud();
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


//! @brief Return el cuadrado de la distance from the point al segmento.
GEOM_FT Segmento2d::dist2(const Pos2d &p) const
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
        if(u<0.0) //Distancia al origen.
	  retval= p.dist2(A);
	else if(u>1.0) //Distancia al destino.
          retval= p.dist2(B);
      }
    return retval;

  }

//! @brief Return the distance from the point al segmento.
GEOM_FT Segmento2d::dist(const Pos2d &p) const
  { return sqrt(dist2(p)); }

//! @brief Return a point of the segment at a distance lambda from its origin.
Pos2d Segmento2d::PtoParametricas(const GEOM_FT &lambda) const
  { return Origen()+lambda*VDir().Normalizado(); }

//! @brief Return the coordenada paramétrica que corresponde
//! a la coordenada natural se pasa como parámetro.
double Segmento2d::getParamCooNatural(const GEOM_FT &chi) const
  { return (chi+1.0)/2.0; }

//! @brief Return the point del segmento cuyas coordenada
//! natural se pasa como parámetro.
Pos2d Segmento2d::PtoCooNatural(const GEOM_FT &chi) const
  { return PtoParametricas(getParamCooNatural(chi)); }

bool Segmento2d::Interseca(const Recta2d &r) const
  { return CGAL::do_intersect(r.cgr,cgseg); }
bool Segmento2d::Interseca(const SemiRecta2d &sr) const
  { return do_intersect(sr.cgsr,cgseg); }

//! @brief Return the intersección de la Linea con un plano coord_i=cte.
GeomObj2d::list_Pos2d Segmento2d::Interseccion(unsigned short int i, const double &d) const
  {
    GeomObj2d::list_Pos2d lp;
    lp= RectaSoporte().Interseccion(i,d);
    if(!lp.empty())
      {
        const Vector2d i_= VDir();
        const double l= RectaSoporte().getLambda(i,d,i_);
        if( (l<0.0) || (l>Longitud()) )
          lp.erase(lp.begin(),lp.end());
      }
    return lp;
  }

//! @brief Return the point intersección de recta and segmento, if not exists la
//! intersección devuelve la lista vacía.
GeomObj2d::list_Pos2d Segmento2d::Interseccion(const Recta2d &r) const
  {
    GeomObj2d::list_Pos2d retval;
    if(Interseca(r))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        CGSegmento_2 segi;
        result = CGAL::intersection(cgseg,r.cgr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else if(CGAL::assign(segi, result)) 
          retval.push_back(Cdg()); //Return el centro de ESTE.
        else
          {
            const GEOM_FT d1= r.dist2(Origen());
            const GEOM_FT d2= r.dist2(Destino());
            const GEOM_FT tol= Longitud()/1e4;
            if(d1<tol)
              retval.push_back(Origen());
            else if(d2<tol)
              retval.push_back(Destino());
            else
              cerr << "Segmento2d::Interseccion(Recta2d): unknown error." << endl
                   << "sg: " << *this << endl
                   << "r: " << r << endl
                   << "tol: " << tol << endl
                   << "d1: " << d1 << endl
                   << "d2: " << d2 << endl;
          }
      }
    return retval;
  }
//! @brief Return the point intersección de semirrecta and segmento, if not exists la
//! intersección devuelve la lista vacía.
GeomObj2d::list_Pos2d Segmento2d::Interseccion(const SemiRecta2d &sr) const
  {
    GeomObj2d::list_Pos2d retval;
    if(Interseca(sr))
      {
        CGAL::Object result;
        CGPoint_2 ptoi;
        result = CGAL::intersection(cgseg,sr.cgsr);
        if(CGAL::assign(ptoi, result))
          retval.push_back(Pos2d(ptoi));
        else
          {
            cerr << "Segmento2d::Interseccion(SemiRecta2d): unknown error." << endl
                 << "sg: " << *this << endl
                 << "sr: " << sr << endl;
          }
      }
    return retval;
  }

//! @brief Return the point intersección de ambos segmentos, if not exists la
//! intersección devuelve la lista vacía.
GeomObj2d::list_Pos2d Segmento2d::Interseccion(const Segmento2d &r2) const
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
    if(Interseca(r2))
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

GEOM_FT dist(const Pos2d &p,const Segmento2d &r)
  { return sqrt_FT(r.dist2(p)); }

//! @brief Return the points that results from the segment division.
//! @param num_partes: number of segments.
VectorPos2d Segmento2d::Divide(int num_partes) const
  { return VectorPos2d(Origen(),Destino(),num_partes); }

//! @brief Aplica a la recta la transformación que se
//! pasa como parámetro.
void Segmento2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d p1= trf2d.Transforma(Origen());
    const Pos2d p2= trf2d.Transforma(Destino());
    (*this)= Segmento2d(p1,p2);
  }

void Segmento2d::Print(std::ostream &os) const
  { os << Origen() << " " << Destino(); }
void Segmento2d::Plot(Plotter &plotter) const
  {
    const Pos2d p1= Origen();
    const Pos2d p2= Destino();
    plotter.fline(p1.x(),p1.y(),p2.x(),p2.y());
  }

//! Return the point de intersección del segmento con la recta, if exists.
Pos2d intersection_point(const Segmento2d &s, const Recta2d &r)
  {
    Pos2d retval;
    GeomObj2d::list_Pos2d tmp= interseccion(s,r);
    if(tmp.empty())
      retval.setExists(false);
    else
      retval= *tmp.begin();
     return retval;
  }

//! Return the point de intersección del segmento con la recta, if exists.
Pos2d intersection_point(const Recta2d &r, const Segmento2d &s)
  { return intersection_point(s,r); }

//! Return the point de intersección de los segmentos, if exists.
Pos2d intersection_point(const Segmento2d &s1, const Segmento2d &s2)
  {
    Pos2d retval;
    GeomObj2d::list_Pos2d tmp= interseccion(s1,s2);
    if(tmp.empty())
      retval.setExists(false);
    else
      retval= *tmp.begin();
    return retval;
  }

std::list<Segmento2d> sin_degenerados(const std::list<Segmento2d> &lista)
  {
    std::list<Segmento2d> retval;
    for(list<Segmento2d>::const_iterator i=lista.begin();i!=lista.end();i++)
      if(!(*i).EsDegenerada())
        retval.push_back(*i);
    return retval;
  }



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
//Recta3d.cc

#include "Recta3d.h"
#include "Recta2d.h"
#include "../pos_vec/Dir3d.h"
#include "../d2/Plano3d.h"




const Pos3d Recta3d::defaultOrg= Pos3d(0,0,0);
const Pos3d Recta3d::defaultDest= Pos3d(1,0,0);
const Vector3d defaultVDir= Vector3d(1,0,0);

Recta3d::Recta3d(void)
  : Linea3d(), cgr(defaultOrg.ToCGAL(),defaultDest.ToCGAL()){}
Recta3d::Recta3d(const CGRecta_3 &r)
  : Linea3d(),cgr(r) {}

Recta3d::Recta3d(const Pos3d &p1,const Pos3d &p2)
  : Linea3d(), cgr(p1.ToCGAL(),p2.ToCGAL())
  {
    if(cgr.is_degenerate())
      {
        std::clog << getClassName() << "::" << __FUNCTION__
	          << ": degenerated line, the points: "
             << p1 << " and " << p2 << " are the same." << std::endl;
      }
    const double d= p1.dist(p2);
    if(d<mchne_eps_dbl)
      std::cerr << getClassName() << "::" << __FUNCTION__
		<< "; ill defined line, the points: "
		<< p1 << " and " << p2 << " are too close d(p1,p2)= "
                << d << ".\n";
  }
Recta3d::Recta3d(const Pos3d &p,const Dir3d &dir)
  : Linea3d(), cgr(p.ToCGAL(),dir.ToCGAL()) {}

Recta3d::Recta3d(const Plano3d &p1,const Plano3d &p2)
  : Linea3d(), cgr()
  {
    const Recta3d tmp= recta_interseccion(p1,p2);
    if(tmp.exists())
      cgr= tmp.ToCGAL();
    else
      setExists(false);
  }

//! @brief Constructs the line from its parametric equation.
Recta3d::Recta3d(const RectaParametricas3d &param)
  : Linea3d(), cgr(defaultOrg.ToCGAL(),defaultDest.ToCGAL())
  { Parametricas(param); }

void Recta3d::TwoPoints(const Pos3d &p1,const Pos3d &p2)
  { (*this)= Recta3d(p1,p2); }

Dir3d Recta3d::GetDir(void) const
  { return Dir3d(cgr.direction()); }

//! @brief Return the direction vector.
Vector3d Recta3d::VDir(void) const
  { return Vector3d(cgr.to_vector()); }

double Recta3d::getLambda(unsigned short int i,const double &d,const Vector3d &i_) const
      { return (d-Point(0)(i))/i_(i);}

//! @brief Return the orthogonal projection onto the line.
Pos3d Recta3d::Projection(const Pos3d &p) const
  { return Pos3d(cgr.projection(p.ToCGAL())); }

//! @brief Return the projection onto the line.
Vector3d Recta3d::Projection(const Vector3d &v) const
  {
    const Vector3d d= VDir().Normalizado();
    return dot(v,d)*d;
  }

//! @brief Return the projection onto the XY plane.
Recta3d Recta3d::XY3DProjection(void) const
  { return PlanoXY3d.Projection(*this); }

//! @brief Return the projection onto the XZ plane.
Recta3d Recta3d::XZ3DProjection(void) const
  { return PlanoXZ3d.Projection(*this); }

//! @brief Return the projection onto the YZ plane.
Recta3d Recta3d::YZ3DProjection(void) const
  { return PlanoYZ3d.Projection(*this); }

//! @brief Return the projection onto the XY plane.
Recta2d Recta3d::XY2DProjection(void) const
  {
    Recta2d retval;
    Recta3d r3d= XY3DProjection();
    if(r3d.exists())
      {
        const Pos2d p1= r3d.Point(0).XY2DProjection();
        const Pos2d p2= r3d.Point(100).XY2DProjection();
        const double d= p1.dist(p2);
        if(d>mchne_eps_dbl)
          retval= Recta2d(p1,p2);
        else
	  retval.setExists(false);
      }
    return retval;
  }

//! @brief Return the projection onto the XZ plane.
Recta2d Recta3d::XZ2DProjection(void) const
  {
    Recta2d retval;
    Recta3d r3d= XZ3DProjection();
    if(r3d.exists())
      {
        const Pos2d p1= r3d.Point(0).XZ2DProjection();
        const Pos2d p2= r3d.Point(100).XZ2DProjection();
        const double d= p1.dist(p2);
        if(d>mchne_eps_dbl)
          retval= Recta2d(p1,p2);
        else
          retval.setExists(false);
      }
    return retval;
  }

//! @brief Return the projection onto the YZ plane.
Recta2d Recta3d::YZ2DProjection(void) const
  {
    Recta2d retval;
    Recta3d r3d= YZ3DProjection();
    if(r3d.exists())
      {
        const Pos2d p1= r3d.Point(0).YZ2DProjection();
        const Pos2d p2= r3d.Point(100).YZ2DProjection();
        const double d= p1.dist(p2);
        if(d>mchne_eps_dbl)
          retval= Recta2d(p1,p2);
        else
          retval.setExists(false);
      }
    return retval;
  }

//! brief Return el ángulo con el plano XY.
GEOM_FT Recta3d::getSlope(void) const
  { return angulo(*this,PlanoXY3d); }

bool Recta3d::Paralela(const Recta3d &r) const
  { return paralelas(GetDir(),r.GetDir()); }
Plano3d Recta3d::Perpendicular(const Pos3d &p) const
//Return el plano perpendicular a r que pasa por p.
  { return Plano3d(cgr.perpendicular_plane(p.ToCGAL())); }

GEOM_FT coo_interseccion(const GeomObj2d::list_Pos2d &int_a, const GeomObj2d::list_Pos2d &int_b,const size_t &coo,const double &tol)
  {
    Pos3d pint_a,pint_b;
    if(!int_a.empty()) pint_a= To3d(*int_a.begin(),coo+1);
    if(!int_b.empty()) pint_b= To3d(*int_b.begin(),coo+2);

    GEOM_FT retval=0.0;
    if((!int_a.empty()) && (!int_b.empty())) //Both projections intercepts.
      {
        if(fabs(pint_a(coo)-pint_b(coo))<tol)
          retval= (pint_a(coo)+pint_b(coo))/2;
        else
          {
            std::cerr << "coo_interseccion(int_a,int_b): Error al promediar la coordenada " << coo 
                 << " de la intersección. Los valores obtenidos: " << pint_a(coo) << " and " << pint_b(coo)
                 << " son muy diferentes." << std::endl;
          }
      }
    else
      if(!int_a.empty()) //First projection intercepts.
        retval= pint_a(coo);
      else
        if(!int_b.empty()) //Second projection intercepts.
          retval= pint_b(coo);
        else //None of the projections intercepts.
          {
            std::cerr << __FUNCTION__
	              << "; error when computing" << coo
		      << " coordinate of the intersection."
                      << std::endl;
          }
    return retval;
  }
//Return true if las rectas intersecan.
bool Recta3d::Interseca(const Recta3d &r2) const
  {
    if(!coplanarias(*this,r2)) return false; //No son coplanarias.
    if(colineales(*this,r2)) return true; //Son la misma.
    if(paralelas(*this,r2))
      return false; //Son distintas and paralelas.
    else
      return true;
  }

//! @brief Return the intersección de la Linea con un plano coord_i=cte.
GeomObj3d::list_Pos3d Recta3d::Interseccion(unsigned short int i, const double &d) const
  {
    GeomObj::list_Pos3d lp;
    unsigned short int j=i;
    j++;
    if(j>3) j=1;
    unsigned short int k=j;k++;
    if(k>3) k=1;
    Pos3d p;
    p.Set(i,d);
    const Vector3d i_= VDir();
    const Pos3d org(Point(0));
    if (fabs(i_(i))<1.0E-12) return lp;
    const double l= getLambda(i,d,i_);
    p.Set(j,org(j)+l*i_(j));
    p.Set(k,org(k)+l*i_(k));
    lp.push_back(p);
    return lp;
  }

//Return the point intersección con la recta r2, if not exists la
//intersección devuelve la lista vacía.
GeomObj3d::list_Pos3d Recta3d::Interseccion(const Recta3d &r2,const double &tol) const
  {
    GeomObj3d::list_Pos3d retval;
    if(!intersecan(*this,r2)) return retval;
    if(colineales(*this,r2))
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
		  << ": lines are the same, all its points belong"
	          << " to the intersection." << std::endl;
        return retval;
      }

    const double tol2= tol*tol;
    bool exists= true;

    const Recta2d r1_xy= (*this).XY2DProjection();
    const Recta2d r1_xz= (*this).XZ2DProjection();
    const Recta2d r1_yz= (*this).YZ2DProjection();

    const Recta2d r2_xy= r2.XY2DProjection();
    const Recta2d r2_xz= r2.XZ2DProjection();
    const Recta2d r2_yz= r2.YZ2DProjection();
    exists= (r1_xy.exists() && r1_xz.exists() && r1_yz.exists() && r2_xy.exists() && r2_xz.exists() && r2_yz.exists());
    if(!exists)
      std::cerr << getClassName() << "::" << __FUNCTION__
	        << "; error when computing projections." 
                << std::endl;

    const GeomObj2d::list_Pos2d int_xy= interseccion(r1_xy,r2_xy);
    const GeomObj2d::list_Pos2d int_xz= interseccion(r1_xz,r2_xz);
    const GeomObj2d::list_Pos2d int_yz= interseccion(r1_yz,r2_yz);

    const GEOM_FT x= coo_interseccion(int_xy,int_xz,1,tol);
    const GEOM_FT y= coo_interseccion(int_xy,int_yz,2,tol);
    const GEOM_FT z= coo_interseccion(int_xz,int_yz,3,tol);

    Pos3d pint(x,y,z);
    if((this->dist2(pint)>tol2) || (r2.dist2(pint))>tol2)
      {
        std::cerr << "interseccion(Recta3d,Recta3d): Error al calcular la intersección."
             << std::endl;
      }
    retval.push_back(pint);
    return retval;
  }

//! @brief Return el cuadrado de la distance from the point a la recta.
GEOM_FT Recta3d::dist(const Pos3d &p) const
  { return sqrt_FT(dist2(p)); }

//! @brier Print stuff.
void Recta3d::Print(std::ostream &os) const
  { os << PtoParametricas(0.0) << " " << PtoParametricas(100.0); }

//! @brief Return the distance from the point a la recta.
GEOM_FT dist(const Pos3d &p,const Recta3d &r)
  { return sqrt_FT(dist2(r,p)); }

bool colineales(const Recta3d &r1,const Recta3d &r2)
  {
    const Pos3d p1= r2.Point(0);
    const Pos3d p2= r2.Point(100);
    if( r1.In(p1) && r1.In(p2) )
      return true;
    else
      return false;
  }

bool coplanarias(const Recta3d &r1,const Recta3d &r2)
  {
    const Pos3d p1= r2.Point(0);
    const Pos3d p2= r2.Point(100);
    const Pos3d p3= r1.Point(0);
    const Pos3d p4= r1.Point(100);
    return coplanarios(p1,p2,p3,p4);
  }

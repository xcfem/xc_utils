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
//SectorCircular2d.cc

#include "SectorCircular2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include <plotter.h>

#include "boost/progress.hpp"


//! @brief Circular sector defined by three points p1->p2->p3.
SectorCircular2d SectorCircular2dThreepoints(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3)
  {
    const Circulo2d tmp= Circulo2d(p1,p2,p3);
    const double th1= tmp.getAngle(p1);
    const double th3= tmp.getAngle(p3);
    SectorCircular2d retval(tmp,th1,th3);
    const double alpha1= 0;
    const double alpha2= retval.getAngle(p2);
    const double alpha3= retval.getAngle(p3);
    if((alpha1>=alpha2) || (alpha3<=alpha2))
      {
	std::cerr << "Error al definir el sector circular: " << std::endl
                  << "  p1= " << p1 << "  alpha1= " << RadToDeg(alpha1) <<std::endl
                  << "  p2= " << p2 << "  alpha2= " << RadToDeg(alpha2) <<std::endl
                  << "  p3= " << p3 << "  alpha3= " << RadToDeg(alpha3) <<std::endl;
      }
    return retval;
  }

//! @brief Constructor por defecto.
SectorCircular2d::SectorCircular2d(void)
  : Circulo2d(), theta1(0), theta2(M_PI/2) {}

//! @brief Build the circle from its center and its radius.
SectorCircular2d::SectorCircular2d(const Circulo2d &c,const double &th1,const double &th2)
  : Circulo2d(c), theta1(th1), theta2(th2) 
  {
    if(theta1>theta2)
      theta1-= 2*M_PI;
  }

//! @brief Constructor de copia.
SectorCircular2d::SectorCircular2d(const SectorCircular2d &otro)
  : Circulo2d(otro), theta1(otro.theta1), theta2(otro.theta2) {}

//! @brief Operador asignacion.
SectorCircular2d &SectorCircular2d::operator=(const SectorCircular2d &p)
  {
    Circulo2d::operator=(p);
    theta1= p.theta1;
    theta2= p.theta2;
    return *this;
  }

//! @brief Constructor virtual.
Superficie2d *SectorCircular2d::clon(void) const
  { return new SectorCircular2d(*this); }


//! @brief Return the posición del centro de gravedad del sector circular.
Pos2d SectorCircular2d::getCenterOfMass(void) const
  {
    const GEOM_FT theta= getIncludedAngle()/2.0;
    const GEOM_FT lambda= 2.0/3.0*sin(theta)/theta;
    const Vector2d v= lambda*(PMed()-Centro());
    return Centro()+v;
  }

//! @brief Return the position of the arc centroid.
Pos2d SectorCircular2d::ArcCentroid(void) const
  {
    const GEOM_FT theta= getIncludedAngle()/2.0;
    const GEOM_FT lambda= sin(theta)/theta;
    const Vector2d v= lambda*(PMed()-Centro());
    return Centro()+v;
  }


//! @brief Return the point inicial del arco.
Pos2d SectorCircular2d::PInic(void) const
  { return Point(theta1); }

//! @brief Return the point final del arco.
Pos2d SectorCircular2d::PFin(void) const
  { return Point(theta2); }

//! @brief Return the point medio del arco.
Pos2d SectorCircular2d::PMed(void) const
  { return Point((theta1+theta2)/2); }

//! @brief Return the angle between the line from the center of the circle
//! to the point p and the line from the center of the circle to the sector
//! start point.
double SectorCircular2d::getAngle(const Pos2d &p) const
  { return Circulo2d::getAngle(p)-theta1; }

//! @brief Returns the parameter of the point in the arc (distance to the arc's first point measured over the arc)
double SectorCircular2d::getLambda(const Pos2d &p) const
  { return getAngle(p)*getRadius(); }


//! @brief Return the included angle.
double SectorCircular2d::getIncludedAngle(void) const
  { return theta2-theta1; }

//! @brief Return the length of the arc.
GEOM_FT SectorCircular2d::getArcLength(void) const
  { return double_to_FT(getIncludedAngle())*getRadius(); }

//! @brief Return the length of the circular sector.
GEOM_FT SectorCircular2d::getLength(void) const
  { return getArcLength()+ Diametro(); }

//! @brief Return the area of the circular sector.
GEOM_FT SectorCircular2d::getArea(void) const
  { return double_to_FT(getIncludedAngle())*getSquaredRadius()/2; }

//! @brief Return the maximum value of the i coordinate of the object points.
GEOM_FT SectorCircular2d::GetMax(unsigned short int i) const
  {
    std::cerr << "SectorCircular2d::GetMax() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el valor mínimo of the i coordinate of the object points.
GEOM_FT SectorCircular2d::GetMin(unsigned short int i) const
  {
    std::cerr << "SectorCircular2d::GetMin() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el moment of inertia del sector circular with respect to 
//! axis parallel to x que pasa por su centro.
GEOM_FT SectorCircular2d::Ix(void) const
  {
    std::cerr << "SectorCircular2d::Ix() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el moment of inertia del sector circular with respect to 
//! axis parallel to y que pasa por su centro.
GEOM_FT SectorCircular2d::Iy(void) const
  {
    std::cerr << "SectorCircular2d::Iy() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el moment of inertia del sector circular with respect to 
//! axis parallel to z que pasa por su centro.
GEOM_FT SectorCircular2d::Iz(void) const
  {
    std::cerr << "SectorCircular2d::Iz() not implemented." << std::endl;
    return 0;
  }

//! @brief Return el product of inertia del sector circular with respect to
//! the axis parallel to x e y que pasan por su centro.
GEOM_FT SectorCircular2d::Pxy(void) const
  {
    std::cerr << "SectorCircular2d::Pxy() not implemented." << std::endl;
    return 0;
  }

//! @brief Return true if the points lies inside the object.
bool SectorCircular2d::In(const Pos2d &p, const double &tol) const
  {
    if(Circulo2d::In(p,tol))
      {
        const double th= getAngle(p);
        return ((th>=theta1) && (th<=theta2));
      }
    else 
      return false;
  }

//! @brief Return n points equally spaced over the arc of the circular sector.
MatrizPos2d SectorCircular2d::getArcPoints(const size_t &n) const
  {
    MatrizPos2d retval;
    if(n>1)
      {
        retval= MatrizPos2d(n,1);
        if(n==2)
          {
            retval(1,1)= PInic(); //Initial and final points
            retval(n,1)= PFin();
          }
        else
          {
            const double delta_theta= getIncludedAngle()/(n-1);
            arc_points(theta1,delta_theta,retval);
          }
      }
    else
      std::cerr << getClassName() << "::" << __FUNCTION__
		<< "; the number of points must be greater than two."
		<< std::endl;
    return retval;
  }

void SectorCircular2d::Print(std::ostream &os) const
  {
    Circulo2d::Print(os);
    os << " theta1= " << theta1
       << " theta2= " << theta2;
  }
void SectorCircular2d::Plot(Plotter &plotter) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
              << "; not implemented." << std::endl;
    return;
  }

bool operator==(const SectorCircular2d &a,const SectorCircular2d &b)
  {
    if((const Circulo2d &)(a) == (const Circulo2d &)(b))
      return ( (a.Theta1() == b.Theta1()) && (a.Theta2() == b.Theta2()));
   else
     return false;
  }

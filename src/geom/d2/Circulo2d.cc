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
//Circulo2d.cc

#include "Circulo2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"
#include <plotter.h>

#include "xc_utils/src/geom/trf/Trf2d.h"




//! @brief Circulo definido por el radio y tangente a dos rectas.
//!
//! Basado en Mathematical elements for computer graphics
//! (Rogers and Adams) page 234 y siguientes.
Circulo2d Circulo2dRTT(const GEOM_FT &radio,const Recta2d &p,const Recta2d &l,const bool &left,const bool &far)
  {
    std::cerr << "Circulo2dRTT no está probada." << std::endl;
    const GeomObj2d::list_Pos2d points_int= p.Interseccion(l);
    if(points_int.size()<1)
      {
        std::cerr << "Circulo2dRTT, error; las rectas son paralelas." << std::endl;
        return Circulo2d();
      }
    else
      {
        const Pos2d &o= *points_int.begin();
        const Recta2d bisect= bisectriz(p,l);
        Ref2d2d ref(o,bisect.GetDir()); //Origen en la intersección, x axis según la recta bisectriz.
        const double theta= angulo(bisect,p); //Angulo entre la bisectriz y la recta p.
        const GEOM_FT sintheta= double_to_FT(sin(theta));
        const GEOM_FT costheta= double_to_FT(cos(theta));
	GEOM_FT h= 0,k= 0;
        if(left) //Círculos C2 o C3 de la figura.
          {
            if(far) //Círculo C2 de la figura.
              k= radio/costheta; //Coordenada y del centro expresada en locales.
            else //Círculo C3 de la figura.
              h= -radio/sintheta; //Coordenada x del centro expresada en locales.
          }
        else //Círculos C1 o C4 de la figura.
          {
            if(far) //Círculo C1 de la figura.
              h= -radio/sintheta; //Coordenada x del centro expresada en locales.
            else //Círculo C4 de la figura.
              k= -radio/costheta; //Coordenada y del centro expresada en locales.
          }
        const Pos2d centro= ref.GetPosGlobal(Pos2d(h,k)); //Centro del círculo.
        return Circulo2d(centro,radio);
      }
  }

//! @brief Construye el círculo a partir del centro y el radio.
Circulo2d::Circulo2d(const Pos2d &centro,const GEOM_FT &rad)
  : Superficie2d(), cgcirc(centro.ToCGAL(),rad*rad) {}

//! @brief Construye el círculo a partir del centro y el cuadrado del radio.
Circulo2d::Circulo2d(const GEOM_FT &rad2,const Pos2d &centro)
  : Superficie2d(), cgcirc(centro.ToCGAL(),rad2) {}

//! @brief Build the circle from three points.
//!
//! Basado en Mathematical elements for computer graphics
//! (Rogers and Adams) page 233.
Circulo2d::Circulo2d(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3)
  : Superficie2d(), cgcirc(p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL())
  {}
Pos2d Circulo2d::Centro(void) const
  { return Pos2d(cgcirc.center()); }

//! @brief Return the posición del centro de gravedad del círculo.
Pos2d Circulo2d::Cdg(void) const
  { return Centro(); }

//! @brief Return the point del círculo correspondiente al ángulo que se pasa como parámetro.
Pos2d Circulo2d::Point(const double &ang) const
  {
    const Pos2d o= Centro();
    const GEOM_FT r= Radio();
    const GEOM_FT x= o.x()+r*double_to_FT(cos(ang));
    const GEOM_FT y= o.y()+r*double_to_FT(sin(ang));
    return Pos2d(x,y);
  }

//! @brief Return el radio del círculo.
GEOM_FT Circulo2d::Radio(void) const
  { return sqrt_FT(Radio2()); }

//! @brief Return the angle between the line that passes through the center
//! and the p point and the x axis.
double Circulo2d::Angulo(const Pos2d &p) const
  {
    static const Vector2d horiz(1,0);
    Vector2d v1(Centro(),p);
    double retval= angulo(v1,horiz);
    return retval;
  }

//! @brief Return the longitud del círculo.
GEOM_FT Circulo2d::Longitud(void) const
  { return M_PI_FT*Diametro(); }
//! @brief Return el área del círculo.
GEOM_FT Circulo2d::Area(void) const
  { return M_PI_FT*Radio2(); }
//! @brief Return the maximum value of the i coordinate of the points of the circle.
GEOM_FT Circulo2d::GetMax(unsigned short int i) const
  { return Centro()(i)+Radio(); }
//! @brief Return el valor mínimo of the i coordinate of the points of the circle.
GEOM_FT Circulo2d::GetMin(unsigned short int i) const
  { return Centro()(i)-Radio(); }
//! @brief Return el moment of inertia del círculo with respect to 
//! axis parallel to x que pasa por su centro.
GEOM_FT Circulo2d::Ix(void) const
  { return M_PI_FT/4*sqr(Radio2()); }


//! @brief Return true if the point is on the circle.
bool Circulo2d::In(const Pos2d &p, const double &tol) const
  { return (cgcirc.has_on_positive_side(p.ToCGAL()) || cgcirc.has_on_boundary(p.ToCGAL())); }


//! @brief Return el ángulo comprendido por círculo (2*pi).
double Circulo2d::AnguloComprendido(void) const
  { return 2*M_PI; }

//! @brief Return n points equally espaces over the circle perimenter.
void Circulo2d::arc_points(const double &theta_inic,const double &delta_theta,MatrizPos2d &ptos) const
  {
    const GEOM_FT r= Radio();
    GEOM_FT x= r*double_to_FT(cos(theta_inic));
    GEOM_FT y= r*double_to_FT(sin(theta_inic));
    const size_t &n= ptos.size();
    const GEOM_FT cosdth= double_to_FT(cos(delta_theta));
    const GEOM_FT sindth= double_to_FT(sin(delta_theta));
    ptos(1,1)= Pos2d(x,y);
    for(size_t i= 2;i<=n;i++)
      {
        x= ptos(i-1,1).x()*cosdth-ptos(i-1,1).y()*sindth;
        y= ptos(i-1,1).x()*sindth+ptos(i-1,1).y()*cosdth;
        ptos(i,1)= Pos2d(x,y);
      }
    const Vector2d v_translac= Centro().VectorPos();
    for(size_t i= 1;i<=n;i++) //Traslación.
      ptos(i,1)= ptos(i,1)+v_translac;
    return;
  }

//! @brief Return n points equally spaced over the cicumference.
MatrizPos2d Circulo2d::getPointsOnPerimeter(const size_t &n,const double &theta_inic) const
  {
    MatrizPos2d retval;
    if(n>0)
      {
        retval= MatrizPos2d(n,1);
        const double delta_theta= 2*M_PI/n;
        arc_points(theta_inic,delta_theta,retval);
      }
    else
      std::cerr << getClassName() << "::" << __FUNCTION__
	        << "; ERROR: number of points must be greater than zero."
		<< std::endl;
    return retval;
  }

//! @brief Return el polígono de n lados inscrito en la circunferencia que forma el perímetro.
Poligono2d Circulo2d::getPoligonoInscrito(const size_t &n,const double &theta_inic) const
  {
    Poligono2d retval;
    const MatrizPos2d points= getPointsOnPerimeter(n,theta_inic);
    for(size_t i= 1;i<=n;i++)
      retval.push_back(points(i,1));
    return retval;
  }

//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Circulo2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d pA= trf2d.Transforma(Cdg());
    (*this)= Circulo2d(pA,Radio());
  }

void Circulo2d::Print(std::ostream &os) const
  {
    os << "x centro: " << Centro().x() 
       << " y centro: " << Centro().y()
       << " radio: " << Radio();
  }
void Circulo2d::Plot(Plotter &plotter) const
  {
    const Pos2d c= Centro();
    plotter.fcircle(c.x(),c.y(),Radio());
  }

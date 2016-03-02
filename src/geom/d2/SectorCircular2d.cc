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
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/T3Cmd.h"
#include "boost/progress.hpp"


//! @brief Sector circular definido por tres puntos p1->p2->p3.
SectorCircular2d SectorCircular2dTresPuntos(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3)
  {
    const Circulo2d tmp= Circulo2d(p1,p2,p3);
    const double th1= tmp.Angulo(p1);
    const double th3= tmp.Angulo(p3);
    SectorCircular2d retval(tmp,th1,th3);
    const double alpha1= 0;
    const double alpha2= retval.Angulo(p2);
    const double alpha3= retval.Angulo(p3);
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

//! @brief Constructor de copia.
//! @brief Construye el círculo a partir del centro y el radio.
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


bool SectorCircular2d::procesa_comando(CmdStatus &status)
  {
    const string &cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SectorCircular2d) Procesando comando: " << cmd << std::endl;
    static Pos2d c;
    if(cmd == "theta1")
      {
        theta1= interpretaDouble(status.GetString());
        return true;
      }
    else if(cmd == "theta2")
      {
        theta2= interpretaDouble(status.GetString());
        return true;
      }
    else if(cmd == "3p")
      {
        Pos2d p1,p2,p3;
        T3Cmd<Pos2d,Pos2d,Pos2d> tres_puntos(p1,"p1",p2,"p2",p3,"p3");
        tres_puntos.LeeCmd(status);
        *this= SectorCircular2dTresPuntos(p1,p2,p3);
        return true;
      }
    else
      return Circulo2d::procesa_comando(status);
  }

//! @brief Devuelve la posición del centro de gravedad del sector circular.
Pos2d SectorCircular2d::Cdg(void) const
  {
    std::cerr << "SectorCircular2d::Cdg() no implementada." << std::endl;
    return Centro();
  }

//! @brief Devuelve el punto inicial del arco.
Pos2d SectorCircular2d::PInic(void) const
  { return Punto(theta1); }

//! @brief Devuelve el punto final del arco.
Pos2d SectorCircular2d::PFin(void) const
  { return Punto(theta2); }

//! @brief Devuelve el punto medio del arco.
Pos2d SectorCircular2d::PMed(void) const
  { return Punto((theta1+theta2)/2); }

//! @brief Devuelve el ángulo que forma la dirección de la línea que
//! une el centro del círculo con el punto inicial del sector.
double SectorCircular2d::Angulo(const Pos2d &p) const
  { return Circulo2d::Angulo(p)-theta1; }

//! @brief Returns the parameter of the point in the arc (distance to the arc's first point measured over the arc)
double SectorCircular2d::getLambda(const Pos2d &p) const
  { return Angulo(p)*Radio(); }


//! @brief Devuelve el ángulo comprendido por el sector.
double SectorCircular2d::AnguloComprendido(void) const
  { return theta2-theta1; }

//! @brief Devuelve la longitud del arco del sector circular.
GEOM_FT SectorCircular2d::LongitudArco(void) const
  { return double_to_FT(AnguloComprendido())*Radio(); }

//! @brief Devuelve la longitud del sector circular.
GEOM_FT SectorCircular2d::Longitud(void) const
  { return LongitudArco()+ Diametro(); }

//! @brief Devuelve el área del sector circular.
GEOM_FT SectorCircular2d::Area(void) const
  { return double_to_FT(AnguloComprendido())*Radio2()/2; }

//! @brief Devuelve el valor máximo de la coordenada i de los puntos del sector circular.
GEOM_FT SectorCircular2d::GetMax(unsigned short int i) const
  {
    std::cerr << "SectorCircular2d::GetMax() no implementada." << std::endl;
    return 0;
  }
//! @brief Devuelve el valor mínimo de la coordenada i de los puntos del sector circular.
GEOM_FT SectorCircular2d::GetMin(unsigned short int i) const
  {
    std::cerr << "SectorCircular2d::GetMin() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve el momento de inercia del sector circular respecto al 
//! eje paralelo al x que pasa por su centro.
GEOM_FT SectorCircular2d::Ix(void) const
  {
    std::cerr << "SectorCircular2d::Ix() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve el momento de inercia del sector circular respecto al 
//! eje paralelo al y que pasa por su centro.
GEOM_FT SectorCircular2d::Iy(void) const
  {
    std::cerr << "SectorCircular2d::Iy() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve el momento de inercia del sector circular respecto al 
//! eje paralelo al z que pasa por su centro.
GEOM_FT SectorCircular2d::Iz(void) const
  {
    std::cerr << "SectorCircular2d::Iz() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve el producto de inercia del sector circular respecto a
//! los ejes paralelos a x e y que pasan por su centro.
GEOM_FT SectorCircular2d::Pxy(void) const
  {
    std::cerr << "SectorCircular2d::Pxy() no implementada." << std::endl;
    return 0;
  }

//! @brief Devuelve verdadero si el punto est'a sobre el sector circular.
bool SectorCircular2d::In(const Pos2d &p, const double &tol) const
  {
    if(Circulo2d::In(p,tol))
      {
        const double th= Angulo(p);
        return ((th>=theta1) && (th<=theta2));
      }
    else 
      return false;
  }

//! @brief Devuelve n puntos equiespaciados sobre el arco del sector circular.
MatrizPos2d SectorCircular2d::PuntosArco(const size_t &n) const
  {
    MatrizPos2d retval;
    if(n>1)
      {
        retval= MatrizPos2d(n,1);
        if(n==2)
          {
            retval(1,1)= PInic(); //Puntos inicial y final
            retval(n,1)= PFin();
          }
        else
          {
            const double delta_theta= AnguloComprendido()/(n-1);
            puntos_arco(theta1,delta_theta,retval);
          }
      }
    else
      std::cerr << "SectorCircular2d::Puntos; el número de puntos ha de ser mayor o igual a dos." << std::endl;
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
    std::cerr << "SectorCircular2d::Plot(plotter) no implementada." << std::endl;
    return;
  }

bool operator==(const SectorCircular2d &a,const SectorCircular2d &b)
  {
    if((const Circulo2d &)(a) == (const Circulo2d &)(b))
      return ( (a.Theta1() == b.Theta1()) && (a.Theta2() == b.Theta2()));
   else
     return false;
  }

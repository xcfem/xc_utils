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
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/T3Cmd.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/geom/trf/Trf2d.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"


//! @brief Circulo definido por el radio y tangente a dos rectas.
//!
//! Basado en Mathematical elements for computer graphics
//! (Rogers and Adams) página 234 y siguientes.
Circulo2d Circulo2dRTT(const GEOM_FT &radio,const Recta2d &p,const Recta2d &l,const bool &left,const bool &far)
  {
    std::cerr << "Circulo2dRTT no está probada." << std::endl;
    const GeomObj2d::list_Pos2d ptos_int= p.Interseccion(l);
    if(ptos_int.size()<1)
      {
        std::cerr << "Circulo2dRTT, error; las rectas son paralelas." << std::endl;
        return Circulo2d();
      }
    else
      {
        const Pos2d &o= *ptos_int.begin();
        const Recta2d bisect= bisectriz(p,l);
        Ref2d2d ref(o,bisect.GetDir()); //Origen en la intersección, eje x según la recta bisectriz.
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


bool Circulo2d::procesa_comando(CmdStatus &status)
  {
    const string &cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(Circulo2d) Procesando comando: " << cmd << std::endl;
    if(cmd == "centro")
      {
        Pos2d c;
        c.LeeCmd(status);
        const GEOM_FT r2= Radio2();
        *this= Circulo2d(r2,c);
        return true;
      }
    else if(cmd == "radio")
      {
        const Pos2d c= Centro();
        const GEOM_FT r= double_to_FT(interpretaDouble(status.GetString()));
        *this= Circulo2d(r*r,c);
        return true;
      }
    else if(cmd == "3p")
      {
        Pos2d p1,p2,p3;
        T3Cmd<Pos2d,Pos2d,Pos2d> tres_puntos(p1,"p1",p2,"p2",p3,"p3");
        tres_puntos.LeeCmd(status);
        *this= Circulo2d(p1,p2,p3);
        return true;
      }
    else
      return Superficie2d::procesa_comando(status);
  }

//! @brief Construye el círculo a partir del centro y el radio.
Circulo2d::Circulo2d(const Pos2d &centro,const GEOM_FT &rad)
  : Superficie2d(), cgcirc(centro.ToCGAL(),rad*rad) {}

//! @brief Construye el círculo a partir del centro y el cuadrado del radio.
Circulo2d::Circulo2d(const GEOM_FT &rad2,const Pos2d &centro)
  : Superficie2d(), cgcirc(centro.ToCGAL(),rad2) {}

//! @brief Construye el círculo a partir de tres puntos.
//!
//! Basado en Mathematical elements for computer graphics
//! (Rogers and Adams) página 233.
Circulo2d::Circulo2d(const Pos2d &p1,const Pos2d &p2,const Pos2d &p3)
  : Superficie2d(), cgcirc(p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL())
  {}
Pos2d Circulo2d::Centro(void) const
  { return Pos2d(cgcirc.center()); }

//! @brief Devuelve la posición del centro de gravedad del círculo.
Pos2d Circulo2d::Cdg(void) const
  { return Centro(); }

//! @brief Devuelve el punto del círculo correspondiente al ángulo que se pasa como parámetro.
Pos2d Circulo2d::Punto(const double &ang) const
  {
    const Pos2d o= Centro();
    const GEOM_FT r= Radio();
    const GEOM_FT x= o.x()+r*double_to_FT(cos(ang));
    const GEOM_FT y= o.y()+r*double_to_FT(sin(ang));
    return Pos2d(x,y);
  }

//! @brief Devuelve el radio del círculo.
GEOM_FT Circulo2d::Radio(void) const
  { return sqrt_FT(Radio2()); }

//! @brief Devuelve el ángulo que forma la dirección de la línea que
//! une el centro del círculo con el punto p con la dirección del eje x.
double Circulo2d::Angulo(const Pos2d &p) const
  {
    static const Vector2d horiz(1,0);
    Vector2d v1(Centro(),p);
    double retval= angulo(v1,horiz);
    return retval;
  }

//! @brief Devuelve la longitud del círculo.
GEOM_FT Circulo2d::Longitud(void) const
  { return M_PI_FT*Diametro(); }
//! @brief Devuelve el área del círculo.
GEOM_FT Circulo2d::Area(void) const
  { return M_PI_FT*Radio2(); }
//! @brief Devuelve el valor máximo de la coordenada i de los puntos del círculo.
GEOM_FT Circulo2d::GetMax(unsigned short int i) const
  { return Centro()(i)+Radio(); }
//! @brief Devuelve el valor mínimo de la coordenada i de los puntos del círculo.
GEOM_FT Circulo2d::GetMin(unsigned short int i) const
  { return Centro()(i)-Radio(); }
//! @brief Devuelve el momento de inercia del círculo respecto al 
//! eje paralelo al x que pasa por su centro.
GEOM_FT Circulo2d::Ix(void) const
  { return M_PI_FT/4*sqr(Radio2()); }


//! @brief Devuelve verdadero si el punto est'a sobre el circulo.
bool Circulo2d::In(const Pos2d &p, const double &tol) const
  { return (cgcirc.has_on_positive_side(p.ToCGAL()) || cgcirc.has_on_boundary(p.ToCGAL())); }


//! @brief Devuelve el ángulo comprendido por círculo (2*pi).
double Circulo2d::AnguloComprendido(void) const
  { return 2*M_PI; }

//! @brief Devuelve n puntos equiespaciados sobre el círculo.
void Circulo2d::puntos_arco(const double &theta_inic,const double &delta_theta,MatrizPos2d &ptos) const
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

//! @brief Devuelve n puntos equiespaciados sobre la circunferencia que forma el perímetro.
MatrizPos2d Circulo2d::PuntosPerimetro(const size_t &n,const double &theta_inic) const
  {
    MatrizPos2d retval;
    if(n>0)
      {
        retval= MatrizPos2d(n,1);
        const double delta_theta= 2*M_PI/n;
        puntos_arco(theta_inic,delta_theta,retval);
      }
    else
      std::cerr << "ERROR en Circulo2d::Puntos; el número de puntos ha de ser mayor que cero." << std::endl;
    return retval;
  }

//! @brief Devuelve el polígono de n lados inscrito en la circunferencia que forma el perímetro.
Poligono2d Circulo2d::getPoligonoInscrito(const size_t &n,const double &theta_inic) const
  {
    Poligono2d retval;
    const MatrizPos2d puntos= PuntosPerimetro(n,theta_inic);
    for(size_t i= 1;i<=n;i++)
      retval.push_back(puntos(i,1));
    return retval;
  }

//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Circulo2d::Transforma(const Trf2d &trf2d)
  {
    const Pos2d pA= trf2d.Transforma(Cdg());
    (*this)= Circulo2d(pA,Radio());
  }

//! @brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro.
any_const_ptr Circulo2d::GetProp(const std::string &cod) const
  {
    if(cod=="getPoligonoInscrito")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const double thetaI= convert_to_double(InterpreteRPN::Pila().Pop());
            const size_t nl= convert_to_size_t(InterpreteRPN::Pila().Pop());
            tmp_gp_pol2d= getPoligonoInscrito(nl,thetaI);
            return any_const_ptr(tmp_gp_pol2d);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
            return any_const_ptr();
          }
      }
    else
      return Superficie2d::GetProp(cod);
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

void Circulo2d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    std::cerr << "Circulo2d::SalvaCmd no implementada" << std::endl;
  }

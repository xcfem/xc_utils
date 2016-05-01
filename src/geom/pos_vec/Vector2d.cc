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
//Vector2d.cc

#include "Vector2d.h"
#include "Pos2d.h"
#include "Dir2d.h"
#include <plotter.h>
#include "xc_basic/src/matrices/giros.h"
#include "xc_utils/src/geom/matriz_FT.h"




// Vector2d::Vector2d(const double &x,const double &y)
//   : ProtoGeom(), cgvct(Vector_2_from_doubles(x,y)) {}
Vector2d::Vector2d(const GEOM_FT &x,const GEOM_FT &y)
  : ProtoGeom(), cgvct(x,y) {}

Vector2d::Vector2d(const matriz_FT &m)
  : cgvct(0,0)
  {
    assert(m.getNumFilas()==2);
    assert(m.getNumCols()==1); 
    cgvct= CGVector_2(m(1),m(2));
  }
Vector2d::Vector2d(const Pos2d &p1,const Pos2d &p2)
  : ProtoGeom(), cgvct(p1.ToCGAL(),p2.ToCGAL()) {}

bool Vector2d::Nulo(void) const
  { return ((*this)==VectorNulo2d); }
void Vector2d::SetX(const GEOM_FT &vx)
  { cgvct= CGVector_2(vx,y()); }
void Vector2d::SetY(const GEOM_FT &vy)
  { cgvct= CGVector_2(x(),vy); }
void Vector2d::Set(unsigned short int i,const GEOM_FT &v)
  {
    switch(i)
      {
      case 1:
        SetX(v);
        break;
      case 2:
        SetY(v);
        break;
      default:
	std::cerr << "Se esperaba que el índice fuera 1, 2 ó 3." << std::endl;
        break;
      }
  }

//! @brief Devuelve la suma de los vectores.
Vector2d Vector2d::operator+(const Vector2d &v) const
  {  return Vector2d(ToCGAL()+v.ToCGAL()); }

//! @brief Devuelve la resta de los vectores.
Vector2d Vector2d::operator-(const Vector2d &v) const
  { return Vector2d(ToCGAL()-v.ToCGAL()); }

//! @brief Devuelve el producto del vector por el escalar.
Vector2d Vector2d::operator*(const GEOM_FT &d) const
  { return Vector2d(ToCGAL()*d); }

//! @brief Devuelve el producto del vector por el inverso del escalar.
Vector2d Vector2d::operator/(const GEOM_FT &d) const
  { return Vector2d(ToCGAL()*(1/d)); }

matriz_FT Vector2d::GetMatriz(void) const
  {
    matriz_FT retval(2,1,0);
    retval(1)= x(); retval(2)= y();
    return retval;
  }

//! @brief Devuelve el vector normal a éste.
Vector2d Vector2d::Normal(void) const
  { return Vector2d(y(),-x()); }

Dir2d Vector2d::Direccion(void) const
  { return Dir2d(*this); }

//! @brief Devuelve el ángulo que forma con el vector
//! que se pasa como parámetro.
GEOM_FT Vector2d::AnguloSigno(const Vector2d &v) const
  { return anguloSigno(*this,v); }

//! @brief Devuelve el ángulo que forma con el vector
//! que se pasa como parámetro (0->360).
GEOM_FT Vector2d::Angulo(const Vector2d &v) const
  { return angulo(*this,v); }

GEOM_FT Vector2d::AnguloEjeX(void) const
  {
    double retval= atan2(y(),x());
    if(retval<0)
      retval+= 2*M_PI;
    return retval;
  }

GEOM_FT Vector2d::AnguloEjeY(void) const
  { return M_PI/2.0-AnguloEjeX(); }


bool Vector2d::EsUnitario(const double &tol) const
  {
    const GEOM_FT md2= GetModulus2();
    if((md2-1)>tol)
      return false;
    else
      return true;
  }

//! @brief Devuelve el módulo del vector.
GEOM_FT Vector2d::GetModulus(void) const
  { return sqrt_FT(GetModulus2()); }

//! @brief Producto del vector por una matriz.
matriz_FT operator*(const matriz_FT &m,const Vector2d &v)
  { return m*v.GetMatriz(); }

//! @brief Producto escalar.
GEOM_FT Vector2d::GetDot(const matriz_FT &m) const
  {
    assert(m.getNumFilas()==2);
    assert(m.getNumCols()==1);
    return (x()*m(1)+y()*m(2));
  }

//! @brief Devuelve el producto del vector por la matriz.
GEOM_FT dot(const Vector2d &v1, const matriz_FT &m)
  { return v1.GetDot(m); }

//! @brief Devuelve el producto de la matriz por el vector.
GEOM_FT dot(const matriz_FT &m, const Vector2d &v1)
  { return v1.GetDot(m); }


// void Vector2d::Gira(const GEOM_FT &ang_rad)
//   { (*this)= GetGirado(ang_rad); }

// Vector2d Vector2d::GetGirado(const double &ang_rad) const
//   { 
//     Vector2d retval;
//     CGTrfAfin_2 giro(CGAL::ROTATION,sin(ang_rad),cos(ang_rad));
//     retval.cgvct = giro(cgvct);
//     return retval;
//   }
Vector2d Vector2d::Perpendicular(const Orientacion &o) const
  {
    Vector2d retval;
    retval.cgvct = cgvct.perpendicular(o);
    return retval;
  }
//! @brief Devuelve un vector que resulta de proyectar v
//! sobre la dirección perpendicular a ESTE vector.
//! Se emplea para ortogonalizar una base.
Vector2d Vector2d::Perpendicular(const Vector2d &v) const
  {
    Vector2d retval(0,0);
    if( Nulo() || v.Nulo() )
      {
	std::cerr << "Vector2d::Perpendicular; Uno de los vectores: "
                  << *this << " o " << v << " es nulo."
                  << " La operación no tiene sentido, se devuelve un vector nulo." << std::endl;
      }
    else
      if(paralelos(*this,v))
        {
	  std::cerr << "Vector2d::Perpendicular; el vector :" << v
                    << " es paralelo a éste: " << *this
                    << ", se devuelve un vector nulo." << std::endl;
        }
      else
        {
          const GEOM_FT alpha= -(dot(v,(*this))/GetModulus2());
          retval= v+alpha*(*this);
        }
    return retval;
  }
void Vector2d::Print(std::ostream &stream) const
  {
    stream << "[[" << x() << "]["
           << y() << "]]";
  }
void Vector2d::Plot(Plotter &plotter) const
  {
    plotter.fline(0,0,x(),y()); //Dibuja una línea.
    plotter.fmarker(x(),y(),7,4.0); //Con un triángulo en el extremo.
  }
std::ostream &operator<<(std::ostream &stream,const Vector2d &n)
  {
    n.Print(stream);
    return stream;
  }
bool colineales(const Vector2d &v1,const Vector2d &v2)
  {
    Pos2d p1= Origen2d + v1;
    Pos2d p2= Origen2d + v2;
    return colineales(Origen2d,p1,p2);
  }
bool paralelos(const Vector2d &v1,const Vector2d &v2)
  { return paralelas(v1.Direccion(),v2.Direccion()); } 

double anguloSigno(const Vector2d &v1,const Vector2d &v2)
  {
    if( v1.Nulo() || v2.Nulo() )
      {
	std::clog << "angulo(Vector2d,Vector2d) Uno de los vectores: v1= "
                  << v1 << " o v2= " << v2 << " es nulo. Se devuelve ángulo cero." << std::endl;
        return 0.0;
      }
    const GEOM_FT prod_mod= sqrt_FT(v1.GetModulus2()*v2.GetModulus2());
    const GEOM_FT prod_escalar= dot(v1,v2);
    const GEOM_FT coseno= prod_escalar/prod_mod;
    const GEOM_FT seno= -(v1.x()*v2.y()-v1.y()*v2.x())/prod_mod;
    return atan2(seno,coseno);
  }

double angulo(const Vector2d &v1,const Vector2d &v2)
  {
    double retval= anguloSigno(v1,v2);
    if(retval<0)
      retval+= 2*M_PI;
    return retval;
  }

matriz_FT prod_tensor(const Vector2d &u,const Vector2d &v)
  { return prod_tensor(u.GetMatriz(),v.GetMatriz()); }
matriz_FT operator&(const Vector2d &u,const Vector2d &v)
  { return prod_tensor(u,v); }







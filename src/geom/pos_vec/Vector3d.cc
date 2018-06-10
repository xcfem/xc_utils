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
//Vector3d.cc

#include "Vector3d.h"
#include "Pos3d.h"
#include "Dir3d.h"

#include "xc_utils/src/geom/matriz_FT.h"
#include "xc_basic/src/matrices/op_tensor.h"
//#include "Inventor/SbVec3f.h"



// Vector3d::Vector3d(const double &x,const double &y,const double &z)
//   : cgvct(Vector_3_from_doubles(x,y,z)) {}
Vector3d::Vector3d(const GEOM_FT &x,const GEOM_FT &y,const GEOM_FT &z)
  : cgvct(x,y,z) {}

Vector3d::Vector3d(const matriz_FT &m)
  : cgvct(0,0,0)
  {
    assert(m.getNumberOfRows()==3);
    assert(m.getNumberOfColumns()==1); 
    cgvct= CGVector_3(m(1),m(2),m(3));
  }
Vector3d::Vector3d(const Pos3d &p1,const Pos3d &p2)
  : cgvct(p1.ToCGAL(),p2.ToCGAL()) {}

bool Vector3d::Nulo(void) const
  { return ((*this)==VectorNulo3d); }
matriz_FT Vector3d::GetMatriz(void) const
  //Return el column vector.
  {
    matriz_FT retval(3,1,0);
    retval(1)= x(); retval(2)= y(); retval(3)= z();
    return retval;
  }
Dir3d Vector3d::Direccion(void) const
  { return Dir3d(*this); }

bool Vector3d::EsUnitario(const double &tol) const
  {
    const GEOM_FT md2= GetModulus2();
    if((md2-1)>tol)
      return false;
    else
      return true;
  }

//! @brief Return el vector normalizado.
Vector3d Vector3d::Normalizado(void) const
  {
    Vector3d retval(*this);
    const double m= GetModulus();
    if(m!=0.0)
      retval= retval/m;
    return retval; }

//! @brief Normaliza el vector.
void Vector3d::Normaliza(void)
  { operator=(this->Normalizado()); }

void Vector3d::SetX(const GEOM_FT &vx)
  { cgvct= CGVector_3(vx,y(),z()); }
void Vector3d::SetY(const GEOM_FT &vy)
  { cgvct= CGVector_3(x(),vy,z()); }
void Vector3d::SetZ(const GEOM_FT &vz)
  { cgvct= CGVector_3(x(),y(),vz); }
void Vector3d::Set(unsigned short int i,const GEOM_FT &v)
  {
    switch(i)
      {
      case 1:
        SetX(v);
        break;
      case 2:
        SetY(v);
        break;
      case 3:
        SetZ(v);
        break;
      default:
	std::cerr << "Se esperaba que el índice fuera 1, 2 ó 3." << std::endl;
        break;
      }
  }

//! @brief Return el módulo del vector.
GEOM_FT Vector3d::GetModulus(void) const
  { return sqrt_FT(GetModulus2()); }

//! @brief Return el producto escalar.
GEOM_FT Vector3d::GetDot(const Vector3d &v) const
  { return (x()*v.x()+y()*v.y()+z()*v.z()); }

//! @brief Return el producto por la matriz.
GEOM_FT Vector3d::GetDot(const matriz_FT &m) const
  {
    assert(m.getNumberOfRows()==3);
    assert(m.getNumberOfColumns()==3);
    return (x()*m(1)+y()*m(2)+z()*m(3));
  }

//! @brief Return el producto vectorial.
Vector3d Vector3d::getCross(const Vector3d &v) const
  { return Vector3d(cross_product(ToCGAL(),v.ToCGAL())); }

//! @brief Producto del vector por una matriz.
matriz_FT operator*(const matriz_FT &m,const Vector3d &v)
  { return m*v.GetMatriz(); }

Vector3d &Vector3d::operator+=(const Vector3d &v)
  {
    (*this)= (*this)+v;
    return *this;
  }

Vector3d &Vector3d::operator-=(const Vector3d &v)
  {
    (*this)= (*this)-v;
    return *this;
  }

//! @brief Return la suma de los vectores.
Vector3d Vector3d::operator+(const Vector3d &v) const
  {  return Vector3d(ToCGAL()+v.ToCGAL()); }

//! @brief Return la resta de los vectores.
Vector3d Vector3d::operator-(const Vector3d &v) const
  { return Vector3d(ToCGAL()-v.ToCGAL()); }

//! @brief Return el producto del vector por el escalar.
Vector3d Vector3d::operator*(const GEOM_FT &d) const
  { return Vector3d(ToCGAL()*d); }

//! @brief Return el producto del vector por el inverso del escalar.
Vector3d Vector3d::operator/(const GEOM_FT &d) const
  { return Vector3d(ToCGAL()*(1/d)); }

//! @brief Return the vector obtained from projecting v
//! onto the perpendicular direction to this vector.
//! Used to orthogonalize a base.
Vector3d Vector3d::Perpendicular(const Vector3d &v) const
  {
    Vector3d retval(0,0,0);
    if( Nulo() || v.Nulo() )
      {
	std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; One of the vectors: "
                  << *this << " o " << v << " es nulo."
                  << " La operación no tiene sentido, se devuelve un vector nulo." << std::endl;
      }
    else
      if(paralelos(*this,v))
        {
	  std::cerr << "Vector3d::Perpendicular; el vector :" << v
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

//! @brief Return the angle between this vector and the argument.
GEOM_FT Vector3d::getAngle(const Vector3d &v) const
  {
    GEOM_FT retval= 0;
    //XXX Modify by splitting in "getAngle" and "getSignedAngle"
    //como en Vector2d.
    if( Nulo() || v.Nulo() )
      {
	std::clog << getClassName() << "::" << __FUNCTION__
	          << "; one of the vector: this= "
                  << *this << " or v= " << v 
                  << " is null. Zero returned." << std::endl;
        retval= 0.0;
      }
    else
      {
        const GEOM_FT mod_v1= GetModulus();
        const GEOM_FT mod_v2= v.GetModulus();
        const GEOM_FT prod_escalar= dot(*this,v);
        retval= acos(prod_escalar/(mod_v1*mod_v2));
      }
    return retval;
  }

bool paralelos(const Vector3d &v1,const Vector3d &v2)
  { return paralelas(v1.Direccion(),v2.Direccion()); } 
bool coplanarios(const Vector3d &v1,const Vector3d &v2,const Vector3d &v3)
  {
    const Pos3d p1= Origen3d + v1;
    const Pos3d p2= Origen3d + v2;
    const Pos3d p3= Origen3d + v3;
    return coplanarios(Origen3d,p1,p2,p3);
  }

GEOM_FT Abs(const Vector3d &v)
//Return el módulo del vector.
  { return v.GetModulus(); }

matriz_FT Traspuesta(const Vector3d &v)
  {
    matriz_FT retval(1,3);
    retval(1,1)= v.x(); retval(1,2)= v.y(); retval(1,3)= v.z();
    return retval;
  }
std::ostream &operator<<(std::ostream &stream,const Vector3d &n)
  {
    stream << "[[" << n.x() << "][" << n.y() << "]["
           << n.z() << "]]";
    return stream;
  }

//! @brief Return el angle between vectors.
double angle(const Vector3d &v1,const Vector3d &v2)
  { return v1.getAngle(v2); }


matriz_FT prod_tensor(const Vector3d &u,const Vector3d &v)
  { return prod_tensor(u.GetMatriz(),v.GetMatriz()); }

matriz_FT operator&(const Vector3d &u,const Vector3d &v)
  { return prod_tensor(u,v); }

//! @brief Dado el vector v que se pasa como parámetro
//! esta función devuelve la matriz que POSTmultiplicada
//! por un vector u devuelve otro vector igual al producto
//! vectorial (u x v)
//!
//! ver "Geometric tools for computer graphics"
//! Philip J. Schneider Morgan Kaufmann Publishers, páginas 119 y 120.
matriz_FT skew_symm_matrix_post(const Vector3d &v)
  {
    matriz_FT retval(3,3,double_to_FT(0.0));
    const GEOM_FT &v1= v(1);
    const GEOM_FT &v2= v(2);
    const GEOM_FT &v3= v(3);
    retval(1,2)= -v3; retval(1,3)= -v2;
    retval(2,1)= v3; retval(2,3)=-v1;
    retval(3,1)= -v2; retval(3,2)=v1;
    return retval;
  }

//! @brief Dado el vector v que se pasa como parámetro
//! esta función devuelve la matriz que PREmultiplicada
//! por un vector u devuelve otro vector igual al producto
//! vectorial (v x u)
//!
//! ver "Geometric tools for computer graphics"
//! Philip J. Schneider Morgan Kaufmann Publishers, páginas 119 y 120.
matriz_FT skew_symm_matrix_pre(const Vector3d &v)
  { return -skew_symm_matrix_post(v); }



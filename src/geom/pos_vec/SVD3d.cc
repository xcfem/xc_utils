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
//SVD3D.cc

#include "SVD3d.h"
#include "VDesliz3d.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/sis_ref/Ref3d3d.h"



//Ecuación del producto vectorial: x ^ a = b
//Ver libro "Mecánica teórica de los sistemas de sólidos rígidos" de José Antonio Fernández Palacios.

//! @brief Condición para que la ecuación tenga solución.
inline bool cond_compat_eq_prod_vect(const Vector3d &a,const Vector3d &b)
  { return (dot(a,b)<=0); }

//! @brief Solución de la ecuación x ^ a = b siendo x, a y b sliding vectors
//! y ^ el producto vectorial.
Recta3d sol_eq_prod_vect(const Vector3d &a,const Vector3d &b)
  {
    //Condición de compatibilidad.
    if(!cond_compat_eq_prod_vect(a,b))
      std::cerr << "La ecuación del producto vectorial no tiene solución." << std::endl;
    const GEOM_FT sqr_abs_a= Abs2(a);
    if(sqr_abs_a<=0)
      std::cerr << "La ecuación del producto vectorial no tiene solución: el vector a es nulo" << std::endl;
    const Pos3d org= Origen3d + ((a ^ b)*(1/sqr_abs_a));
    Pos3d dest= org+1000*a;
    return Recta3d(org,dest);
  }

SVD3d::SVD3d(const Pos3d &O,const Vector3d &R,const Vector3d &Mo)
  : VDesliz3d(O,R), mom(Mo) {}

SVD3d::SVD3d(const VDesliz3d &v)
  : VDesliz3d(v), mom(0,0,0) {}

//! @brief Moment field of the SVD3d.
//! Return themoment of the SVD3d with respect to the point P.
VDesliz3d SVD3d::getMoment(const Pos3d &P) const
  {
    const VDesliz3d m2= VDesliz3d::getMoment(P);
    return VDesliz3d(P,mom+m2);
  }

//! @brief Return the intersection of the zero moment line (if exists)
//! with the plane.
//! It's used, for example, to compunte the point of application of
//! the compression block in a reinforced concrete section.
Pos3d SVD3d::PointOfApplication(const Plane &p) const
  {
    Pos3d retval(NAN,NAN,NAN);
    if(ExisteRectaMomNulo())
      {
        Recta3d r= RectaMomNulo();
        GeomObj::list_Pos3d ptos= intersection(p,r);
        if(ptos.size()>0)
          retval= (*ptos.begin());
        else
          std::cerr << "The line of zero moment points is parallel to the plane."
		    << std::endl;
      }
    else
      std::cerr << "There are no points with zero moment." << std::endl;
    return retval;
  }

void SVD3d::PrintLtx(std::ostream &os,const std::string &ud_long,const GEOM_FT &f_long, const std::string &ud_f,const GEOM_FT &f_f) const
  {
    //Se asume que imprimimos en una tabla.
    os << "Point of application: " << org.VectorPos()*f_long << ud_long << "\\\\" << std::endl
       << "Resultant: " << getResultant()*f_f << ud_f << "\\\\" << std::endl 
       << "Moment: " << mom*f_f << ud_f << ud_long << "\\\\" << std::endl;
  }

//! @brief Moment with respect to an axis.
//! Is the moment with respect a point on the axis
//! projected onto the axis.
GEOM_FT SVD3d::getMoment(const Recta3d &e) const
  { return dot(SVD3d::getMoment(e.Point()),e.VDir().Normalizado()); }

//! @brief Return el moment vector expressed in the reference
//! frame being passed as parameter.
Vector3d SVD3d::getMoment(const Ref3d3d &ref) const
  {
    VDesliz3d m= getMoment(ref.Org());
    return ref.GetCooLocales(m);
  }

//! @brief Return the resultant vector expressed in the
//! reference frame argument.
Vector3d SVD3d::getResultant(const Ref3d3d &ref) const
  { return ref.GetCooLocales(getResultant()); } 

bool SVD3d::Nulo(void) const
  {
    bool retval= true;
    if(!VDesliz3d::Nulo()) retval= false;
    if(!mom.Nulo()) retval= false;
    return retval;
  }

void SVD3d::Neg(void)
  {
    VDesliz3d::Neg();
    mom=-mom;
  }

//! @brief Return the central axis of the system (moment paraller to resultant).
Recta3d SVD3d::centralAxis(void) const
  { return sol_eq_prod_vect(getResultant(),mom); }

//! @brief Return the line of the points with zero moment.
Recta3d SVD3d::RectaMomNulo(const double &tol) const
  {
    if(ExisteRectaMomNulo(tol))
      return sol_eq_prod_vect(getResultant(),mom);
    else
      return Recta3d(Pos3d(NAN,NAN,NAN),Pos3d(NAN,NAN,NAN));
  }

//! @brief Return true if the line of the points with zero moment exists.
bool SVD3d::ExisteRectaMomNulo(const double &tol) const
  {
    if((VDesliz3d::Nulo()) && !(mom.Nulo())) return false;
    if(dot(getResultant(),mom)>0) return false;
    return true;
  }

SVD3d SVD3d::ReduceA(const Pos3d &Q) const
  { return SVD3d(Q,getResultant(),getMoment(Q)); }

SVD3d &SVD3d::operator+=(const VDesliz3d &v)
  {
    Vector3d::operator+=(v);
    mom= mom + v.getMoment(org);
    return *this;
  }
SVD3d &SVD3d::operator-=(const VDesliz3d &v)
  {
    VDesliz3d::operator-=(v);
    mom= mom - v.getMoment(org);
    return *this;
  }
SVD3d &SVD3d::operator+=(const SVD3d &s)
  //The org point is preserved.
  {
    VDesliz3d::operator+=(s);
    mom= mom + s.getMoment(org);
    return *this;
  }

SVD3d &SVD3d::operator-=(const SVD3d &s)
  //The org point is preserved.
  {
    VDesliz3d::operator-=(s);
    mom= mom - s.getMoment(org);
    return *this;
  }
SVD3d &SVD3d::operator*=(const GEOM_FT &d)
  {
    VDesliz3d::operator*=(d);
    mom= mom * d;
    return *this;
  }

//! @brief Return the sum of the sliding vectors systems.
SVD3d operator+(const SVD3d &s1,const SVD3d &s2)
  {
    SVD3d retval(s1);
    retval+=s2;
    return retval;
  }

//! @brief Return the difference of sliding vectors systems.
SVD3d operator-(const SVD3d &s1,const SVD3d &s2)
  {
    SVD3d retval(s1);
    retval-=s2;
    return retval;
  }

//! @brief Return the product of the sliding vectors system by a scalar.
SVD3d operator*(const GEOM_FT &d, const SVD3d &s)
  {
    SVD3d retval(s);
    return retval*=d;
  }
//! @brief Return the product of the sliding vectors system by a scalar.
SVD3d operator*(const SVD3d &s,const GEOM_FT &d)
  { return d*s; }

//! @brief Imprime el sliding vectors system.
void SVD3d::Print(std::ostream &os) const
  {
    os << "Resultant R=" << getResultant()
       << " , moment with respect to " << org << " Mo= " << mom; 
  }

//! @brief Return the suma de los sliding vectors.
SVD3d operator+(const VDesliz3d &v1,const VDesliz3d &v2)
  {
    SVD3d suma(v1);
    suma+=v2;
    return suma;
  }

//! @brief Return the sum of the sliding vector system
//! with the vector being passed as parameter.
SVD3d operator+(const SVD3d &s,const VDesliz3d &v)
  {
    SVD3d suma(s);
    suma+=v;
    return suma;
  }

//! @brief Return the sum of the sliding vector system
//! with the vector being passed as parameter.
SVD3d operator+(const VDesliz3d &v,const SVD3d &s)
  { return s+v; }

//! @brief Cambia de signo al sliding vector.
SVD3d operator-(const SVD3d &svd3d)
  {
    SVD3d retval(svd3d);
    retval.Neg();
    return retval;
  }

//! @brief Prints.
std::ostream &operator<<(std::ostream &os, const SVD3d &svd3d)
  {
    svd3d.Print(os);
    return os;
  }

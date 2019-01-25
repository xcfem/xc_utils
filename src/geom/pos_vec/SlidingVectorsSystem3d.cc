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
//SlidingVectorsSystem3d.cc

#include "SlidingVectorsSystem3d.h"
#include "SlidingVector3d.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d1/Line3d.h"
#include "xc_utils/src/geom/sis_ref/Ref3d3d.h"



//Equation of the cross product: x ^ a = b
//See book "Mecánica teórica de los sistemas de sólidos rígidos" de José Antonio Fernández Palacios.

//! @brief Condición para que la ecuación tenga solución.
inline bool cond_compat_eq_prod_vect(const Vector3d &a,const Vector3d &b)
  { return (dot(a,b)<=0); }

//! @brief Solución de la ecuación x ^ a = b siendo x, a y b sliding vectors
//! y ^ el producto vectorial.
Line3d sol_eq_prod_vect(const Vector3d &a,const Vector3d &b)
  {
    //Condición de compatibilidad.
    if(!cond_compat_eq_prod_vect(a,b))
      std::cerr << "La ecuación del producto vectorial no tiene solución." << std::endl;
    const GEOM_FT sqr_abs_a= Abs2(a);
    if(sqr_abs_a<=0)
      std::cerr << "La ecuación del producto vectorial no tiene solución: el vector a es nulo" << std::endl;
    const Pos3d org= Origin3d + ((a ^ b)*(1/sqr_abs_a));
    Pos3d dest= org+1000*a;
    return Line3d(org,dest);
  }

SlidingVectorsSystem3d::SlidingVectorsSystem3d(const Pos3d &O,const Vector3d &R,const Vector3d &Mo)
  : SlidingVector3d(O,R), mom(Mo) {}

SlidingVectorsSystem3d::SlidingVectorsSystem3d(const SlidingVector3d &v)
  : SlidingVector3d(v), mom(0,0,0) {}

//! @brief Moment field of the SlidingVectorsSystem3d.
//! Return themoment of the SlidingVectorsSystem3d with respect to the point P.
SlidingVector3d SlidingVectorsSystem3d::getMoment(const Pos3d &P) const
  {
    const SlidingVector3d m2= SlidingVector3d::getMoment(P);
    return SlidingVector3d(P,mom+m2);
  }

//! @brief Return the intersection of the zero moment line (if exists)
//! with the plane.
//! It's used, for example, to compunte the point of application of
//! the compression block in a reinforced concrete section.
Pos3d SlidingVectorsSystem3d::PointOfApplication(const Plane &p) const
  {
    Pos3d retval(NAN,NAN,NAN);
    if(existsZeroMomentLine())
      {
        Line3d r= getZeroMomentLine();
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

void SlidingVectorsSystem3d::PrintLtx(std::ostream &os,const std::string &ud_long,const GEOM_FT &f_long, const std::string &ud_f,const GEOM_FT &f_f) const
  {
    //Se asume que imprimimos en una tabla.
    os << "Point of application: " << org.VectorPos()*f_long << ud_long << "\\\\" << std::endl
       << "Resultant: " << getResultant()*f_f << ud_f << "\\\\" << std::endl 
       << "Moment: " << mom*f_f << ud_f << ud_long << "\\\\" << std::endl;
  }

//! @brief Moment with respect to an axis.
//! Is the moment with respect a point on the axis
//! projected onto the axis.
GEOM_FT SlidingVectorsSystem3d::getMoment(const Line3d &e) const
  { return dot(SlidingVectorsSystem3d::getMoment(e.Point()),e.VDir().Normalizado()); }

//! @brief Return el moment vector expressed in the reference
//! frame being passed as parameter.
Vector3d SlidingVectorsSystem3d::getMoment(const Ref3d3d &ref) const
  {
    SlidingVector3d m= getMoment(ref.Org());
    return ref.GetCooLocales(m);
  }

//! @brief Return the resultant vector expressed in the
//! reference frame argument.
Vector3d SlidingVectorsSystem3d::getResultant(const Ref3d3d &ref) const
  { return ref.GetCooLocales(getResultant()); } 

bool SlidingVectorsSystem3d::Nulo(void) const
  {
    bool retval= true;
    if(!SlidingVector3d::Nulo()) retval= false;
    if(!mom.Nulo()) retval= false;
    return retval;
  }

void SlidingVectorsSystem3d::Neg(void)
  {
    SlidingVector3d::Neg();
    mom=-mom;
  }

//! @brief Return the central axis of the system (moment paraller to resultant).
Line3d SlidingVectorsSystem3d::centralAxis(void) const
  { return sol_eq_prod_vect(getResultant(),mom); }

//! @brief Return the line of the points with zero moment.
Line3d SlidingVectorsSystem3d::getZeroMomentLine(const double &tol) const
  {
    if(existsZeroMomentLine(tol))
      return sol_eq_prod_vect(getResultant(),mom);
    else
      return Line3d(Pos3d(NAN,NAN,NAN),Pos3d(NAN,NAN,NAN));
  }

//! @brief Return true if the line of the points with zero moment exists.
bool SlidingVectorsSystem3d::existsZeroMomentLine(const double &tol) const
  {
    if((SlidingVector3d::Nulo()) && !(mom.Nulo())) return false;
    if(dot(getResultant(),mom)>0) return false;
    return true;
  }

SlidingVectorsSystem3d SlidingVectorsSystem3d::ReduceA(const Pos3d &Q) const
  { return SlidingVectorsSystem3d(Q,getResultant(),getMoment(Q)); }

SlidingVectorsSystem3d &SlidingVectorsSystem3d::operator+=(const SlidingVector3d &v)
  {
    Vector3d::operator+=(v);
    mom= mom + v.getMoment(org);
    return *this;
  }
SlidingVectorsSystem3d &SlidingVectorsSystem3d::operator-=(const SlidingVector3d &v)
  {
    SlidingVector3d::operator-=(v);
    mom= mom - v.getMoment(org);
    return *this;
  }
SlidingVectorsSystem3d &SlidingVectorsSystem3d::operator+=(const SlidingVectorsSystem3d &s)
  //The org point is preserved.
  {
    SlidingVector3d::operator+=(s);
    mom= mom + s.getMoment(org);
    return *this;
  }

SlidingVectorsSystem3d &SlidingVectorsSystem3d::operator-=(const SlidingVectorsSystem3d &s)
  //The org point is preserved.
  {
    SlidingVector3d::operator-=(s);
    mom= mom - s.getMoment(org);
    return *this;
  }
SlidingVectorsSystem3d &SlidingVectorsSystem3d::operator*=(const GEOM_FT &d)
  {
    SlidingVector3d::operator*=(d);
    mom= mom * d;
    return *this;
  }

//! @brief Return the sum of the sliding vectors systems.
SlidingVectorsSystem3d operator+(const SlidingVectorsSystem3d &s1,const SlidingVectorsSystem3d &s2)
  {
    SlidingVectorsSystem3d retval(s1);
    retval+=s2;
    return retval;
  }

//! @brief Return the difference of sliding vectors systems.
SlidingVectorsSystem3d operator-(const SlidingVectorsSystem3d &s1,const SlidingVectorsSystem3d &s2)
  {
    SlidingVectorsSystem3d retval(s1);
    retval-=s2;
    return retval;
  }

//! @brief Return the product of the sliding vectors system by a scalar.
SlidingVectorsSystem3d operator*(const GEOM_FT &d, const SlidingVectorsSystem3d &s)
  {
    SlidingVectorsSystem3d retval(s);
    return retval*=d;
  }
//! @brief Return the product of the sliding vectors system by a scalar.
SlidingVectorsSystem3d operator*(const SlidingVectorsSystem3d &s,const GEOM_FT &d)
  { return d*s; }

//! @brief Imprime el sliding vectors system.
void SlidingVectorsSystem3d::Print(std::ostream &os) const
  {
    os << "Resultant R=" << getResultant()
       << " , moment with respect to " << org << " Mo= " << mom; 
  }

//! @brief Return the suma de los sliding vectors.
SlidingVectorsSystem3d operator+(const SlidingVector3d &v1,const SlidingVector3d &v2)
  {
    SlidingVectorsSystem3d suma(v1);
    suma+=v2;
    return suma;
  }

//! @brief Return the sum of the sliding vector system
//! with the vector being passed as parameter.
SlidingVectorsSystem3d operator+(const SlidingVectorsSystem3d &s,const SlidingVector3d &v)
  {
    SlidingVectorsSystem3d suma(s);
    suma+=v;
    return suma;
  }

//! @brief Return the sum of the sliding vector system
//! with the vector being passed as parameter.
SlidingVectorsSystem3d operator+(const SlidingVector3d &v,const SlidingVectorsSystem3d &s)
  { return s+v; }

//! @brief Cambia de signo al sliding vector.
SlidingVectorsSystem3d operator-(const SlidingVectorsSystem3d &svd3d)
  {
    SlidingVectorsSystem3d retval(svd3d);
    retval.Neg();
    return retval;
  }

//! @brief Prints.
std::ostream &operator<<(std::ostream &os, const SlidingVectorsSystem3d &svd3d)
  {
    svd3d.Print(os);
    return os;
  }

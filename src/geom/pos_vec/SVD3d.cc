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
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/sis_ref/Ref3d3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/utils_any.h"

//Ecuación del producto vectorial: x ^ a = b
//Ver libro "Mecánica teórica de los sistemas de sólidos rígidos" de José Antonio Fernández Palacios.

//! @brief Condición para que la ecuación tenga solución.
inline bool cond_compat_eq_prod_vect(const Vector3d &a,const Vector3d &b)
  { return (dot(a,b)<=0); }

//! @brief Solución de la ecuación x ^ a = b siendo x, a y b vectores deslizantes
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

//! Lee un objeto SVD3d desde archivo
bool SVD3d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SVD3d) Procesando comando: " << cmd << std::endl;
    if(cmd == "momento")
      {
        mom.LeeCmd(status);
        return true;
      }
    else if(cmd == "suma_vector")
      {
        VDesliz3d tmp;
        tmp.LeeCmd(status);
        (*this)+=tmp;
        return true;
      }
    else if(cmd == "suma")
      {
        SVD3d tmp;
        tmp.LeeCmd(status);
        (*this)+=tmp;
        return true;
      }
    else
      return VDesliz3d::procesa_comando(status);
  }

//! @brief Campo de momentos del SVD3d.
//! Devuelve el momento del SVD3d respecto al punto P.
VDesliz3d SVD3d::getMomento(const Pos3d &P) const
  {
    const VDesliz3d m2= VDesliz3d::getMomento(P);
    return VDesliz3d(P,mom+m2);
  }

//! @brief Devuelve la intersección de la recta de puntos cuyo momento es nulo (if exists)
//! con el plano que se pasa como parámetro.
//! Se usa, por ejemplo, para calcular el punto de aplicación del bloque de compresiones del hormigón.
Pos3d SVD3d::PuntoAplic(const Plano3d &p) const
  {
    Pos3d retval(NAN,NAN,NAN);
    if(ExisteRectaMomNulo())
      {
        Recta3d r= RectaMomNulo();
        GeomObj::list_Pos3d ptos= interseccion(p,r);
        if(ptos.size()>0)
          retval= (*ptos.begin());
        else
          std::cerr << "La recta de puntos de momento nulo es paralela a la sección" << std::endl;
      }
    else
      std::cerr << "No existen de puntos de momento nulo" << std::endl;
    return retval;
  }

void SVD3d::PrintLtx(std::ostream &os,const std::string &ud_long,const GEOM_FT &f_long, const std::string &ud_f,const GEOM_FT &f_f) const
  {
    //Se asume que imprimimos en una tabla.
    os << "Punto de aplicación: " << org.VectorPos()*f_long << ud_long << "\\\\" << std::endl
       << "Resultante: " << getResultante()*f_f << ud_f << "\\\\" << std::endl 
       << "Momento: " << mom*f_f << ud_f << ud_long << "\\\\" << std::endl;
  }

//! @brief Momento de un SVD3d respecto a un eje.
//! Es el momento respecto a un punto
//! del eje proyectado sobre el eje.
GEOM_FT SVD3d::getMomento(const Recta3d &e) const
  { return dot(SVD3d::getMomento(e.Punto()),e.VDir().Normalizado()); }

//! @brief Devuelve el vector momento expresado en el sistema
//! de referencia que se pasa como parámetro.
Vector3d SVD3d::getMomento(const Ref3d3d &ref) const
  {
    VDesliz3d m= getMomento(ref.Org());
    return ref.GetCooLocales(m);
  }

//! @brief Devuelve el vector resultante expresado en el sistema
//! de referencia que se pasa como parámetro.
Vector3d SVD3d::getResultante(const Ref3d3d &ref) const
  { return ref.GetCooLocales(getResultante()); } 

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

//Lugar geométrico de los puntos cuyo momento es paralelo a la
//resultante.
Recta3d SVD3d::EjeCentral(void) const
{ return sol_eq_prod_vect(getResultante(),mom); }

//Lugar geométrico de los puntos cuyo momento es paralelo a la
//resultante.
Recta3d SVD3d::RectaMomNulo(const double &tol) const
  {
    if(ExisteRectaMomNulo(tol))
      return sol_eq_prod_vect(getResultante(),mom);
    else
      return Recta3d(Pos3d(NAN,NAN,NAN),Pos3d(NAN,NAN,NAN));
  }

//Devuelve verdadero if exists una recta cuyos puntos
//tienen momento nulo.
bool SVD3d::ExisteRectaMomNulo(const double &tol) const
  {
    if((VDesliz3d::Nulo()) && !(mom.Nulo())) return false;
    if(dot(getResultante(),mom)>0) return false;
    return true;
  }

SVD3d SVD3d::ReduceA(const Pos3d &Q)
  { return SVD3d(Q,getResultante(),getMomento(Q)); }

SVD3d &SVD3d::operator+=(const VDesliz3d &v)
  {
    Vector3d::operator+=(v);
    mom= mom + v.getMomento(org);
    return *this;
  }
SVD3d &SVD3d::operator-=(const VDesliz3d &v)
  {
    VDesliz3d::operator-=(v);
    mom= mom - v.getMomento(org);
    return *this;
  }
SVD3d &SVD3d::operator+=(const SVD3d &s)
  //El punto org se conserva.
  {
    VDesliz3d::operator+=(s);
    mom= mom + s.getMomento(org);
    return *this;
  }

SVD3d &SVD3d::operator-=(const SVD3d &s)
  //El punto org se conserva.
  {
    VDesliz3d::operator-=(s);
    mom= mom - s.getMomento(org);
    return *this;
  }
SVD3d &SVD3d::operator*=(const GEOM_FT &d)
  {
    VDesliz3d::operator*=(d);
    mom= mom * d;
    return *this;
  }

//! @brief Devuelve la suma de los sistemas de vectores deslizantes.
SVD3d operator+(const SVD3d &s1,const SVD3d &s2)
  {
    SVD3d retval(s1);
    retval+=s2;
    return retval;
  }

//! @brief Devuelve la resta de los sistemas de vectores deslizantes.
SVD3d operator-(const SVD3d &s1,const SVD3d &s2)
  {
    SVD3d retval(s1);
    retval-=s2;
    return retval;
  }
//! @brief Devuelve el producto del sistema de vectores deslizantes por un escalar.
SVD3d operator*(const GEOM_FT &d, const SVD3d &s)
  {
    SVD3d retval(s);
    return retval*=d;
  }
//! @brief Devuelve el producto del sistema de vectores deslizantes por un escalar.
SVD3d operator*(const SVD3d &s,const GEOM_FT &d)
  { return d*s; }

//! @brief Devuelve una propiedad del objeto.
any_const_ptr SVD3d::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "SVD3d::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod=="getResultante")
      {
        tmp_gp_vector3d= getResultante();
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getMomento")
      return any_const_ptr(mom);
    else if(cod=="getMomentoRespectoPunto")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_gp_vdesliz3d= getMomento(tmp);
        return any_const_ptr(tmp_gp_vdesliz3d);
      }
    else if(cod=="getMomentoRespectoEje")
      {
        const Recta3d eje= popRecta3d(cod);
        tmp_gp_dbl= getMomento(eje);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="getEjeCentral")
      {
        tmp_gp_recta3d= EjeCentral();
        return any_const_ptr(tmp_gp_recta3d);
      }
    else
      return VDesliz3d::GetProp(cod);
  }

//! @brief Imprime el sistema de vectores deslizantes.
void SVD3d::Print(std::ostream &os) const
  {
    os << "Resultante R=" << getResultante()
       << " , momento respecto a " << org << " Mo= " << mom; 
  }

//! @brief Devuelve la suma de los vectores deslizantes.
SVD3d operator+(const VDesliz3d &v1,const VDesliz3d &v2)
  {
    SVD3d suma(v1);
    suma+=v2;
    return suma;
  }

//! @brief Devuelve la suma del sistema de vectores
//! deslizantes con el vector deslizante.
SVD3d operator+(const SVD3d &s,const VDesliz3d &v)
  {
    SVD3d suma(s);
    suma+=v;
    return suma;
  }

//! @brief Devuelve la suma del sistema de vectores
//! deslizantes con el vector deslizante.
SVD3d operator+(const VDesliz3d &v,const SVD3d &s)
  { return s+v; }

//! @brief Cambia de signo al vector deslizante.
SVD3d operator-(const SVD3d &svd3d)
  {
    SVD3d retval(svd3d);
    retval.Neg();
    return retval;
  }

//! @brief Imprime el sistema de vectores deslizantes.
std::ostream &operator<<(std::ostream &os, const SVD3d &svd3d)
  {
    svd3d.Print(os);
    return os;
  }

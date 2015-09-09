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
//tipos_cgal.cc

#include "tipos_cgal.h"
#include "CGAL/to_rational.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/base/any_const_ptr.h"

GEOM_FT double_to_FT(const double &d)
  {
    //return CGAL::to_rational<GEOM_FT>(d);
    return d;
  }

GEOM_FT sqrt_FT(const GEOM_FT &n)
  { 
    const double tmp= sqrt(n);
    return double_to_FT(tmp);
  }

GEOM_FT abs_FT(const GEOM_FT &n)
  { return fabs(n); }

CGPoint_2 Point_2_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y)
  {
//     const GEOM_RT wsx = x.numerator() * y.denominator(); 
//     const GEOM_RT wsy = y.numerator() * x.denominator(); 
//     const GEOM_RT wsh  = x.denominator() * y.denominator(); 
//     return CGPoint_2(wsx, wsy, wsh);
    return CGPoint_2(x, y, 1.0);
  }
CGDirection_2 Dir_2_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y)
  {
//     const GEOM_RT wsx = x.numerator() * y.denominator(); 
//     const GEOM_RT wsy = y.numerator() * x.denominator(); 
//     return CGDirection_2(wsx, wsy);
    return CGDirection_2(x, y);
  }
CGVector_2 Vector_2_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y)
  {
//     const GEOM_RT wsx = x.numerator() * y.denominator(); 
//     const GEOM_RT wsy = y.numerator() * x.denominator(); 
//     const GEOM_RT wsh  = x.denominator() * y.denominator(); 
//     assert(wsh!=0);
//     return CGVector_2(wsx, wsy, wsh);
    return CGVector_2(x, y, 1.0);
  }
CGPoint_2 Point_2_from_doubles(const double &x,const double &y)
  {
//     const GEOM_FT p_q_x(double_to_FT(x));
//     const GEOM_FT p_q_y(double_to_FT(y));
//     return Point_2_from_cartesianas(p_q_x,p_q_y);
    return Point_2_from_cartesianas(x,y);
  }
CGVector_2 Vector_2_from_doubles(const double &x,const double &y)
  {
//     const GEOM_FT p_q_x(double_to_FT(x));
//     const GEOM_FT p_q_y(double_to_FT(y));
//     return Vector_2_from_cartesianas(p_q_x,p_q_y);
    return Vector_2_from_cartesianas(x,y);
  }

CGPoint_3 Point_3_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y,const GEOM_FT &z)
  {
//     const GEOM_RT wsx = x.numerator() * y.denominator() * z.denominator(); 
//     const GEOM_RT wsy = y.numerator() * x.denominator() * z.denominator(); 
//     const GEOM_RT wsz = z.numerator() * x.denominator() * y.denominator(); 
//     const GEOM_RT wsh  = x.denominator() * y.denominator() * z.denominator(); 
//     return CGPoint_3(wsx, wsy, wsz, wsh);
    return CGPoint_3(x, y, z, 1.0);
  }
CGDirection_3 Dir_3_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y,const GEOM_FT &z)
  {
//     const GEOM_RT wsx = x.numerator() * y.denominator() * z.denominator(); 
//     const GEOM_RT wsy = y.numerator() * x.denominator() * z.denominator(); 
//     const GEOM_RT wsz = z.numerator() * x.denominator() * y.denominator(); 
//     return CGDirection_3(wsx, wsy,wsz);
    return CGDirection_3(x, y,z);
  }
CGVector_3 Vector_3_from_cartesianas(const GEOM_FT &x,const GEOM_FT &y,const GEOM_FT &z)
  {
//     const GEOM_RT wsx = x.numerator() * y.denominator() * z.denominator(); 
//     const GEOM_RT wsy = y.numerator() * x.denominator() * z.denominator(); 
//     const GEOM_RT wsz = z.numerator() * x.denominator() * y.denominator(); 
//     const GEOM_RT wsh  = x.denominator() * y.denominator() * z.denominator(); 
//     assert(wsh!=0);
//     return CGVector_3(wsx, wsy, wsz, wsh);
    return CGVector_3(x, y, z, 1.0);
  }
CGPoint_3 Point_3_from_doubles(const double &x,const double &y,const double &z)
  {
//     const GEOM_FT p_q_x(double_to_FT(x));
//     const GEOM_FT p_q_y(double_to_FT(y));
//     const GEOM_FT p_q_z(double_to_FT(z));
//     return Point_3_from_cartesianas(p_q_x,p_q_y,p_q_z);
    return Point_3_from_cartesianas(x,y,z);
  }
CGVector_3 Vector_3_from_doubles(const double &x,const double &y,const double &z)
  {
//     const GEOM_FT p_q_x(double_to_FT(x));
//     const GEOM_FT p_q_y(double_to_FT(y));
//     const GEOM_FT p_q_z(double_to_FT(z));
//     return Vector_3_from_cartesianas(p_q_x,p_q_y,p_q_z);
    return Vector_3_from_cartesianas(x,y,z);
  }


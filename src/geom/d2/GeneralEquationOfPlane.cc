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
//GeneralEquationOfPlane.cc

#include "GeneralEquationOfPlane.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Pos2d.h"

// GeneralEquationOfPlane::GeneralEquationOfPlane(const GEOM_RT &a,const GEOM_RT &b,const GEOM_RT &c,const GEOM_RT &d)
//   : v(4,0.0) { v[0]= d; v[1]= a; v[2]= b; v[3]= c; }

GeneralEquationOfPlane::GeneralEquationOfPlane(const GEOM_FT &fa,const GEOM_FT &fb,const GEOM_FT &fc,const GEOM_FT &fd)
  : v(4,0.0) 
  { 
//     const GEOM_RT a= fa.numerator()*fb.denominator()*fc.denominator()*fd.denominator();
//     const GEOM_RT b= fa.denominator()*fb.numerator()*fc.denominator()*fd.denominator();
//     const GEOM_RT c= fa.denominator()*fb.denominator()*fc.numerator()*fd.denominator();
//     const GEOM_RT d= fa.denominator()*fb.denominator()*fc.denominator()*fd.numerator();
//     v[0]= d; v[1]= a; v[2]= b; v[3]= c; 
    v[0]= fd; v[1]= fa; v[2]= fb; v[3]= fc; 
  }

GEOM_FT GeneralEquationOfPlane::Eval(const Pos3d &p) const
  { return a()*p.x()+b()*p.y()+c()*p.z()+d(); }

//! @brief Devuelve la x coordinate del point of the plano
//! which y and z are those from the argument.
GEOM_FT GeneralEquationOfPlane::x(const GEOM_FT &y,const GEOM_FT &z) const
      { return -(d()+b()*y+c()*z)/a(); }

//! @brief Return the x coordinate of the point of the plane
//! which y and z are those from the argument.
GEOM_FT GeneralEquationOfPlane::x(const Pos2d &p) const
  { return x(p.x(),p.y()); }

//! @brief Return the y coordinate del point of the plano
//! which x and z are those from the argument.
GEOM_FT GeneralEquationOfPlane::y(const GEOM_FT &x,const GEOM_FT &z) const
      { return -(d()+a()*x+c()*z)/b(); }

//! @brief Return the y coordinate del point of the plano
//! which x and z are those from the argument.
GEOM_FT GeneralEquationOfPlane::y(const Pos2d &p) const
  { return y(p.x(),p.y()); }

//! @brief Return the z coordinate del point of the plano
//! which x and y are those from the argument.
GEOM_FT GeneralEquationOfPlane::z(const GEOM_FT &x,const GEOM_FT &y) const
      { return -(d()+a()*x+b()*y)/c(); }

//! @brief Return the z coordinate del point of the plano
//! which x and y are those from the argument.
GEOM_FT GeneralEquationOfPlane::z(const Pos2d &p) const
  { return z(p.x(),p.y()); }

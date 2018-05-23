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
//GeomObj2d.cc

#include "PrincipalAxesOfInertia2D.h"
#include "xc_basic/src/util/inercia.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"


//! @brief Constructor.
PrincipalAxesOfInertia2D::PrincipalAxesOfInertia2D(const Pos2d &center_of_mass_,const GEOM_FT &Ix,const GEOM_FT &Iy,const GEOM_FT &Pxy)
  : center_of_mass(center_of_mass_), axis1(1,0), i1(0.0), i2(0.0)
  {
    double th1= theta_inercia(Ix,Iy,Pxy);
    const GEOM_FT media= (Ix+Iy)/2;
    const GEOM_FT dif2= (Ix-Iy)/2;
    const double th1_por2= 2*th1;
    const GEOM_FT seno= sin(th1_por2);
    const GEOM_FT coseno= cos(th1_por2);
    i1= media+dif2*coseno-Pxy*seno;
    i2= Ix+Iy-i1;
    if(i1<i2)
      {
	std::swap(i1,i2);
        th1+= (M_PI/2.0);
      }
    axis1= Vector2d(cos(th1),sin(th1));
  }
Ref2d2d PrincipalAxesOfInertia2D::getAxis(void) const
  { return Ref2d2d(center_of_mass,axis1); }
const GEOM_FT &PrincipalAxesOfInertia2D::I1(void) const
  { return i1; }
const GEOM_FT &PrincipalAxesOfInertia2D::I2(void) const
  { return i2; }

//! @brief Return the direction vector of the minor
//! principal axis of inertia.
Vector2d PrincipalAxesOfInertia2D::getAxis2VDir(void) const
  { return Vector2d(-axis1.y(),axis1.x()); }

std::ostream &operator<<(std::ostream &os,const PrincipalAxesOfInertia2D &axis)
  {
    os << "Axis: " << axis.getAxis() << std::endl
       << "I1= " << axis.I1() << std::endl
       << "I2= " << axis.I2();
    return os;
  }


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
//Rotation3d.cc

#include "Rotation3d.h"
#include "xc_utils/src/geom/d1/Line3d.h"
#include "xc_utils/src/geom/FT_matrix.h"

//! Rotation in 3D as described in "Geometric tools for computer graphics"
//! Philip J. Schneider Morgan Kaufmann Publishers, page 141
FT_matrix rotation_3d_matrix(const Line3d &axis,const double &theta)
  {
    FT_matrix retval(4,4);
    const GEOM_FT cos_theta= double_to_FT(cos(theta));
    const GEOM_FT sin_theta= double_to_FT(sin(theta));
    const FT_matrix I= identidad(FT_matrix(3,3));
    const Vector3d u= axis.VDir();
    const FT_matrix T_u_theta_1= cos_theta*I;
    const FT_matrix T_u_theta_2= (double_to_FT(1.0)-cos_theta)*prod_tensor(u,u);
    const FT_matrix T_u_theta_3= sin_theta*skew_symm_matrix_pre(u);
    const FT_matrix T_u_theta= traspuesta(T_u_theta_1+T_u_theta_2+T_u_theta_3);
    retval.putBox(1,1,T_u_theta);
    const Pos3d Q= axis.Point();
    const Vector3d tmp= T_u_theta*Q.VectorPos();
    const Vector3d VQ= Q.VectorPos()-tmp;
    retval.putBox(1,4,VQ.getMatrix());
    retval(4,4)=1;
    return retval;
  }

//! @brief Default constructor.
Rotation3d::Rotation3d(void)
  : Trf3d()
  {
    FT_matrix rr=  identidad(4);
    putHomogenousMatrix(rr);
  }

//! @brief Constructor.
Rotation3d::Rotation3d(const Line3d &axis,const GEOM_FT &theta)
  : Trf3d()
  {
    FT_matrix rr=  rotation_3d_matrix(axis,theta);
    putHomogenousMatrix(rr);
  }

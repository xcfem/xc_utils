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
//Rotacion3d.cc

#include "Rotacion3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/geom/matriz_FT.h"

//! Rotación en 3d según se describe en "Geometric tools for computer graphics"
//! Philip J. Schneider Morgan Kaufmann Publishers, página 141
matriz_FT matriz_rotacion_3d(const Recta3d &eje,const double &theta)
  {
    matriz_FT retval(4,4);
    const GEOM_FT cos_theta= double_to_FT(cos(theta));
    const GEOM_FT sin_theta= double_to_FT(sin(theta));
    const matriz_FT I= identidad(matriz_FT(3,3));
    const Vector3d u= eje.VDir();
    const matriz_FT T_u_theta_1= cos_theta*I;
    const matriz_FT T_u_theta_2= (double_to_FT(1.0)-cos_theta)*prod_tensor(u,u);
    const matriz_FT T_u_theta_3= sin_theta*skew_symm_matrix_pre(u);
    const matriz_FT T_u_theta= traspuesta(T_u_theta_1+T_u_theta_2+T_u_theta_3);
    retval.PutCaja(1,1,T_u_theta);
    const Pos3d Q= eje.Punto();
    const Vector3d tmp= T_u_theta*Q.VectorPos();
    const Vector3d VQ= Q.VectorPos()-tmp;
    retval.PutCaja(1,4,VQ.GetMatriz());
    retval(4,4)=1;
    return retval;
  }

//! @brief Constructor por defecto.
Rotacion3d::Rotacion3d(void)
  : Trf3d()
  {
    matriz_FT rr=  identidad(4);
    PutMatrizHomogeneas(rr);
  }

//! @brief Constructor.
Rotacion3d::Rotacion3d(const Recta3d &eje,const GEOM_FT &theta)
  : Trf3d()
  {
    matriz_FT rr=  matriz_rotacion_3d(eje,theta);
    PutMatrizHomogeneas(rr);
  }

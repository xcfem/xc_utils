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
//Reflection3d.cc

#include "Reflection3d.h"
#include "xc_utils/src/geom/matriz_FT.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d2/Plane.h"


//! Reflexión en 3d según se describe en "Geometric tools for computer graphics"
//! Philip J. Schneider Morgan Kaufmann Publishers, page 153
matriz_FT Reflection3d::matriz_reflection3d(const  Pos3d &Q,const Vector3d &n)
  {
    const Vector3d nn= n.Normalizado();
    matriz_FT retval(4,4);
    const matriz_FT I= identidad(matriz_FT(3,3));
    const matriz_FT T_n= traspuesta(I-2*prod_tensor(nn,nn));
    retval.PutCaja(1,1,T_n);
    const Vector3d VQ= double_to_FT(2)*dot(Q.VectorPos(),nn)*nn;
    retval.PutCaja(1,4,VQ.GetMatriz());
    retval(4,4)=1;
    return retval;
  }

//! @brief Constructor por defecto.
Reflection3d::Reflection3d(void)
  : Trf3d()
  {
    matriz_FT rf=  matriz_reflection3d(Pos3d(0.0,0.0,0.0),Vector3d(0.0,0.0,1.0));
    PutMatrizHomogeneas(rf);
  }

//! @brief Constructor.
Reflection3d::Reflection3d(const Pos3d &Q,const Vector3d &d)
  : Trf3d()
  {
    matriz_FT rf=  matriz_reflection3d(Q,d);
    PutMatrizHomogeneas(rf);
  }

//! @brief Constructor.
Reflection3d::Reflection3d(const Plane &p)
  : Trf3d()
  {
    matriz_FT rf=  matriz_reflection3d(p.Point(),p.Normal());
    PutMatrizHomogeneas(rf);
  }


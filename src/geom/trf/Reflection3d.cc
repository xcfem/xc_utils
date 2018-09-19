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
#include "xc_utils/src/geom/FT_matrix.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d2/Plane.h"


//! Reflexión en 3d según se describe en "Geometric tools for computer graphics"
//! Philip J. Schneider Morgan Kaufmann Publishers, page 153
FT_matrix Reflection3d::reflection3d_matrix(const  Pos3d &Q,const Vector3d &n)
  {
    const Vector3d nn= n.Normalizado();
    FT_matrix retval(4,4);
    const FT_matrix I= identity(FT_matrix(3,3));
    const FT_matrix T_n= traspuesta(I-2*prod_tensor(nn,nn));
    retval.putBox(1,1,T_n);
    const Vector3d VQ= double_to_FT(2)*dot(Q.VectorPos(),nn)*nn;
    retval.putBox(1,4,VQ.getMatrix());
    retval(4,4)=1;
    return retval;
  }

//! @brief Default constructor.
Reflection3d::Reflection3d(void)
  : Trf3d()
  {
    FT_matrix rf=  reflection3d_matrix(Pos3d(0.0,0.0,0.0),Vector3d(0.0,0.0,1.0));
    putHomogenousMatrix(rf);
  }

//! @brief Constructor.
Reflection3d::Reflection3d(const Pos3d &Q,const Vector3d &d)
  : Trf3d()
  {
    FT_matrix rf=  reflection3d_matrix(Q,d);
    putHomogenousMatrix(rf);
  }

//! @brief Constructor.
Reflection3d::Reflection3d(const Plane &p)
  : Trf3d()
  {
    FT_matrix rf=  reflection3d_matrix(p.Point(),p.Normal());
    putHomogenousMatrix(rf);
  }


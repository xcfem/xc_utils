//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//giros.cc

#include "giros.h"
#include <cmath>

//En dos dimensiones.
ZMatrix<double> Giro2D(double ang)
  {
    const double c= cos(ang);
    const double s= sin(ang);
    ZMatrix<double> giro(2,2,0.0);
    giro(1,1)=c;  giro(1,2)=s;
    giro(2,1)=-s; giro(2,2)=c;
    return giro;
  }

//En tres dimensiones
ZMatrix<double> GiroX(double ang)
  {
    const double c= cos(ang);
    const double s= sin(ang);
    ZMatrix<double> giro(3,3,0.0);
    giro(1,1)= 1.0;
    giro(2,2)=c;  giro(2,3)=s;
    giro(3,2)=-s; giro(3,3)=c;
    return giro;
  }

ZMatrix<double> GiroY(double ang)
  {
    const double c= cos(ang);
    const double s= sin(ang);
    ZMatrix<double> giro(3,3,0.0);
    giro(1,1)=c;  giro(1,3)=s;
    giro(2,2)= 1.0;
    giro(3,1)=-s; giro(3,3)=c;
    return giro;
  }

ZMatrix<double> GiroZ(double ang)
  {
    const double c= cos(ang);
    const double s= sin(ang);
    ZMatrix<double> giro(3,3,0.0);
    giro(1,1)=c;  giro(1,2)=s;
    giro(2,1)=-s; giro(2,2)=c;
    giro(3,3)= 1.0;
    return giro;
  }

ZMatrix<double> GiroXYZ(double rx,double ry,double rz)
  {
    ZMatrix<double> giro(3,3,0.0);
    giro= GiroZ(rz) * GiroY(ry) * GiroX(rx);
    return giro;
  }

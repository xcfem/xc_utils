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
//Cuadratura2D.cc

#include "Cuadratura2D.h"


Cuadratura2D::Cuadratura2D( double x1, double x2,double y1, double y2,int nx, int ny) : ConjPG2(nx*ny)
  {
    int i= 1, j= 1;
    GaussPoints x(x1,x2,nx);
    GaussPoints y(y1,y2,ny);
    GaussPoints::const_iterator ii,jj;
    for(ii=x.begin();ii!=x.end();ii++)
      {
        j= 1;
        for(jj=y.begin();jj!=y.end();jj++)
          {
            (*this)[(i-1)*ny+j-1] = PsoGss2D(x[i].x, y[j].x, x[i].w*y[j].w);
            j++;
          }
        i++;
      }
  }
std::ostream& operator<<(std::ostream& o, const Cuadratura2D& gpts)
  {
    Cuadratura2D::const_iterator i;
    for(i=gpts.begin();i!=gpts.end();i++)
      o << *i << ", ";
    return o;
  }

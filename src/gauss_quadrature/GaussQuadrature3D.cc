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
//GaussQuadrature3D.cc

#include "GaussQuadrature3D.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"

GaussQuadrature3D::GaussQuadrature3D(const Pos3d &p1,const Pos3d &p2,int nx, int ny, int nz): ConjPG3(nx*ny*nz)
  {
    int i= 0,j= 0, k=0,l= 0;
    GaussPoints x(p1.x(),p2.x(),nx);
    GaussPoints y(p1.y(),p2.y(),ny);
    GaussPoints z(p1.z(),p2.z(),nz);
    GaussWeights1D wx, wy, wz;
    num_dim=0;
    if (nx>1) num_dim++;
    if (ny>1) num_dim++;
    if (nz>1) num_dim++;
    if (num_dim==0) num_dim++;
	GaussPoints::const_iterator ii;
    GaussPoints::const_iterator jj;
    GaussPoints::const_iterator kk;
    for(ii=x.begin();ii!=x.end();ii++)
      {
        wx= x.Get(i);
        j= 0;
        for(jj=y.begin();jj!=y.end();jj++)
          {
            wy= y.Get(j);
            k= 0;
            for(kk=z.begin();kk!=z.end();kk++)
              {
                wz= z.Get(k);
                Pos3d c(wx.x,wy.x,wz.x);
                double w=1.0;
                if (nx > 1) w*=wx.w;
                if (ny > 1) w*=wy.w;
                if (nz > 1) w*=wz.w;
                (*this)[l]= GaussWeights3D(wx.x,wy.x,wz.x, w);
                l++;
                k++;
              }
            j++;
          }
        i++;
      }
  }
std::ostream& operator<<(std::ostream& o, const GaussQuadrature3D& gpts)
  {
    GaussQuadrature3D::const_iterator i;
    for(i=gpts.begin();i!=gpts.end();i++)
      o << *i << ", ";
    return o;
  }

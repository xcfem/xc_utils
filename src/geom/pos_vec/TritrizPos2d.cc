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
//TritrizPos2d.cc

#include "TritrizPos2d.h"
#include "MatrizPos2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/geom/d2/BND2d.h"


TritrizPos2d::TritrizPos2d(const size_t capas)
  : TritrizPos<Pos2d>(capas) {}

Pos2d TritrizPos2d::GetCentro(void) const
  { return get_centro(*this,Segmento2d()); }

TritrizPos2d crea_uniform_grid(const BND2d &bnd,const size_t &ndiv_x,const size_t &ndiv_y,const size_t &ndiv_z)
  {
    const size_t ncapas= ndiv_z+1;
    TritrizPos2d retval(ncapas);
    Pos2d pmin= bnd.GetPMin();
    Pos2d pmax= bnd.GetPMax();
    GEOM_FT x= pmin.x();
    GEOM_FT y= pmin.y();
    const GEOM_FT Lx= pmax.x()-pmin.x();
    const GEOM_FT Ly= pmax.y()-pmin.y();
    const GEOM_FT inc_x= (ndiv_x > 0 ? Lx/ndiv_x: 0);
    const GEOM_FT inc_y= (ndiv_y > 0 ? Ly/ndiv_y: 0);
    const size_t nfilas= ndiv_x+1;
    const size_t ncols= ndiv_y+1;
    for(size_t k=1;k<=ncapas;k++) //Para cada capa.
      {
        retval[k-1]= MatrizPos2d(nfilas,ncols);
        for(size_t i=1;i<=nfilas;i++) //Para cada fila.
          {
            for(size_t j=1;j<=ncols;j++) //Para cada columna.
              {
                retval(k,i,j)= Pos2d(x,y);
                y+= inc_y;
              }
            y= pmin.y();
            x+= inc_x;
          }
        x= pmin.x();
      }
    return retval;
  }

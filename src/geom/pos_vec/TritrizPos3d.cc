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
//TritrizPos3d.cc

#include "TritrizPos3d.h"
#include "MatrizPos3d.h"
#include "xc_utils/src/geom/d1/Segmento3d.h"
#include "xc_utils/src/geom/d3/BND3d.h"
#include "xc_utils/src/geom/trf/Trf3d.h"
#include "xc_utils/src/geom/trf/Revolucion3d.h"

TritrizPos3d::TritrizPos3d(const size_t &iLayers)
  : TritrizPos<Pos3d>(iLayers) {}
TritrizPos3d::TritrizPos3d(const size_t &iLayers,const MatrizPos<Pos3d> &points)
  : TritrizPos<Pos3d>(iLayers,points) {}
TritrizPos3d::TritrizPos3d(const MatrizPos<Pos3d> &l1_points,const MatrizPos<Pos3d> &l2_points,
                           const MatrizPos<Pos3d> &l3_points,const MatrizPos<Pos3d> &l4_points,
                           const size_t &ndiv_12,const size_t &ndiv_13)
  : TritrizPos<Pos3d>(l1_points,l2_points,l3_points,l4_points,ndiv_12,ndiv_13) {}
TritrizPos3d::TritrizPos3d(const MatrizPos3d &l1_points,const MatrizPos3d &l2_points,
                           const MatrizPos3d &l3_points,const MatrizPos3d &l4_points,
                           const size_t &ndiv_12,const size_t &ndiv_13)
  : TritrizPos<Pos3d>(l1_points,l2_points,l3_points,l4_points,ndiv_12,ndiv_13) {}

Pos3d TritrizPos3d::GetCentro(void) const
  { return get_centro(*this,Segmento3d()); }

void TritrizPos3d::Transforma(const Trf3d &trf)
  { trf.Transforma(*this); }

TritrizPos3d TritrizPos3d::Transforma(const Trf3d &trf) const
  {
    TritrizPos3d retval(*this);
    retval.Transforma(trf);
    return retval;
  }

TritrizPos3d create_uniform_grid(const BND3d &bnd,const size_t &ndiv_x,const size_t &ndiv_y,const size_t &ndiv_z)
  {
    const size_t n_layers= ndiv_z+1;
    TritrizPos3d retval(n_layers);
    Pos3d pmin= bnd.GetPMin();
    Pos3d pmax= bnd.GetPMax();
    GEOM_FT x= pmin.x();
    GEOM_FT y= pmin.y();
    GEOM_FT z= pmin.z();
    const GEOM_FT Lx= pmax.x()-pmin.x();
    const GEOM_FT Ly= pmax.y()-pmin.y();
    const GEOM_FT Lz= pmax.z()-pmin.z();
    const GEOM_FT inc_x= (ndiv_x > 0 ? Lx/ndiv_x: 0);
    const GEOM_FT inc_y= (ndiv_y > 0 ? Ly/ndiv_y: 0);
    const GEOM_FT inc_z= (ndiv_z > 0 ? Lz/ndiv_z: 0);
    const size_t n_rows= ndiv_x+1;
    const size_t n_columns= ndiv_y+1;
    for(size_t k=1;k<=n_layers;k++) //For each layer.
      {
        retval[k-1]= MatrizPos3d(n_rows,n_columns);
        for(size_t i=1;i<=n_rows;i++) //For each row.
          {
            for(size_t j=1;j<=n_columns;j++) //For each column.
              {
                retval(k,i,j)= Pos3d(x,y,z);
                y+= inc_y;
              }
            y= pmin.y();
            x+= inc_x;
          }
        x= pmin.x();
        z+= inc_z;
      }
    return retval;
  }

//! @brief Return the revolution solid obtained by applying
//! to the matrix the transformation argument.
TritrizPos3d crea_vol_revolucion(const Revolucion3d &r,const MatrizPos3d &m)
  {
    if(m.isRow() || m.isColumn()) //Unidimensional.
      {
	std::cerr << __FUNCTION__ << "called with an one-dimensional matrix "
                  << " a degenerated volume will be returned." << std::endl;
      }
    return r.Aplica2d(m);
  }



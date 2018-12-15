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
//Pos3dArray3d

#ifndef ARRAY_3DPOS3D_H
#define ARRAY_3DPOS3D_H

#include "Pos3d.h"
#include "PosArray3d.h"

class Pos3dArray;
class Trf3d;
class Revolution3d;


//! @ingroup GEOM
//
//! @brief Position array in a three-dimensional space.
class Pos3dArray3d: public PosArray3d<Pos3d>
  {
  public:
    Pos3d getCenter(void) const;
    Pos3dArray3d(const size_t &iLayers= 1);
    Pos3dArray3d(const size_t &,const PosArray<Pos3d> &);
    Pos3dArray3d(const PosArray<Pos3d> &l1_points,const PosArray<Pos3d> &l2_points,
                 const PosArray<Pos3d> &l3_points,const PosArray<Pos3d> &l4_points,
                 const size_t &ndiv_12,const size_t &ndiv_13);
    Pos3dArray3d(const Pos3dArray &l1_points,const Pos3dArray &l2_points,
                 const Pos3dArray &l3_points,const Pos3dArray &l4_points,
                 const size_t &ndiv_12,const size_t &ndiv_13);
    void Transform(const Trf3d &trf);
    Pos3dArray3d Transform(const Trf3d &trf) const;
  };

class BND3d;

Pos3dArray3d create_uniform_grid(const BND3d &bnd,const size_t &ndiv_x,const size_t &ndiv_y,const size_t &ndiv_z);
Pos3dArray3d create_revolution_volume(const Revolution3d &r,const Pos3dArray &m);

#endif

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
//Pos3dArray

#ifndef POS3DARRAY_H
#define POS3DARRAY_H

#include "Pos3d.h"
#include "PosArray.h"

class Triangle3d;
class BND3d;
class Trf3d;
class Revolution3d;

//! @ingroup GEOM
//
//! @brief Array of positions in a three-dimensional space.
class Pos3dArray: public PosArray<Pos3d>
  {
    Pos3dArray(const PosArray<Pos3d> &mp3d);
    friend class Pos3dArray3d;
    Pos3d pos_lagrangiana(const size_t &i,const size_t &j) const;
    GEOM_FT dist_lagrange(void) const;
    GEOM_FT ciclo_lagrange(void);
  public:
    Pos3dArray(const size_t &f=1,const size_t &c=1,const Pos3d &p= Pos3d());
    Pos3dArray(const Pos3d &p1,const Pos3d &p2,const size_t &num,const GEOM_FT &ratio);
    Pos3dArray(const Pos3d &p1,const Pos3d &p2,const size_t &ndiv);
    Pos3dArray(const Pos3d &p1,const Pos3d &p2,const std::vector<GEOM_FT> &longs);
    Pos3dArray(const Pos3d &p0,const Pos3d &p1,const Pos3d &p2,const size_t &ndiv1,const size_t &ndiv2);
    Pos3dArray(const Pos3dArray &l1_points,const Pos3dArray &l2_points,const Pos3dArray &l3_points,const Pos3dArray &l4_points);
    Pos3dArray(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4,const size_t &ndiv1,const size_t &ndiv2);
    Pos3d getCenter(void) const;
    Triangle3d getTriangle1(const size_t &i,const size_t &j) const;
    Triangle3d getTriangle2(const size_t &i,const size_t &j) const;
    GEOM_FT Lagrange(const GEOM_FT &tol);
    void Transforma(const Trf3d &trf);
  };

GEOM_FT dist2(const Pos3dArray &ptos,const Pos3d &pt);
bool dist_menor(const Pos3dArray &ptos,const Pos3d &pt,const GEOM_FT &d_max);
GEOM_FT dist(const Pos3dArray &ptos,const Pos3d &pt);
GEOM_FT pseudo_dist2(const Pos3dArray &ptos,const Pos3d &pt);
GEOM_FT pseudo_dist(const Pos3dArray &ptos,const Pos3d &pt);

BND3d get_bnd(const Pos3dArray &ptos);

Pos3dArray create_revolution_surface(const Revolution3d &r,const Pos3dArray &m);
Pos3dArray Quadrilateral(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4,const size_t &ndiv1,const size_t &ndiv2);

#endif

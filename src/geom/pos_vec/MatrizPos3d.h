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
//MatrizPos3d

#ifndef MATRIZPOS3D_H
#define MATRIZPOS3D_H

#include "Pos3d.h"
#include "MatrizPos.h"

class Triangulo3d;
class BND3d;
class Trf3d;
class Revolucion3d;

//! @ingroup GEOM
//
//! @brief Matriz de posiciones en tres dimensiones.
class MatrizPos3d: public MatrizPos<Pos3d>
  {
    MatrizPos3d(const MatrizPos<Pos3d> &mp3d);
    friend class TritrizPos3d;
    Pos3d pos_lagrangiana(const size_t &i,const size_t &j) const;
    GEOM_FT dist_lagrange(void) const;
    GEOM_FT ciclo_lagrange(void);
  public:
    MatrizPos3d(const size_t &f=1,const size_t &c=1,const Pos3d &p= Pos3d());
    MatrizPos3d(const Pos3d &p1,const Pos3d &p2,const size_t &num,const GEOM_FT &ratio);
    MatrizPos3d(const Pos3d &p1,const Pos3d &p2,const size_t &ndiv);
    MatrizPos3d(const Pos3d &p1,const Pos3d &p2,const std::vector<GEOM_FT> &longs);
    MatrizPos3d(const Pos3d &p0,const Pos3d &p1,const Pos3d &p2,const size_t &ndiv1,const size_t &ndiv2);
    MatrizPos3d(const MatrizPos3d &puntos_l1,const MatrizPos3d &puntos_l2,const MatrizPos3d &puntos_l3,const MatrizPos3d &puntos_l4);
    MatrizPos3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4,const size_t &ndiv1,const size_t &ndiv2);
    Pos3d GetCentro(void) const;
    Triangulo3d GetTriangulo1(const size_t &i,const size_t &j) const;
    Triangulo3d GetTriangulo2(const size_t &i,const size_t &j) const;
    GEOM_FT Lagrange(const GEOM_FT &tol);
    void Transforma(const Trf3d &trf);
  };

GEOM_FT dist2(const MatrizPos3d &ptos,const Pos3d &pt);
bool dist_menor(const MatrizPos3d &ptos,const Pos3d &pt,const GEOM_FT &d_max);
GEOM_FT dist(const MatrizPos3d &ptos,const Pos3d &pt);
GEOM_FT pseudo_dist2(const MatrizPos3d &ptos,const Pos3d &pt);
GEOM_FT pseudo_dist(const MatrizPos3d &ptos,const Pos3d &pt);

BND3d get_bnd(const MatrizPos3d &ptos);

MatrizPos3d crea_sup_revolucion(const Revolucion3d &r,const MatrizPos3d &m);
MatrizPos3d cuadrilatero(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3,const Pos3d &p4,const size_t &ndiv1,const size_t &ndiv2);

#endif

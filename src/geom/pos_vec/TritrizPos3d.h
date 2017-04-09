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
//TritrizPos3d

#ifndef TRITRIZPOS3D_H
#define TRITRIZPOS3D_H

#include "Pos3d.h"
#include "TritrizPos.h"

class MatrizPos3d;
class Trf3d;
class Revolucion3d;


//! @ingroup GEOM
//
//! @brief «Tritriz» de posiciones en tres dimensiones.
class TritrizPos3d: public TritrizPos<Pos3d>
  {
  public:
    Pos3d GetCentro(void) const;
    TritrizPos3d(const size_t &capas= 1);
    TritrizPos3d(const size_t &capas,const MatrizPos<Pos3d> &);
    TritrizPos3d(const MatrizPos<Pos3d> &puntos_l1,const MatrizPos<Pos3d> &puntos_l2,
                 const MatrizPos<Pos3d> &puntos_l3,const MatrizPos<Pos3d> &puntos_l4,
                 const size_t &ndiv_12,const size_t &ndiv_13);
    TritrizPos3d(const MatrizPos3d &puntos_l1,const MatrizPos3d &puntos_l2,
                 const MatrizPos3d &puntos_l3,const MatrizPos3d &puntos_l4,
                 const size_t &ndiv_12,const size_t &ndiv_13);
    void Transforma(const Trf3d &trf);
    TritrizPos3d Transforma(const Trf3d &trf) const;
  };

class BND3d;

TritrizPos3d create_uniform_grid(const BND3d &bnd,const size_t &ndiv_x,const size_t &ndiv_y,const size_t &ndiv_z);
TritrizPos3d crea_vol_revolucion(const Revolucion3d &r,const MatrizPos3d &m);

#endif

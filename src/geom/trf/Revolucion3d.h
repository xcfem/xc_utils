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
//Revolucion3d.h
//Rotación en el plano.

#ifndef REVOLUCION3D_H
#define REVOLUCION3D_H

#include "xc_utils/src/geom/d1/Recta3d.h"
#include "Trf3d.h"

class MatrizPos3d;
class TritrizPos3d;


//! @ingroup GEOM
//
//! @brief Revolución.
class Revolucion3d: public Trf3d
  {
    Recta3d eje; //Eje de revolución.
    GEOM_FT theta; //!< Ángulo barrido por la revolución.
    size_t ndiv; //Número de divisiones.
  public:
    Revolucion3d(const Recta3d &e,const GEOM_FT &th= 0.0,const size_t &nd= 1);
    MatrizPos3d Aplica0d(const Pos3d &p) const;
    MatrizPos3d Aplica1d(const MatrizPos3d &m) const;
    TritrizPos3d Aplica2d(const MatrizPos3d &m) const;
    MatrizPos3d operator()(const Pos3d &) const;
    MatrizPos3d operator()(const MatrizPos3d &) const;
  };

#endif

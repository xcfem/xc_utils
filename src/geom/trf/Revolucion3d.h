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
//Revolution in a three-dimensional space.

#ifndef REVOLUCION3D_H
#define REVOLUCION3D_H

#include "xc_utils/src/geom/d1/Line3d.h"
#include "Trf3d.h"

class Pos3dArray;
class Pos3dArray3d;


//! @ingroup GEOM
//
//! @brief Revolución.
class Revolucion3d: public Trf3d
  {
    Line3d axis; //Revolution axis.
    GEOM_FT theta; //!< Swept angle.
    size_t ndiv; //number of divisions.
  public:
    Revolucion3d(const Line3d &e,const GEOM_FT &th= 0.0,const size_t &nd= 1);
    Pos3dArray Aplica0d(const Pos3d &p) const;
    Pos3dArray Aplica1d(const Pos3dArray &m) const;
    Pos3dArray3d Aplica2d(const Pos3dArray &m) const;
    Pos3dArray operator()(const Pos3d &) const;
    Pos3dArray operator()(const Pos3dArray &) const;
  };

#endif

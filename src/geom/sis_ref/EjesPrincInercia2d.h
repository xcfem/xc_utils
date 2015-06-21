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
//EjesPrincInercia2d.h

#ifndef EJESPRINCINERCIA2D_H
#define EJESPRINCINERCIA2D_H

#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"

class Ref2d2d;

//! @ingroup GEOM
//
//! @brief Ejes principales de inercia en dos dimensiones.
class EjesPrincInercia2d
  {
    Pos2d cdg; //Centro de gravedad.
    Vector2d eje1; //Ejes principal de inercia
                   //correspondiente al momento principal mayor. 
    GEOM_FT i1; //Momento de inercia principal mayor;
    GEOM_FT i2; //Momento de inercia principal menor;
  public:
    EjesPrincInercia2d(const Pos2d &cdg_,const GEOM_FT &Ix,const GEOM_FT &Iy,const GEOM_FT &Pxy);
    Ref2d2d GetEjes(void) const;
    const GEOM_FT &I1() const;
    const GEOM_FT &I2() const;
    inline Vector2d getVDirEje1(void) const
      { return eje1; }
    Vector2d getVDirEje2(void) const;
  };

std::ostream &operator<<(std::ostream &os,const EjesPrincInercia2d &ejes);


#endif





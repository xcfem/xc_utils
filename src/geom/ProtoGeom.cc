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
//ProtoGeom.cc

#include "ProtoGeom.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "matriz_FT.h"
#include <iostream>
#include "xc_utils/src/nucleo/aux_any.h"

//! @brief Constructor.
ProtoGeom::ProtoGeom(void)
  :exts(true) {}

//! @brief Imprime el valor de una propiedad geométrica del objeto (ver GetProp()).
void ProtoGeom::printprop(std::ostream *out_file,const any_const_ptr &prop) const
  {
     //Suponemos que es el nombre de una propiedad.
    if(const_ptr_is_empty(prop)) return;
    const_ptr_print(*out_file,prop);
  }

void ProtoGeom::Print(std::ostream &os) const
  { os << "nil_geom_obj"; }

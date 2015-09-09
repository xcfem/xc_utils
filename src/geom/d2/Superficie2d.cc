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
//Superficie2d.cc

#include "Superficie2d.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include <cstdlib>
#include <cmath>
#include "xc_basic/src/util/matem.h"

//! @brief Devuelve el area de la Superficie2d.
GEOM_FT Superficie2d::Area(void) const
  { return NAN; }

//! @brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
any_const_ptr Superficie2d::GetProp(const std::string &cod) const
  {
    static GEOM_FT tmp_ft= 0.0;
    if(cod=="getPerimetro")
      {
        tmp_ft= Perimetro();
        return any_const_ptr(tmp_ft);
      }
    else
      return GeomObj2d::GetProp(cod);
  }

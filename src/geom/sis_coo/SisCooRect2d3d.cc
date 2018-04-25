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
//SisCooRect2d3d.cc

#include "SisCooRect2d3d.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Vector2d.h"

#include "xc_basic/src/text/text_string.h"



//! El vector v define tres angulos de giro
//! around the axis 3, 2 and 1
//! que aplicados secuencialmente alinean el sistema
//! global con éste.
SisCooRect2d3d::SisCooRect2d3d(const VGlobal &v)
  : SisCooXd3d(2,v) {}
//! @brief Define un sistema de coordenadas de dimensión i
//! el x axis tendrá la dirección y sentido del vector v1
//! se pasa como parámetro.
SisCooRect2d3d::SisCooRect2d3d(const VGlobal &v1,const VGlobal &v2)
  : SisCooXd3d(2,v1,v2) {}
//! @brief Build the 2D coordinate system defined in a 3D space, so 
//! the axis 1 goes from p1 to p2 and p3 defines the plane that contains the
//! axis 1 and 2.
SisCooRect2d3d::SisCooRect2d3d(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : SisCooXd3d(2,p1,p2,p3) {}

//! @brief Return el vector unitario I en el sistema global.
SisCooRect2d3d::VGlobal SisCooRect2d3d::GetI(void) const
  { return getAxisVDir(1); }
//! @brief Return el vector unitario J en el sistema global.
SisCooRect2d3d::VGlobal SisCooRect2d3d::GetJ(void) const
  { return getAxisVDir(2); }

SisCooRect2d3d::VGlobal SisCooRect2d3d::GetCooGlobales(const VLocal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  { return SisCooXd3d::GetCooGlobales(v.GetMatriz()); }

SisCooRect2d3d::VLocal SisCooRect2d3d::GetCooLocales(const VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const matriz_FT tmp= SisCooXd3d::GetCooLocales(v);
    return VLocal(tmp(1),tmp(2));
  }


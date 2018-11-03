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
//Rect2d3dCooSys.cc

#include "Rect2d3dCooSys.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Vector2d.h"

#include "xc_utils/src/utils/text/text_string.h"



//! @brief Constructor.
//!
//! @param v: rotation angles about the axis 3, 2 and 1 that
//! applied sequentially align the global system with this one.
Rect2d3dCooSys::Rect2d3dCooSys(const VGlobal &v)
  : Xd3dCooSys(2,v) {}
//! @brief Define un sistema de coordenadas de dimensión i
//! el x axis tendrá la dirección y sentido del vector v1
//! se pasa como parámetro.
Rect2d3dCooSys::Rect2d3dCooSys(const VGlobal &v1,const VGlobal &v2)
  : Xd3dCooSys(2,v1,v2) {}
//! @brief Build the 2D coordinate system defined in a 3D space, so 
//! the axis 1 goes from p1 to p2 and p3 defines the plane that contains the
//! axis 1 and 2.
Rect2d3dCooSys::Rect2d3dCooSys(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : Xd3dCooSys(2,p1,p2,p3) {}

//! @brief Return el vector unitario I en el sistema global.
Rect2d3dCooSys::VGlobal Rect2d3dCooSys::GetI(void) const
  { return getAxisVDir(1); }
//! @brief Return el vector unitario J en el sistema global.
Rect2d3dCooSys::VGlobal Rect2d3dCooSys::GetJ(void) const
  { return getAxisVDir(2); }

Rect2d3dCooSys::VGlobal Rect2d3dCooSys::GetCooGlobales(const VLocal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  { return Xd3dCooSys::GetCooGlobales(v.getMatrix()); }

Rect2d3dCooSys::VLocal Rect2d3dCooSys::GetCooLocales(const VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const FT_matrix tmp= Xd3dCooSys::GetCooLocales(v);
    return VLocal(tmp(1),tmp(2));
  }

